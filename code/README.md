# Code for the Ultimate Sensor Kit

This folder holds the Arduino sketches of the kit. There are **two versions**, because the
kit has been shipped with two different wireless modules:

| Folder | Module | Bluetooth |
|---|---|---|
| `iot_project_esp01` | ESP-01 (ESP8266) | separate JDY-31 module |
| `iot_project_espc201` | **ESPC2-01 (ESP32-C2)** | built into the same module (BLE) |

Use the version that matches the module inside your kit. Everything else - the board, the
sensors, the lessons - is the same.

`components_basic` and `fun_project` are shared by both versions.

---

## Which folder do I need?

* **My kit has two small modules on the IoT page** (one ESP-01 with an adapter, one JDY-31
  Bluetooth module) -> use `iot_project_esp01`.
* **My kit has one module** labelled ESPC2-01 -> use `iot_project_espc201`.

---

## iot_project_esp01

```
iot_project_esp01/
    wifi/                 9 sketches (00-Set_software_serial ... 07-Auto_watering_system)
    bluetooth/           10 sketches (00-Bluetooth_start ... 09-Bluetooth_voice_control_relay)
    esp8266_firmware.zip the AT firmware shipped on the ESP-01
```

The ESP-01 is wired to D2/D3 with `SoftwareSerial`.

---

## iot_project_espc201

```
iot_project_espc201/
    wifi/                 9 sketches (00-Set_software_serial ... 07-Auto_watering_system)
    bluetooth/           10 sketches (00-Bluetooth_start ... 09-Bluetooth_voice_control_relay)
    README.md            notes about this version
```

Differences from the ESP-01 version:

* the module sits on **D0/D1**, the hardware serial port `Serial1` - no `SoftwareSerial`,
  so there are no bit errors at 115200;
* every Wi-Fi sketch calls `espModuleInit()`, which waits for the module to boot and then
  turns the echo off with `ATE0`;
* the Bluetooth sketches use `SunFounder_BLE.h` instead of a JDY-31, because the ESPC2-01
  speaks BLE (see the `bluetooth` folder);
* the phone side is **LightBlue** instead of the App Inventor apps.

---

## How to open a sketch

1. Open the folder of the project, for example `iot_project_espc201/wifi/01-Flame_alert_system`.
2. Double-click the `.ino` file - the Arduino IDE opens it with the libraries it needs.
3. Select **Arduino UNO R4 Minima** and the port of your board, then click **Upload**.

Every sketch prints on the Serial Monitor at **115200**.
