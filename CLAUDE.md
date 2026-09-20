# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

ESP-IDF firmware for an ESP32 (Elegoo ESP32 board) that reads temperature/humidity from a DHT11 sensor and logs both °C/°F and relative humidity every 2 seconds via `ESP_LOGI`. Target chip is `esp32` (Xtensa), configured in `sdkconfig`.

## Build environment (Windows)

This repo builds with a native Windows ESP-IDF v6.1 install managed by the Espressif IDE Manager (`eim`), **not** a plain `export.sh`/`export.ps1` setup — `idf.py` is not on `PATH` by default. Before running any `idf.py` command in a fresh shell, activate the environment first:

```powershell
. C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1
```

This sets `IDF_PATH`, `IDF_TOOLS_PATH`, `IDF_PYTHON_ENV_PATH` and adds `idf.py`/`esptool`/etc. to the session. In a Bash tool call the activation doesn't persist across separate tool invocations, so activate and build in one combined command, e.g.:

```powershell
. C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1 | Out-Null; idf.py build
```

Common commands (after activation):

```powershell
idf.py build                  # compile
idf.py -p <PORT> flash        # flash over serial (e.g. COM5 — see .vscode/settings.json idf.portWin)
idf.py -p <PORT> monitor      # serial monitor to view ESP_LOG output
idf.py -p <PORT> flash monitor
idf.py set-target esp32       # only needed if retargeting the chip
```

There is no separate lint or test suite in this project — validate changes by building and, when hardware is available, flashing + monitoring.

A Linux/devcontainer alternative also exists ([.devcontainer/](.devcontainer/), based on `espressif/idf`) which uses the standard `. $IDF_PATH/export.sh` activation instead.

**Never flash hardware without explicit user confirmation** — building is safe to do freely, flashing changes what's running on the user's physical board.

## Architecture

- `main/main.c` — the entire application. `app_main()` runs an infinite loop: read the DHT11 via `dht_read_float_data()`, log on success/failure, then `vTaskDelay(pdMS_TO_TICKS(2000))`. There is no other application logic, no multi-tasking, and no networking — keep additions here simple and consistent with a single-file learning project.
- DHT11 sensor reading uses the third-party **esp-idf-lib/dht** component (declared in `main/idf_component.yml`, fetched via the IDF Component Manager into `managed_components/esp-idf-lib__dht/`, gitignored). Do not hand-roll the DHT single-wire bit-banging protocol — use `dht_read_float_data(DHT_TYPE_DHT11, <gpio>, &humidity, &temperature)` from `dht.h`.
  - The component's registered CMake target name is `esp-idf-lib__dht` (matching its `managed_components/` directory name, not the shorter "dht"). It's linked via `PRIV_REQUIRES esp-idf-lib__dht` in `main/CMakeLists.txt`.
- The DHT data pin is set via `DHT_GPIO_PIN` in `main.c` (currently `GPIO_NUM_18`) — update this constant if the physical wiring changes; it must match the Elegoo board's DHT11 data-pin connection.
- `sdkconfig` is the generated ESP-IDF project configuration (target `esp32`); it's gitignored and not tracked, so it's local/machine-specific — don't assume it's part of the reviewable diff.
