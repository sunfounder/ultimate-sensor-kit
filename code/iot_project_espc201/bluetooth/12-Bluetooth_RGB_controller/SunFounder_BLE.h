/*
  SunFounder_BLE.h - BLE serial wrapper for the ESPC2-01 (ESP32-C2, ESP-AT firmware)

  What it does
      Wraps the BLE characteristic read/write of the module into an ordinary Stream
      object, so a sketch can call bleSerial.read() / bleSerial.print() the same way
      it used to with a JDY-31 module.

  Wiring (hardware Serial1 on the UNO R4)
      ESPC2-01 TX0  -> D0
      ESPC2-01 RX0  -> D1
      ESPC2-01 3V3  -> 3V3        (or the adapter's 5V pin, never 3.3V into 5V)
      ESPC2-01 GND  -> GND
      IO9           -> leave floating
      The 9V supply must be plugged in: the module draws more than 400 mA at start-up.

  Characteristics (measured with the ESP-AT v4.1.1.0 Wi-Fi + BLE build)
      phone  -> module : write to C304, the module prints +WRITE:0,1,5,,<len>,<data>
      module -> phone  : notify C305 with AT+BLEGATTSNTFY=0,1,6,<len>
*/

#ifndef SUNFOUNDER_BLE_H
#define SUNFOUNDER_BLE_H

#include <Arduino.h>

#define BLE_PORT          Serial1
#define BLE_CONN_INDEX    0
#define BLE_SRV_INDEX     1
#define BLE_RX_CHAR       5      // C304, written by the phone
#define BLE_TX_CHAR       6      // C305, notified by the module
#define BLE_BUF_SIZE      512

class BLEStream : public Stream {
 public:
  BLEStream() : _head(0), _tail(0), _count(0), _olen(0), _st(0), _field(0), _len(0), _remain(0) {}

  // ---------------- initialisation ----------------
  void begin(unsigned long baud = 115200) {
    BLE_PORT.begin(baud);
    delay(800);                 // let the module finish booting
    _drainInput();
    _cmd("ATE0", 800);
    _cmd("AT+BLEINIT=2", 4000);
    _cmd("AT+BLENAME=\"SunFounder-C2\"", 1200);
    _cmd("AT+BLEADVPARAM=32,32,0,0,7", 1200);
    _cmd("AT+BLEADVDATA=\"0201060E0953756E466F756E6465722D4332\"", 1500);
    _cmd("AT+BLEADVSTART", 1500);
  }

  void begin(long baud) { begin((unsigned long)baud); }

  // Print the start-up banner and ask the module whether BLE really started.
  void report() {
    while (BLE_PORT.available()) BLE_PORT.read();
    BLE_PORT.print("AT+BLEINIT?\r\n");
    unsigned long t0 = millis();
    String r;
    while (millis() - t0 < 700) {
      while (BLE_PORT.available() && r.length() < 256) r += (char)BLE_PORT.read();
    }
    if (r.indexOf("+BLEINIT:2") >= 0) {
      Serial.println("[OK] BLE is ready - scan for \"SunFounder-C2\" on your phone");
    } else {
      Serial.print("[!] no reply from the module, got: ");
      Serial.println(r);
    }
  }



  // ---------------- Stream interface ----------------
  int available() override {
    if (_olen > 0 && millis() - _lastWrite > 30) flushOut();   // send once the line goes quiet
    pump();
    return _count;
  }

  int read() override {
    pump();
    if (_count == 0) return -1;
    uint8_t c = _buf[_tail];
    _tail = (_tail + 1) % BLE_BUF_SIZE;
    _count--;
    return c;
  }

  int peek() override {
    pump();
    if (_count == 0) return -1;
    return _buf[_tail];
  }

  size_t write(uint8_t c) override {
    // more than 30 ms since the last byte: this is a new message, send the old one first
    if (_olen > 0 && millis() - _lastWrite > 30) flushOut();
    _lastWrite = millis();
    if (_olen < (int)sizeof(_out)) _out[_olen++] = c;
    if (_olen >= 19 || c == '\n' || c == '\r') flushOut();
    return 1;
  }

  size_t write(const uint8_t *buffer, size_t size) override {
    for (size_t i = 0; i < size; i++) write(buffer[i]);
    return size;
  }

  using Print::write;

  void flush() override { flushOut(); }

  // is a phone connected right now?
  bool connected() {
    BLE_PORT.print("AT+BLECONN?\r\n");
    String r = _waitReply(400);
    return r.indexOf("+BLECONN:") >= 0 && r.length() > 12;
  }

 private:
  uint8_t _buf[BLE_BUF_SIZE];
  int _head, _tail, _count;
  uint8_t _out[24];
  int _olen;
  // parser state machine
  int _st, _field, _len, _remain;
  unsigned long _lastWrite = 0;

  void _drainInput() {
    unsigned long t0 = millis();
    while (millis() - t0 < 50) {
      while (BLE_PORT.available()) BLE_PORT.read();
    }
  }

  String _waitReply(unsigned long ms) {
    String s;
    unsigned long t0 = millis();
    while (millis() - t0 < ms) {
      while (BLE_PORT.available()) {
        char c = (char)BLE_PORT.read();
        s += c;
        if (s.indexOf("OK\r\n") >= 0 || s.indexOf("ERROR") >= 0) return s;
      }
    }
    return s;
  }

  void _cmd(const char *cmd, unsigned long ms) {
    _drainInput();
    BLE_PORT.print(cmd);
    BLE_PORT.print("\r\n");
    _waitReply(ms);
  }

  void _push(uint8_t c) {
    if (_count >= BLE_BUF_SIZE) return;    // buffer full: drop the byte
    _buf[_head] = c;
    _head = (_head + 1) % BLE_BUF_SIZE;
    _count++;
  }

  // send the buffered data to the phone as a notification
  void flushOut() {
    if (_olen == 0) return;
    BLE_PORT.print("AT+BLEGATTSNTFY=");
    BLE_PORT.print(BLE_CONN_INDEX); BLE_PORT.print(",");
    BLE_PORT.print(BLE_SRV_INDEX);  BLE_PORT.print(",");
    BLE_PORT.print(BLE_TX_CHAR);    BLE_PORT.print(",");
    BLE_PORT.print(_olen);
    BLE_PORT.print("\r\n");

    // wait for the '>' prompt
    bool prompt = false;
    unsigned long t0 = millis();
    while (millis() - t0 < 500) {
      while (BLE_PORT.available()) {
        uint8_t c = BLE_PORT.read();
        if (c == '>') { prompt = true; break; }
      }
      if (prompt) break;
    }
    if (prompt) {
      BLE_PORT.write(_out, _olen);
      _waitReply(500);
    }
    _olen = 0;
  }

  // pull bytes from the serial port and parse the +WRITE events
  void pump() {
    while (BLE_PORT.available()) {
      uint8_t c = BLE_PORT.read();

      switch (_st) {
        case 0:  // look for '+'
          if (c == '+') _st = 1;
          break;

        case 1:  // match "WRITE:"
          {
            static const char *kw = "WRITE:";
            static int idx = 0;
            if (c == kw[idx]) {
              idx++;
              if (kw[idx] == 0) { _st = 2; _field = 0; _len = 0; idx = 0; }
            } else {
              idx = (c == '+') ? 1 : 0;
              _st = (c == '+') ? 1 : 0;
            }
          }
          break;

        case 2:  // read the fields; the number before the last comma is the length
          if (c == ',') {
            if (_field == 4) _remain = _len;   // the length field has just been parsed
            _field++;
            _len = 0;
            if (_field == 5) _st = 3;
          } else if (c >= '0' && c <= '9') {
            _len = _len * 10 + (c - '0');
          }
          break;

        case 3:  // read the payload
          _push(c);
          if (--_remain <= 0) _st = 0;
          break;
      }
    }
  }
};

#endif
