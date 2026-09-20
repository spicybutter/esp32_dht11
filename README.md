# esp32_dht11

ESP-IDF project for an ESP32 (Elegoo ESP32 board) reading temperature/humidity from a DHT11 sensor.

Every 2 seconds, `app_main()` reads the DHT11 via the [esp-idf-lib/dht](https://components.espressif.com/components/esp-idf-lib/dht) component and logs the result over UART, e.g.:

```
I (2345) dht11: Temperature: 24.0 C (75.2 F), Humidity: 55.0 %
```

## Requirements

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) (target chip: `esp32`)
- A DHT11 sensor wired to the board (data pin + pull-up resistor, per the Elegoo kit wiring diagram). The data pin GPIO is set by `DHT_GPIO_PIN` in [main/main.c](main/main.c) — update it to match your wiring.

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
  main.c            # application entry point (app_main): reads DHT11, logs C/F + humidity
  idf_component.yml # declares the esp-idf-lib/dht dependency
  CMakeLists.txt    # component registration
CMakeLists.txt      # top-level ESP-IDF project file
sdkconfig           # generated project configuration (target: esp32)
```

## Next steps

- Publish sensor readings somewhere beyond the UART log (e.g. MQTT, a web server, etc.).
