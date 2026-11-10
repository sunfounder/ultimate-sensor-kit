/*
  Vibration Alert System with IFTTT

  A vibration switch (SW-420) is watched all the time. When it shakes, the board sends
  one HTTP request to IFTTT, and IFTTT sends you an email or a phone notification.
  Two alerts are kept at least two minutes apart, so your inbox does not fill up.

  Board:     Arduino Uno R4 Minima
  Module:    ESPC2-01 (ESP32-C2) with ESP-AT firmware, on D0/D1
  Component: Vibration sensor (SW-420)
*/

#define EspSerial Serial1
#define DEBUG true

// ---- what you have to fill in ----
String mySSID = "your_ssid";      // your Wi-Fi network
String myPWD = "your_password";  // its password
String myHOST = "maker.ifttt.com";
String myPORT = "80";

// Paste the whole address IFTTT shows you, https:// included. The sketch keeps only the
// part after the host name, because the module opens a plain TCP connection to port 80.
String URL = "https://maker.ifttt.com/trigger/vibration_detected/with/key/xxxxxxxxxxxxxxxxxxxxxx";

// ---- timing ----
unsigned long lastAlertTime = 0;
const unsigned long postingInterval = 120000L;   // at most one alert every 2 minutes

const int sensorPin = 7;   // SW-420 digital output: HIGH while it shakes

bool wifiOK = false;

// Turn "https://maker.ifttt.com/trigger/xxx/with/key/yyy" into "/trigger/xxx/with/key/yyy".
String urlPath() {
  String u = URL;
  u.replace("https://", "");
  u.replace("http://", "");
  int slash = u.indexOf('/');
  return (slash >= 0) ? u.substring(slash) : "/";
}

// The module needs about a second to boot and prints its start-up log on the same wire.
// Wait for "ready", then switch the echo off so the replies stay readable.
void espModuleInit() {
  unsigned long t0 = millis();
  String buf;
  while (millis() - t0 < 5000) {
    while (EspSerial.available() && buf.length() < 512) {
      buf += (char)EspSerial.read();
      if (buf.indexOf("ready") >= 0) t0 = millis() - 5000;   // leave the loop
    }
    if (buf.indexOf("ready") >= 0) break;
  }
  // The module keeps printing boot lines for a while after "ready", so give it time and
  // throw them away - otherwise they end up mixed into the reply of the first command.
  delay(1000);
  while (EspSerial.available()) EspSerial.read();

  EspSerial.print("ATE0\r\n");
  delay(500);
  while (EspSerial.available()) EspSerial.read();
}

// Send one AT command and collect the reply. Stops early when one of the two
// markers shows up, or when the time is over - it never blocks for ever.
String at(const String& cmd, unsigned long waitMs, const char* okMark, const char* errMark) {
  while (EspSerial.available()) EspSerial.read();
  EspSerial.print(cmd);
  EspSerial.print("\r\n");
  if (DEBUG) {
    Serial.print("  > ");
    Serial.println(cmd);
  }

  unsigned long t0 = millis();
  String r;
  while (millis() - t0 < waitMs) {
    while (EspSerial.available() && r.length() < 512) r += (char)EspSerial.read();
    if (okMark && r.indexOf(okMark) >= 0) break;
    if (errMark && r.indexOf(errMark) >= 0) break;
  }
  return r;
}

bool joinWiFi() {
  at("AT+CWMODE=1", 1500, "OK", "ERROR");

  Serial.print("joining Wi-Fi ... ");
  String r = at("AT+CWJAP=\"" + mySSID + "\",\"" + myPWD + "\"", 20000,
               "WIFI GOT IP", "FAIL");
  bool ok = r.indexOf("WIFI GOT IP") >= 0;
  if (ok) {
    Serial.println("connected");
  } else {
    Serial.println("FAILED");
    String why = r;
    why.replace("\r", "");
    why.replace("\n", " | ");
    Serial.print("  module said: ");
    Serial.println(why.length() ? why : "(nothing)");
  }
  return ok;
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println();
  Serial.println("=== Vibration Alert System (IFTTT) ===");

  Serial.print("IFTTT path: ");
  Serial.println(urlPath());

  pinMode(sensorPin, INPUT);

  EspSerial.begin(115200);
  espModuleInit();
  Serial.println("module is ready");

  wifiOK = joinWiFi();
  if (!wifiOK) {
    Serial.println("The alerts cannot be sent until Wi-Fi works. The board keeps trying.");
  }
}

unsigned long lastRetry = 0;

void loop() {
  // keep trying to get online, without blocking
  if (!wifiOK && millis() - lastRetry > 30000) {
    lastRetry = millis();
    wifiOK = joinWiFi();
  }

  int shake = digitalRead(sensorPin);

  if (shake) {
    if (lastAlertTime == 0 || millis() - lastAlertTime > postingInterval) {
      Serial.println("Detected vibration!!!");
      lastAlertTime = millis();
      sendAlert();
    } else {
      Serial.print("Detected vibration!!! ");
      Serial.println("An alert was sent recently, so this one is skipped.");
    }
  } else if (DEBUG) {
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 2000) {
      lastPrint = millis();
      Serial.print("Detecting...  pin=");
      Serial.println(shake);
    }
  }
  delay(200);
}

void sendAlert() {
  if (!wifiOK) {
    Serial.println("  no Wi-Fi, alert dropped");
    return;
  }

  // Build the HTTP request. The length must match exactly, because CIPSEND counts bytes.
  String req = "GET " + urlPath() + " HTTP/1.1\r\n";
  req += "Host: maker.ifttt.com\r\n";
  req += "Connection: close\r\n";
  req += "\r\n";

  at("AT+CIPMUX=0", 1000, "OK", "ERROR");

  String r = at("AT+CIPSTART=\"TCP\",\"" + myHOST + "\"," + myPORT, 5000, "OK", "ERROR");
  if (r.indexOf("OK") < 0 && r.indexOf("ALREADY") < 0) {
    Serial.println("  could not reach IFTTT, alert dropped");
    return;
  }

  // Ask the module to accept req.length() bytes, then wait for the ">" prompt.
  while (EspSerial.available()) EspSerial.read();
  EspSerial.print("AT+CIPSEND=");
  EspSerial.print(req.length());
  EspSerial.print("\r\n");

  bool prompt = false;
  unsigned long t0 = millis();
  while (millis() - t0 < 3000) {
    while (EspSerial.available()) {
      if (EspSerial.read() == '>') { prompt = true; break; }
    }
    if (prompt) break;
  }
  if (!prompt) {
    Serial.println("  no > prompt, alert dropped");
    at("AT+CIPCLOSE", 1000, "OK", "ERROR");
    return;
  }

  EspSerial.print(req);                    // the request itself
  Serial.println("  request sent to IFTTT");
  delay(1500);                             // give the module time to deliver it

  at("AT+CIPCLOSE", 1000, "OK", "ERROR");
  lastAlertTime = millis();
}
