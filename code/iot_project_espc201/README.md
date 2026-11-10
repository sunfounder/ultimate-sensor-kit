# ESPC2-01 example code (Wi-Fi + Bluetooth)

The original sketches come from `iot_project` in sunfounder/ultimate-sensor-kit and have
been changed to use the **ESPC2-01 (ESP32-C2)** module.

## Wiring (the same for the Wi-Fi and the Bluetooth projects)

```
module TX0  ->  R4 D0
module RX0  ->  R4 D1
module 3V3  ->  R4 3V3        (or the adapter's 5V pin - never 3.3V into 5V)
module GND  ->  R4 GND
module IO9  ->  leave floating (do not tie it to GND)
```

**The 9V supply must be plugged in.** On USB power alone the module keeps restarting.

## What was changed

### wifi/ (8 sketches)

| Change | Reason |
|---|---|
| `SoftwareSerial EspSerial(2, 3)` -> `#define EspSerial Serial1` | uses the R4 hardware serial port D0/D1, no bit errors at 115200 |
| new `espModuleInit()` | waits for the module to boot, then sends `ATE0` so Blynk can parse the replies |

### bluetooth/ (10 sketches)

| Change | Reason |
|---|---|
| `SoftwareSerial bleSerial(3, 4)` -> `BLEStream bleSerial` | see `SunFounder_BLE.h` |
| new `SunFounder_BLE.h` | wraps the BLE characteristic read/write into a normal serial port, so the project code barely changes |

What `BLEStream` does internally:

- `begin()`: `AT+BLEINIT=2` -> `AT+BLEADVPARAM` -> `AT+BLEADVDATA` -> `AT+BLEADVSTART`
- `read()`: parses `+WRITE:0,1,5,,<len>,<data>` and hands the payload to the sketch
- `print()`: sends `AT+BLEGATTSNTFY=0,1,6,<len>` so the phone receives a notification

## Phone side (LightBlue)

| Action | Characteristic |
|---|---|
| send data to the board | **C304** -> Write new value |
| receive data from the board | **C305** -> tap **Subscribe** first |
| read a value from the board | **C300** -> Read |

## Suggested test order

1. `bluetooth/00-Bluetooth_start` - plain serial bridge, confirms the module answers
2. `bluetooth/01-Bluetooth_lcd` - type on the phone, the text appears on the LCD
3. the remaining Bluetooth projects
4. `wifi/00-Set_software_serial` - Wi-Fi serial bridge
5. `wifi/00-Blynk_quick_start` - fill in your own token / ssid / password
6. `wifi/01` to `wifi/07`

## Notes

- Serial Monitor: **115200** for both tracks.
- Characteristic **C304** writes to the board, **C305** notifies the phone, **C300** can be read.
- The `.aia` / `.apk` files in some Bluetooth folders are the old **App Inventor** apps
  built for the JDY-31 (classic Bluetooth). They do **not** work with BLE - use LightBlue.
