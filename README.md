# esp32_dht11

ESP-IDF project for an ESP32 (Elegoo ESP32 board) reading temperature/humidity from a DHT11 sensor.

> **Status:** project skeleton only — `main/main.c` currently has an empty `app_main()`. DHT11 sensor reading is not yet implemented.

## Requirements

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) (target chip: `esp32`)
- A DHT11 sensor wired to the board (data pin + pull-up resistor, per the Elegoo kit wiring diagram)

## Building and flashing

```sh
. $IDF_PATH/export.sh   # set up the ESP-IDF environment, once per shell
idf.py set-target esp32
idf.py build
idf.py -p <PORT> flash monitor
```

Replace `<PORT>` with the serial port the board enumerates as (e.g. `COM3` on Windows, `/dev/ttyUSB0` on Linux).

## Dev Container

A dev container is provided under [.devcontainer/](.devcontainer/) based on the official `espressif/idf` Docker image, with the ESP-IDF and ESP-IDF Web extensions pre-configured for VS Code. Reopen the folder in the container to get a ready-to-use build environment without installing ESP-IDF locally.

## Project layout

```
main/
  main.c          # application entry point (app_main)
  CMakeLists.txt  # component registration
CMakeLists.txt    # top-level ESP-IDF project file
sdkconfig         # generated project configuration (target: esp32)
```

## Next steps

- Wire up the DHT11 driver (bit-banged single-wire protocol or an existing ESP-IDF component) and read temperature/humidity in `app_main`.
- Log or publish sensor readings (e.g. via UART log output, MQTT, etc.).
