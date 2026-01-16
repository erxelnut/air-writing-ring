# air-writing-ring
## How to set up the Development Environment.
- clone this git, install nix.
- run `nix develop`
- incase if you don't have arduino-cli config, run `arduino-cli config init`
## Set up the Development Environment for Seeeduino Xiao nRF52840 Sense
- go to ~/.arduino15/arduino-cli.yaml, at the additional_urls: add `https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json`
- update index with `arduino-cli core update-index`
- search board core: `arduino-cli core search "..."`
- install board core: `arduino-cli core install ...:...`
  - `arduino-cli core install Seeeduino:nrf52`
- search library: `arduino-cli lib search "..."`
  - bluemicro_hid
  - Adafruit TinyUSB Library
- install libraries: `arduino-cli lib install "..."`
  - arduino-cli lib install "bluemicro_hid"
  - arduino-cli lib install "Adafruit TinyUSB Library"
  - arduino-cli lib install "Seeed Arduino LSM6DS3"
- what we have now: arduino-cli with Seeeduino:nrf52 board core and some of it's libraries.
## Air Mouse Feature (Barebone)
- go to dir with the .ino file you want to try. 
  - plug your Seeeduino board, compile and install
```
arduino-cli compile --fqbn Seeeduino:nrf52:xiaonRF52840Sense .
arduino-cli upload -p /dev/ttyACM0 --fqbn Seeeduino:nrf52:xiaonRF52840Sense .
```



