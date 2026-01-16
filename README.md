# air-writing-ring

`arduino-cli config init`
go to ~/.arduino15/arduino-cli.yaml, at the additional_urls: add `https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json`
update index with `arduino-cli core update-index`
search board core: `arduino-cli core search "..."`
install board core: `arduino-cli core install ...:...`
`arduino-cli core install Seeeduino:nrf52`
search library: `arduino-cli lib search "..."`
install library: `arduino-cli lib install "..."`
- arduino-cli lib install "Seeed Arduino LSM6DS3"
- Mouse.h

arduino-cli compile --fqbn Seeeduino:nrf52:xiaonRF52840Sense .
arduino-cli lib install "bluemicro_hid"
arduino-cli lib install "Adafruit TinyUSB Library"

arduino-cli compile --fqbn Seeeduino:nrf52:xiaonRF52840Sense .

arduino-cli upload -p /dev/ttyACM0 --fqbn Seeeduino:nrf52:xiaonRF52840Sense .



