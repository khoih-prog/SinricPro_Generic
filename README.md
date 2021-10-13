## SinricPro_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/SinricPro_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/SinricPro_Generic.svg)](https://github.com/khoih-prog/SinricPro_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/SinricPro_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/SinricPro_Generic.svg)](http://github.com/khoih-prog/SinricPro_Generic/issues)

---
---

## Table of Contents

* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
  * [8. For fixing ESP8266 compile error](#8-for-fixing-esp8266-compile-error)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Important Notes](#important-notes)
* [Full user documentation](#full-user-documentation)
* [Important Notes](#important-notes)
* [Examples](#examples)
  * [Examples for ESP32/ESP8266](#examples-for-esp32esp8266)
    * [ESP32/ESP8266 examples](examples/ESP)
  * [Examples for Generic Boards (SAMD, nRF52, STM32, SAM DUE, etc.)](#examples-for-generic-boards-samd-nrf52-stm32-sam-due-etc)
    * [Generic Boards examples](examples/Generic)
  * [Examples for WT32_ETH01](#examples-for-wt32_eth01)
* [HOWTO Usage](#howto-usage)
  * [Include SinricPro-Library (SinricPro_Generic.h) and SinricPro-Device-Libraries (eg. SinricProSwitch.h)](#include-sinricpro-library-sinricpro_generich-and-sinricpro-device-libraries-eg-sinricproswitchh)
  * [Define your credentials from SinricPro-Portal (portal.sinric.pro)](#define-your-credentials-from-sinricpro-portal-portalsinricpro)
  * [Define callback routine(s)](#define-callback-routines)
  * [In setup()](#in-setup)
  * [In loop()](#in-loop)
* [HOWTO Add a device](#howto-add-a-device)
  * [Example](#example)
  * [Example 2 (alternatively)](#example-2-alternatively)
* [How to retrieve a device for sending an event?](#how-to-retrieve-a-device-for-sending-an-event)
  * [Example 1](#example-1)
  * [Example 2 (alternatively)](#example-2-alternatively-1)
* [Example SAMD_WiFiNINA_Switch](#example-samd_wifinina_switch)
  * [ 1. File SAMD_WiFiNINA_Switch.ino](#1-file-samd_wifinina_switchino)
  * [ 2. File defines.h](#2-file-definesh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. SAMD_WiFiNINA_TV on NANO_33_IOT](#1-samd_wifinina_tv-on-nano_33_iot)
  * [ 2. SAMD_WiFiNINA_Light on NANO_33_IOT](#2-samd_wifinina_light-on-nano_33_iot)
  * [ 3. Generic_Ethernet_Blinds on nRF52 NRF52840_ITSYBITSY with W5500 Ethernet](#3-generic_ethernet_blinds-on-nrf52-nrf52840_itsybitsy-with-w5500-ethernet)
  * [ 4. Generic_Ethernet_Blinds on Seeeduino SEEED_XIAO_M0 with W5500 Ethernet](#4-generic_ethernet_blinds-on-seeeduino-seeed_xiao_m0-with-w5500-ethernet)
  * [ 5. Generic_Ethernet_Blinds on Arduino SAMD_NANO_33_IOT with WiFiNINA](#5-generic_ethernet_blinds-on-arduino-samd_nano_33_iot-with-wifinina)
  * [ 6. Generic_Ethernet_Blinds on Adafruit nRF52 NRF52840_FEATHER with W5500 Ethernet ](#6-generic_ethernet_blinds-on-adafruit-nrf52-nrf52840_feather-with-w5500-ethernet)
  * [ 7. Generic_Ethernet_Blinds on STM32F7 Nucleo-144 NUCLEO_F767ZI with W5500 Ethernet](#7-generic_ethernet_blinds-on-stm32f7-nucleo-144-nucleo_f767zi-with-w5500-ethernet)
  * [ 8. WIOT_MultiSwitch_LCD on SeeedStudio SAMD51 WIO Terminal](#8-wiot_multiswitch_lcd-on-seeedstudio-samd51-wio-terminal)
  * [ 9. Generic_WiFiNINA_Blinds on MBED NANO_RP2040_CONNECT](#9-generic_wifinina_blinds-on-mbed-nano_rp2040_connect)
  * [10. RP2040_WiFiNINA_Blinds on MBED NANO_RP2040_CONNECT](#10-rp2040_wifinina_blinds-on-mbed-nano_rp2040_connect)
  * [11. Blinds on WT32-ETH01 with ETH_PHY_LAN8720](#11-blinds-on-wt32-eth01-with-eth_phy_lan8720)
* [Devices](#devices)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---


## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ESP32 Core 2.0.0+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
 3. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS. 
 4. [`Arduino AVR core 1.8.3+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 5. [`Teensy core v1.55+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards..
 6. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 7. [`Arduino SAMD core 1.8.11+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 8. [`Adafruit SAMD core 1.7.5+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 9. [`Seeeduino SAMD core 1.8.2+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
10. [`Adafruit nRF52 v1.1.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest) 
11. [`Arduino Core for STM32 v2.1.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
12. [`Arduino mbed_rp2040 core 2.5.2+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino RP2040-based boards, such as **Arduino Nano RP2040 Connect, RASPBERRY_PI_PICO, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
13. [`Earle Philhower's arduino-pico core v1.9.5+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
14. [`ArduinoJson v6.18.5+`](https://github.com/bblanchon/ArduinoJson). [![GitHub release](https://img.shields.io/github/release/bblanchon/ArduinoJson.svg)](https://github.com/bblanchon/ArduinoJson/releases/latest)
15. [`WebSockets_Generic v2.10.0+`](https://github.com/khoih-prog/WebSockets_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebSockets_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic)

16. For built-in LAN8742A Ethernet:
   - [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest)
   - [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
   
17. For W5x00 Ethernet:
   - [`Ethernet library v2.0.0+`](https://github.com/arduino-libraries/Ethernet) for W5100, W5200 and W5500.  [![GitHub release](https://img.shields.io/github/release/arduino-libraries/Ethernet.svg)](https://github.com/arduino-libraries/Ethernet/releases/latest)
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500. [![GitHub release](https://img.shields.io/github/release/adafruit/Ethernet2.svg)](https://github.com/adafruit/Ethernet2/releases/latest)
   - [`Ethernet3 library v1.5.5+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip. [![GitHub release](https://img.shields.io/github/release/sstaub/Ethernet3.svg)](https://github.com/sstaub/Ethernet3/releases/latest)
   
18. For ENC28J60 Ethernet:
   - [`EthernetENC library v2.0.1+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.10+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)

19. [`WiFiNINA_Generic library v1.8.13+`](https://github.com/khoih-prog/WiFiNINA_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) if using WiFiNINA for boards such as Nano 33 IoT, nRF52, Teensy, etc.
20. [`Seeed_Arduino_rpcWiFi library v1.0.5+`](https://github.com/Seeed-Studio/Seeed_Arduino_rpcWiFi) for WIO-Terminal or boards using **Realtek RTL8720DN WiFi**. [![GitHub release](https://img.shields.io/github/release/Seeed-Studio/Seeed_Arduino_rpcWiFi.svg)](https://github.com/Seeed-Studio/Seeed_Arduino_rpcWiFi/releases/latest). To be used with [`Seeed_Arduino_rpcUnified library v2.1.3+`](https://github.com/Seeed-Studio/Seeed_Arduino_rpcUnified). [![GitHub release](https://img.shields.io/github/release/Seeed-Studio/Seeed_Arduino_rpcUnified.svg)](https://github.com/Seeed-Studio/Seeed_Arduino_rpcUnified/releases/latest).

21. [`WebServer_WT32_ETH01 library v1.2.0+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) to use WT32_ETH01 (ESP32 + LAN8720). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01).

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**SinricPro_Generic**](https://github.com/khoih-prog/SinricPro_Generic), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/SinricPro_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**SinricPro_Generic**](https://github.com/khoih-prog/SinricPro_Generic) page.
2. Download the latest release `SinricPro_Generic-master.zip`.
3. Extract the zip file to `SinricPro_Generic-master` directory 
4. Copy whole `SinricPro_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**SinricPro_Generic** library](https://platformio.org/lib/show/11243/SinricPro_Generic) by using [**Library Manager**](https://platformio.org/lib/show/11243/SinricPro_Generic/installation). Search for [**SinricPro_Generic**](https://platformio.org/lib/show/11243/SinricPro_Generic) in [Platform.io **Author's Libraries**](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.1.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0). 

Supposing the Adafruit nRF52 version is 1.1.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.1.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.15/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.15. These files must be copied into the directory:

- `./arduino-1.8.15/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.15/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.11) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.11).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.5) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.5). 

Supposing the Adafruit SAMD core version is 1.7.5. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.5/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.5/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.5/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2). 

Supposing the Seeeduino SAMD core version is 1.8.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.1.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.1.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.1.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.1.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.1.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.1.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 2.5.2. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`

---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.13/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

#### 8. For fixing ESP8266 compile error

To fix `ESP8266 compile error` such as

```
error: 'class EthernetClass' has no member named 'init'
Ethernet.init (USE_THIS_SS_PIN);
```

just rename the following file in ./arduino-1.8.13/hardware/esp8266com/esp8266/libraries/Ethernet directory

- From `Ethernet.h` to `Ethernet_ESP8266.h`

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).


---
---

### Important Notes

1. Code is restructured to provide flexibility to make it easy to support many more **WiFi/Ethernet** modules/shields in the future. Please delete the *.cpp files, replaced by *.hpp files, in the src directory, if *.cpp files still exist after installing new version.

2. For **Adafruit nRF52**, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = MO(SI)
  - SPI_MISO  = MI(SO)
  - SPI_SCK   = SCK

3. For **Adafruit SAMD21/SAMD51**, use the SPI's CS/SS pin as follows:

  - Itsy-Bitsy M0/M4, Feather M0 (Express), Hallowing M0 Express, Zero, Metro M0 => use CS = 16 = pin A2
  - Feather M4 (SAMD51)   => use SS/CS = 9
  - Grand Central M4      => use SS/CS = 53
  - Hallowing M4          => use SS/CS = 10
  - Metro M4 AirLift      => use SS/CS = 36

To know the default CS/SS pins of not listed boards, check the related `variant.h` files in 

`~/.arduino15/packages/adafruit/hardware/samd/x.y.zz/variants/board_name/variant.h`

4. For **Arduino SAM DUE**, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = 75 ( pin 4 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_MISO  = 74 ( pin 1 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_SCK   = 76 ( pin 3 @ [ICSP connector](pics/ICSP_connector.jpg) )
  
<p align="center">
    <img src="https://github.com/khoih-prog/SinricPro_Generic/blob/master/pics/ICSP_connector.jpg">
</p>
  
---
---

## Full user documentation
Please see here for [**Full User Documentation**](https://sinricpro.github.io/esp8266-esp32-sdk)

---

## Examples

See [Many examples](https://github.com/khoih-prog/SinricPro_Generic/tree/master/examples) on GitHub


### Examples for ESP32/ESP8266

#### [ESP32/ESP8266 examples](https://github.com/khoih-prog/SinricPro_Generic/tree/master/examples/ESP)

 1. [AirQualitySensor](examples/ESP/AirQualitySensor)
 2. [AirQualitySensor_GP2Y1014AU0F](examples/ESP/AirQualitySensor_GP2Y1014AU0F)
 3. [Blinds](examples/ESP/Blinds)
 4. [Camera](examples/ESP/Camera)
 5. [ContactSensor](examples/ESP/ContactSensor)
 6. [DimSwitch](examples/ESP/DimSwitch)
 7. [DoorBell](examples/ESP/doorbell)
 8. [Fan](examples/ESP/Fan)
 9. [GarageDoor](examples/ESP/GarageDoor)
10. [Light](examples/ESP/Light/Light)
11. [**Light_FastLED_WS2812**](examples/ESP/Light/Light_FastLED_WS2812). New.
12. [**RGB_LED_Stripe_5050**](examples/ESP/Light/RGB_LED_Stripe_5050). New.
13. [Lock](examples/ESP/Lock/Lock)
14. [Lock_with_feedback](examples/ESP/Lock/Lock_with_feedback)
15. [MotionSensor](examples/ESP/MotionSensor)
16. [PowerSensor](examples/ESP/PowerSensor)
17. [Speaker](examples/ESP/Speaker)
18. [MultiSwitch_advance](examples/ESP/Switch/MultiSwitch_advance)
19. [MultiSwitch_beginner](examples/ESP/Switch/MultiSwitch_beginner)
20. [MultiSwitch_intermediate](examples/ESP/Switch/MultiSwitch_intermediate)
21. [Switch](examples/ESP/Switch/Switch)
22. [WeMosD1_mini_relay_shield](examples/ESP/Switch/WeMosD1_mini_relay_shield)
23. [TemperatureSensor](examples/ESP/temperaturesensor)
24. [Thermostat](examples/ESP/Thermostat)
25. [TV](examples/ESP/TV)

### Examples for Generic Boards (SAMD, nRF52, STM32, SAM DUE, etc.)

#### [Generic Boards examples](https://github.com/khoih-prog/SinricPro_Generic/tree/master/examples/Generic)

Each item is a directory containing many examples designed for different kinds of boards (SAMD, nRF52, STM32, SAM DUE, etc.) and shields/modules (Ethernet/WiFiNINA)

 1. [AirQualitySensor](examples/Generic/AirQualitySensor)
 2. [Blinds](examples/Generic/Blinds)
 3. [ContactSensor](examples/Generic/ContactSensor)
 4. [DimSwitch](examples/Generic/DimSwitch)
 5. [DoorBell](examples/Generic/DoorBell)
 6. [Fan](examples/Generic/Fan)
 7. [GarageDoor](examples/Generic/GarageDoor)
 8. [Light](examples/Generic/Light)
 9. [Lock](examples/Generic/Lock)
10. [MotionSensor](examples/Generic/MotionSensor)
11. [PowerSensor](examples/Generic/PowerSensor)
12. [Speaker](examples/Generic/Speaker)
13. [Generic_Ethernet_Switch](examples/Generic/Switch/Generic_Ethernet)
14. [Generic_WiFiNINA_Switch](examples/Generic/Switch/Generic_WiFiNINA)
15. [nRF52_Ethernet_Switch](examples/Generic/Switch/nRF52_Ethernet)
16. [nRF52_WiFiNINA_Switch](examples/Generic/Switch/nRF52_WiFiNINA)
17. [SAMD_Ethernet_Switch](examples/Generic/Switch/SAMD_Ethernet)
18. [SAMD_WiFiNINA_Switch](examples/Generic/Switch/SAMD_WiFiNINA)
19. [**WIO_Terminal**](examples/Generic/Switch/WIO_Terminal).                  <===== New from v2.7.4
20. [TemperatureSensor](examples/Generic/TemperatureSensor)
21. [Thermostat](examples/Generic/Thermostat)
22. [TV](examples/Generic/TV)

#### [Examples for WT32_ETH01](https://github.com/khoih-prog/SinricPro_Generic/tree/master/examples/WT32_ETH01)

 1. [Blinds](examples/WT32_ETH01/Blinds)
 2. [GarageDoor](examples/WT32_ETH01/GarageDoor)
 3. [Light](examples/WT32_ETH01/Light/Light)
 4. [**Light_FastLED_WS2812**](examples/WT32_ETH01/Light/Light_FastLED_WS2812).
 5. [**RGB_LED_Stripe_5050**](examples/WT32_ETH01/Light/RGB_LED_Stripe_5050).
 6. [Lock](examples/WT32_ETH01/Lock/Lock)
 7. [Lock_with_feedback](examples/WT32_ETH01/Lock/Lock_with_feedback)
 8. [MotionSensor](examples/WT32_ETH01/MotionSensor)
 9. [PowerSensor](examples/WT32_ETH01/PowerSensor)
10. [Speaker](examples/WT32_ETH01/Speaker)
11. [Switch](examples/WT32_ETH01/Switch/Switch)
12. [TemperatureSensor](examples/WT32_ETH01/temperaturesensor)
13. [Thermostat](examples/WT32_ETH01/Thermostat)
14. [TV](examples/WT32_ETH01/TV)


---
---

### HOWTO Usage

#### Include SinricPro-Library (SinricPro_Generic.h) and SinricPro-Device-Libraries (eg. SinricProSwitch.h)

```C++
#include <SinricPro_Generic.h>
#include <SinricProSwitch.h>
```

#### Define your credentials from SinricPro-Portal (portal.sinric.pro)

```C++
#define APP_KEY    "YOUR-APP-KEY"    // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET "YOUR-APP-SECRET" // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID  "YOUR-DEVICE-ID"  // Should look like "5dc1564130xxxxxxxxxxxxxx"
```

#### Define callback routine(s)

```C++
bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.printf("device %s turned %s\r\n", deviceId.c_str(), state?"on":"off");
  return true; // indicate that callback handled correctly
}
```

#### In setup()

```C++
  // create and add a switch to SinricPro
  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];
  // set callback function
  mySwitch.onPowerState(onPowerState);
  // startup SinricPro
  SinricPro.begin(APP_KEY, APP_SECRET);

```

#### In loop()

```C++
  SinricPro.handle();
```

---

### HOWTO Add a device

Syntax is

```C++
  DeviceType& myDevice = SinricPro[DEVICE_ID];
```

#### Example

```C++
  SinricProSwitch& mySwitch = SinricPro["YOUR-SWITCH-ID-HERE"];
```

#### Example 2 (alternatively)

```C++
  SinricProSwitch& mySwitch = SinricPro.add<SinricProSwitch>("YOUR-SWITCH-ID-HERE");
```

---

### How to retrieve a device for sending an event?

Syntax is

```C++
  DeviceType& myDevice = SinricPro[DEVICE_ID];
```

#### Example 1

```C++
  SinricProDoorbell& myDoorbell = SinricPro["YOUR-DOORBELL-ID-HERE"];
  myDoorbell.sendDoorbellEvent();
```

#### Example 2 (alternatively)
```C++
  SinricPro["YOUR-DOORBELL-ID-HERE"].as<SinricProDoorbell>().sendDoorbellEvent();
```

---
---

### Example [SAMD_WiFiNINA_Switch](examples/Generic/Switch/SAMD_WiFiNINA/SAMD_WiFiNINA_Switch)

Please take a look at other examples, as well.

#### 1. File [SAMD_WiFiNINA_Switch.ino](examples/Generic/Switch/SAMD_WiFiNINA/SAMD_WiFiNINA_Switch/SAMD_WiFiNINA_Switch.ino)

```cpp
// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0

#include "defines.h"

#include "SinricPro_Generic.h"
#include "SinricProSwitch.h"

bool myPowerState = false;
unsigned long lastBtnPress = 0;

/* bool onPowerState(String deviceId, bool &state)

   Callback for setPowerState request
   parameters
    String deviceId (r)
      contains deviceId (useful if this callback used by multiple devices)
    bool &state (r/w)
      contains the requested state (true:on / false:off)
      must return the new state

   return
    true if request should be marked as handled correctly / false if not
*/
bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.print("Device ");
  Serial.print(deviceId.c_str());
  Serial.print(state ? " turned on" : " turn off");
  Serial.println(" (via SinricPro)");
  
  myPowerState = state;
  digitalWrite(LED_PIN, myPowerState ? LOW : HIGH);
  return true; // request handled properly
}

void handleButtonPress() 
{
  unsigned long actualMillis = millis(); // get actual millis() and keep it in variable actualMillis
  if (digitalRead(BUTTON_PIN) == LOW && actualMillis - lastBtnPress > 1000)  
  { 
    // is button pressed (inverted logic! button pressed = LOW) and debounced?
    if (myPowerState) 
    {     
      // flip myPowerState: if it was true, set it to false, vice versa
      myPowerState = false;
    } 
    else 
    {
      myPowerState = true;
    }
    digitalWrite(LED_PIN, myPowerState ? LOW : HIGH); // if myPowerState indicates device turned on: turn on led (builtin led uses inverted logic: LOW = LED ON / HIGH = LED OFF)

    // get Switch device back
    SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];
    // send powerstate event
    mySwitch.sendPowerStateEvent(myPowerState); // send the new powerState to SinricPro server
    Serial.print("Device ");
    Serial.print(mySwitch.getDeviceId().toString());
    Serial.print(myPowerState ? "turned on" : "turn off");
    Serial.println(" (manually via flashbutton)");

    lastBtnPress = actualMillis;  // update last button press variable
  }
}

// setup function for WiFi connection
void setupWiFi() 
{
  Serial.println("\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) 
  {
     Serial.print(".");
    delay(250);
  }
  Serial.print("\n[WiFi]: IP-Address is ");
  Serial.println(WiFi.localIP());
}

// setup function for SinricPro
void setupSinricPro() 
{
  // add device to SinricPro
  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];

  // set callback function to device
  mySwitch.onPowerState(onPowerState);

  // setup SinricPro
  SinricPro.onConnected([]() 
  {
    Serial.println("Connected to SinricPro");
  });
  
  SinricPro.onDisconnected([]() 
  {
    Serial.println("Disconnected from SinricPro");
  });
  
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP); // GPIO 0 as input, pulled high
  pinMode(LED_PIN, OUTPUT); // define LED GPIO as output
  digitalWrite(LED_PIN, HIGH); // turn off LED on bootup

  Serial.begin(BAUD_RATE); 
  while (!Serial);
  
  Serial.println("\nStarting SAMD_WiFiNINA_Switch on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));
  
  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  handleButtonPress();
  SinricPro.handle();
}

```

---

#### 2. File [defines.h](examples/Generic/Switch/SAMD_WiFiNINA/SAMD_WiFiNINA_Switch/defines.h)

```cpp
#ifndef defines_h
#define defines_h

#define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA

#if defined(ESP8266) || defined(ESP32)
  #error This code is not intended to run on the ESP32/ESP8266 boards ! Please check your Tools->Board setting.
#endif

#define SRP_DEBUG_PORT                Serial

// Debug Level from 0 to 4
#define _SRP_LOGLEVEL_                1

// Uncomment the following line to enable serial debug output
#define ENABLE_DEBUG    true

#if ENABLE_DEBUG
  #define DEBUG_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(WIFININA_USE_SAMD)
    #undef WIFININA_USE_SAMD
  #endif
  #define WIFININA_USE_SAMD      true
  #endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(WIFININA_USE_NRF528XX)
    #undef WIFININA_USE_NRF528XX
  #endif
  #define WIFININA_USE_NRF528XX      true
#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(WIFININA_USE_SAM_DUE)
    #undef WIFININA_USE_SAM_DUE
  #endif
  #define WIFININA_USE_SAM_DUE      true
#endif

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #if defined(WIFININA_USE_STM32)
    #undef WIFININA_USE_STM32
  #endif
  #define WIFININA_USE_STM32        true
#endif

#if defined(WIFININA_USE_SAMD)
  // For SAMD
  
  #if ( defined(ARDUINO_SAMD_ZERO) && !defined(SEEED_XIAO_M0) )
    #define BOARD_TYPE      "SAMD Zero"
  #elif defined(ARDUINO_SAMD_MKR1000)
    #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
    #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
    #define BOARD_TYPE      "SAMD NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
    #define BOARD_TYPE      "SAMD MKRFox1200"
  #elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
    #define BOARD_TYPE      "SAMD MKRWAN13X0"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
    #define BOARD_TYPE      "SAMD MKRGSM1400"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
    #define BOARD_TYPE      "SAMD MKRNB1500"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
    #define BOARD_TYPE      "SAMD MKRVIDOR4000"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
    #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
  #elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_FEATHER_M0_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_METRO_M0_EXPRESS"
  #elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_CIRCUITPLAYGROUND_M0"
  #elif defined(ADAFRUIT_GEMMA_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_GEMMA_M0"
  #elif defined(ADAFRUIT_TRINKET_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_TRINKET_M0"
  #elif defined(ADAFRUIT_ITSYBITSY_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_ITSYBITSY_M0"
  #elif defined(ARDUINO_SAMD_HALLOWING_M0)
    #define BOARD_TYPE      "SAMD21 ARDUINO_SAMD_HALLOWING_M0"
  #elif defined(ADAFRUIT_METRO_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_EXPRESS"
  #elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_GRAND_CENTRAL_M4"
  #elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_FEATHER_M4_EXPRESS"
  #elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_TRELLIS_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYPORTAL)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL"
  #elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL_M4_TITANO"
  #elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_M4_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_AIRLIFT_LITE"
  #elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_AIRLIFT_M4"
  #elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_MONSTER_M4SK_EXPRESS"
  #elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_HALLOWING_M4_EXPRESS"
  #elif defined(SEEED_WIO_TERMINAL)
    #define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"
  #elif defined(SEEED_FEMTO_M0)
    #define BOARD_TYPE      "SAMD SEEED_FEMTO_M0"
  #elif defined(SEEED_XIAO_M0)
    #define BOARD_TYPE      "SAMD SEEED_XIAO_M0"
    #define USE_THIS_SS_PIN       A1
    #warning define SEEED_XIAO_M0 USE_THIS_SS_PIN == A1
  #elif defined(Wio_Lite_MG126)
    #define BOARD_TYPE      "SAMD SEEED Wio_Lite_MG126"
  #elif defined(WIO_GPS_BOARD)
    #define BOARD_TYPE      "SAMD SEEED WIO_GPS_BOARD"
  #elif defined(SEEEDUINO_ZERO)
    #define BOARD_TYPE      "SAMD SEEEDUINO_ZERO"
  #elif defined(SEEEDUINO_LORAWAN)
    #define BOARD_TYPE      "SAMD SEEEDUINO_LORAWAN"
  #elif defined(SEEED_GROVE_UI_WIRELESS)
    #define BOARD_TYPE      "SAMD SEEED_GROVE_UI_WIRELESS"
  #elif defined(__SAMD21E18A__)
    #define BOARD_TYPE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
    #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
    #define BOARD_TYPE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
    #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
    #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
    #define BOARD_TYPE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
    #define BOARD_TYPE      "CPU_ARC"
  #elif defined(__SAMD51__)
    #define BOARD_TYPE      "SAMD51"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

#elif (WIFININA_USE_SAM_DUE)
  #define BOARD_TYPE      "SAM DUE"

#elif (WIFININA_USE_NRF528XX)

  #if defined(NRF52840_FEATHER)
    #define BOARD_TYPE      "NRF52840_FEATHER"
  #elif defined(NRF52832_FEATHER)
    #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
    #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
    #define BOARD_TYPE      "NRF52840_ITSYBITSY"
  #elif defined(NRF52840_CIRCUITPLAY)
    #define BOARD_TYPE      "NRF52840_CIRCUITPLAY"
  #elif defined(NRF52840_CLUE)
    #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
    #define BOARD_TYPE      "NRF52840_METRO"
  #elif defined(NRF52840_PCA10056)
    #define BOARD_TYPE      "NRF52840_PCA10056"
  #elif defined(NINA_B302_ublox)
    #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(NINA_B112_ublox)
    #define BOARD_TYPE      "NINA_B112_ublox"
  #elif defined(PARTICLE_XENON)
    #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
    #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #else
    #define BOARD_TYPE      "nRF52 Unknown"
  #endif

#elif ( defined(CORE_TEENSY) )
  #if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #define BOARD_TYPE      "TEENSY 4.1/4.0"
  #elif defined(__MK66FX1M0__)
    #define BOARD_TYPE "Teensy 3.6"
  #elif defined(__MK64FX512__)
    #define BOARD_TYPE "Teensy 3.5"
  #elif defined(__MKL26Z64__)
    #define BOARD_TYPE "Teensy LC"
  #elif defined(__MK20DX256__)
    #define BOARD_TYPE "Teensy 3.2" // and Teensy 3.1 (obsolete)
  #elif defined(__MK20DX128__)
    #define BOARD_TYPE "Teensy 3.0"
  #elif defined(__AVR_AT90USB1286__)
    #error Teensy 2.0++ not supported yet
  #elif defined(__AVR_ATmega32U4__)
    #error Teensy 2.0 not supported yet
  #else
    // For Other Boards
    #define BOARD_TYPE      "Unknown Teensy Board"
  #endif

#elif (WIFININA_USE_STM32)
  #if defined(STM32F0)
    #define BOARD_TYPE  "STM32F0"
  #elif defined(STM32F1)
    #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)
    #define BOARD_TYPE  "STM32F7"
  #elif defined(STM32L0)
    #define BOARD_TYPE  "STM32L0"
  #elif defined(STM32L1)
    #define BOARD_TYPE  "STM32L1"
  #elif defined(STM32L4)
    #define BOARD_TYPE  "STM32L4"
  #elif defined(STM32H7)
    #define BOARD_TYPE  "STM32H7"
  #elif defined(STM32G0)
    #define BOARD_TYPE  "STM32G0"
  #elif defined(STM32G4)
    #define BOARD_TYPE  "STM32G4"
  #elif defined(STM32WB)
    #define BOARD_TYPE  "STM32WB"
  #elif defined(STM32MP1)
    #define BOARD_TYPE  "STM32MP1"
  #else
    #define BOARD_TYPE  "STM32 Unknown"
  #endif

#else
  // For Mega
  #define BOARD_TYPE      "AVR Mega"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include "WiFiNINA_Generic.h"

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 222);

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define SWITCH_ID         "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200                // Change baudrate to your need

#define BUTTON_PIN        0   // GPIO for BUTTON (inverted: LOW = pressed, HIGH = released)
#define LED_PIN           2   // GPIO for LED (inverted)
#endif    //defines_h
```

---
---

### Debug Terminal Output Samples

#### 1. [SAMD_WiFiNINA_TV](examples/Generic/TV/SAMD_WiFiNINA_TV) on NANO_33_IOT

This is the terminal output when running [SAMD_WiFiNINA_TV](examples/Generic/TV/SAMD_WiFiNINA_TV) on **NANO_33_IOT**

```
Starting SAMD_WiFiNINA_TV on SAMD NANO_33_IOT
Version : SinricPro_Generic (v2.8.3)
12 channels configured

[Wifi]: Connecting
WiFi-begin: return1 = 3
WiFi-begin: return2 = 3

[WiFi]: IP-Address is 192.168.2.46
Connected to SinricPro
TV turned off
TV turned on
Volume set to:  50
TV volume is unmuted
TV volume is muted
TV turned on
Volume set to:  65
TV turned on
MediaControl: play
MediaControl: pause
TV turned off
TV turned on
TV turned on
TV volume is unmuted
TV turned off
```
---

#### 2. [SAMD_WiFiNINA_Light](examples/Generic/Light/SAMD_WiFiNINA_Light) on NANO_33_IOT

This is the terminal output when running [SAMD_WiFiNINA_Light](examples/Generic/Light/SAMD_WiFiNINA_Light) on **NANO_33_IOT**


```
Starting SAMD_WiFiNINA_Light on SAMD NANO_33_IOT
Version : SinricPro_Generic (v2.8.3)
Setup color temperature lookup table
colorTemperatureIndex[2200] = 0
colorTemperatureIndex[2700] = 1
colorTemperatureIndex[4000] = 2
colorTemperatureIndex[5500] = 3
colorTemperatureIndex[7000] = 4

[Wifi]: ConnectingWiFi-begin: return1 = 3
WiFi-begin: return2 = 3
[WiFi]: IP-Address is 192.168.2.46
Connected to SinricPro
Device **** turned on (via SinricPro)
Device **** turn off (via SinricPro)
Device **** brightness level changed to 70
Device **** brightness level changed to 25
Device **** color changed to 160, 112, 112(RGB)
Device **** color changed to 218, 23, 23(RGB)
Device **** color changed to 236, 214, 214(RGB)
Device **** turn off (via SinricPro)
Device **** turned on (via SinricPro)
Device**** brightness level changed to 65
```

---

#### 3. [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on nRF52 NRF52840_ITSYBITSY with W5500 Ethernet

This is the terminal output when running terminal output when running [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on **nRF52 NRF52840_ITSYBITSY** with W5500 Ethernet using "patched" Ethernet2 Library


```
Starting Generic_Ethernet_Blinds on NRF52840_ITSYBITSY
Version : SinricPro_Generic (v2.8.3)
[SRP] =========== USE_ETHERNET2 ===========
[SRP] Default SPI pinout:
[SRP] MOSI: 24
[SRP] MISO: 23
[SRP] SCK: 25
[SRP] SS: 5
[SRP] =========================
[SRP] Use default CS/SS pin :  10
Index = 0
Ethernet Connected!. IP-Address is: 192.168.2.165
[SRP] Creating new device. No Device=  _deviceID
[SRP] add(): Adding device with id=  _deviceID
[SRP] Websocket: Connecting to WebSocket Server:  ws.sinric.pro
[SRP] Websocket: headers:
 appkey:APP_KEY
deviceids:_deviceID
restoredevicestates:false
ip:192.168.2.165
mac:DE:AD:BE:EF:FE:01
platform:NRF52840_ITSYBITSY
version:2.5.1
[SRP] Websocket: connected
Connected to SinricPro
[SRP] Websocket: receiving data
[SRP] handleReceiveQueue(): Message(s) in receiveQueue=  1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp=  1596497923
```

---

#### 4. [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on Seeeduino SEEED_XIAO_M0 with W5500 Ethernet

This is the terminal output when running terminal output when running [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on **Seeeduino SEEED_XIAO_M0** with W5500 Ethernet using "patched" Ethernet3 Library


```
Starting Generic_Ethernet_Blinds on SEEED_XIAO_M0
Version : SinricPro_Generic (v2.8.3)
[SRP] =========== USE_ETHERNET3 ===========
[SRP] Default SPI pinout:
[SRP] MOSI: 10
[SRP] MISO: 9
[SRP] SCK: 8
[SRP] SS: 4
[SRP] =========================
[SRP] Use default CS/SS pin :  1
Index = 11

Ethernet3 W5500 init, using SPI_CS = 1, number of sockets = 4
Ethernet Connected!. IP-Address is: 192.168.2.164
[SRP] Creating new device. No Device=  _deviceID
[SRP] add(): Adding device with id=  _deviceID
[SRP] Websocket: Connecting to WebSocket Server:  ws.sinric.pro
[SRP] Websocket: headers:
 appkey:APP_KEY
deviceids:_deviceID
restoredevicestates:false
ip:192.168.2.164
mac:DE:AD:BE:EF:BE:0C
platform:SEEED_XIAO_M0
version:2.5.1
[SRP] Websocket: connected
Connected to SinricPro
[SRP] Websocket: receiving data
[SRP] handleReceiveQueue(): Message(s) in receiveQueue=  1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp=  1596499807
```
---

#### 5. [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on Arduino SAMD_NANO_33_IOT with WiFiNINA

This is the terminal output when running terminal output when running [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on **Arduino SAMD_NANO_33_IOT** with WiFiNINA using "patched" `Arduino.h`


```
Starting SAMD_WiFiNINA_Blinds on SAMD_NANO_33_IOT
Version : SinricPro_Generic (v2.8.3)
[Wifi]: Connecting[WiFi]: IP-Address is 192.168.2.105
[SRP] Creating new device. No Device=  _deviceID
[SRP] add(): Adding device with id=  _deviceID
[SRP] Websocket: Connecting to WebSocket Server:  ws.sinric.pro
[SRP] Websocket: headers:
 appkey:APP_KEY
deviceids:_deviceID
restoredevicestates:false
ip:192.168.2.105
mac:74:7A:C9:AE:11:4C
platform:SAMD_NANO_33_IOT
version:2.5.1
[SRP] Websocket: connected
Connected to SinricPro
[SRP] Websocket: receiving data
[SRP] handleReceiveQueue(): Message(s) in receiveQueue=  1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp=  1596518895

```

---

#### 6. [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on Adafruit nRF52 NRF52840_FEATHER with W5500 Ethernet 

This is the terminal output when running terminal output when running [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on **Adafruit nRF52 NRF52840_FEATHER** with W5500 Ethernet using EthernetLarge Library with (_SRP_LOGLEVEL_ = 3)


```
Starting Generic_Ethernet_Blinds on NRF52840_FEATHER
Version : SinricPro_Generic (v2.8.3)
[SRP] =========== USE_ETHERNET_LARGE ===========
[SRP] Default SPI pinout:
[SRP] MOSI: 25
[SRP] MISO: 24
[SRP] SCK: 26
[SRP] SS: 5
[SRP] =========================
[SRP] Use default CS/SS pin :  10
Index = 6
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =8192
Connected!
[Ethernet]: IP-Address is 192.168.2.97
[SRP] Creating new device. No Device = 123456789012345678901234
[SRP] add(): Adding DeviceId = 123456789012345678901234
[SRP] begin(): App-Key = 12345678-1234-1234-1234-123456789012
[SRP] begin(): App-Secret = 12345678-1234-1234-1234-123456789012-12345678-1234-1234-1234-123456789012
[SRP] Websocket: Connecting to WebSocket Server:  ws.sinric.pro
Websocket: headers:
appkey:12345678-1234-1234-1234-123456789012
deviceids:123456789012345678901234
restoredevicestates:false
ip:192.168.2.87
mac:DE:AD:BE:EF:FE:0B
platform:NRF52840_FEATHER
version:2.7.0
Connected to SinricPro
[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1601877066
[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1601877184
[SRP] handleRequest(): handling request
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1601877184,
    "deviceAttributes": [],
    "deviceId": "123456789012345678901234",
    "replyToken": "1068f321-1ad6-4750-a089-f73e56502044",
    "type": "request",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "/3hvMknpWRtzgNcD41s94YMLzPrA/gj1BIUihcRajjk="
  }
}
Device 123456789012345678901234 power turned off
[SRP] handleSendQueue(): Sending Number of Message(s) in sendQueue = 1
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1601877184,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "1068f321-1ad6-4750-a089-f73e56502044",
    "success": true,
    "type": "response",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "DS4Lby1xXXiM7OBe3cphs2G+1HaN6Z9T8crcRRA4avc="
  }
}
[SRP] handleSendQueue: Sending to WebSocket
[SRP] handleSendQueue(): Message sent.

```

---

#### 7. [Generic_Ethernet_Blinds](examples/Generic/Speaker/Generic_Ethernet_Speaker) on STM32F7 Nucleo-144 NUCLEO_F767ZI with W5500 Ethernet

This is the terminal output when running terminal output when running [Generic_Ethernet_Blinds](examples/Generic/Speaker/Generic_Ethernet_Speaker) on **STM32F7 Nucleo-144 NUCLEO_F767ZI** with W5500 Ethernet using Ethernet2 Library with (_SRP_LOGLEVEL_ = 3)


```
Starting Generic_Ethernet_Speaker on NUCLEO_F767ZI
Version : SinricPro_Generic (v2.8.3)
Index = 0
Connected!
[Ethernet]: IP-Address is 192.168.2.84
[SRP] Creating new device. No current DeviceId = 123456789012345678901234
[SRP] add(): Adding DeviceId = 123456789012345678901234
[SRP] begin(): App-Key = 12345678-1234-1234-1234-123456789012
[SRP] begin(): App-Secret = 12345678-1234-1234-1234-123456789012-12345678-1234-1234-1234-123456789012
[SRP] Websocket: Connecting to WebSocket Server:  ws.sinric.pro
Websocket: headers:
appkey:12345678-1234-1234-1234-123456789012
deviceids:123456789012345678901234
restoredevicestates:false
ip:192.168.2.84
mac:DE:AD:BE:EF:FE:01
platform:NUCLEO_F767ZI
version:2.7.0
Connected to SinricPro

[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1601879732
[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1601879782
[SRP] handleRequest(): handling request
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setVolume",
    "clientId": "sinricpro-web",
    "createdAt": 1601879782,
    "deviceAttributes": [],
    "deviceId": "123456789012345678901234",
    "replyToken": "7c989b3f-84aa-4462-8f3d-1a29c04c7df0",
    "type": "request",
    "value": {
      "volume": 45
    }
  },
  "signature": {
    "HMAC": "J27eUYEZJ+pQyzG5uC1+w/2jz8SKGU4LcP5snSb0KF4="
  }
}
Volume set to: 45
[SRP] handleSendQueue(): Sending Number of Message(s) in sendQueue = 1
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setVolume",
    "clientId": "sinricpro-web",
    "createdAt": 1601879782,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "7c989b3f-84aa-4462-8f3d-1a29c04c7df0",
    "success": true,
    "type": "response",
    "value": {
      "volume": 45
    }
  },
  "signature": {
    "HMAC": "mYoFZxZ//yKd3BU/TWs56rKoM+lcdZsxVs1ql0/1XM4="
  }
}
[SRP] handleSendQueue: Sending to WebSocket
[SRP] handleSendQueue(): Message sent.
[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1601879790
[SRP] handleRequest(): handling request
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1601879790,
    "deviceAttributes": [],
    "deviceId": "123456789012345678901234",
    "replyToken": "0069ff67-31ee-4e6e-a647-a054617a2061",
    "type": "request",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "kx6ZtXl1DUNMIXCmlcBO5ni8NN9w1CLaM8hSIESM9fM="
  }
}
Speaker turned off
[SRP] handleSendQueue(): Sending Number of Message(s) in sendQueue = 1
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1601879790,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "0069ff67-31ee-4e6e-a647-a054617a2061",
    "success": true,
    "type": "response",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "qiI38SI0ulIJKXR/R/Zm9n6Uhd3HlNmX2vto9DkDah8="
  }
}
[SRP] handleSendQueue: Sending to WebSocket
[SRP] handleSendQueue(): Message sent.
[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1601879793
[SRP] handleRequest(): handling request
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1601879793,
    "deviceAttributes": [],
    "deviceId": "123456789012345678901234",
    "replyToken": "d4d1d50c-9c44-40fa-943c-84c40c0d7550",
    "type": "request",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "49poW0mpG3CZUs8UJ48EF6eAw8mz09jcfGRy2Xob86w="
  }
}
Speaker turned on
[SRP] handleSendQueue(): Sending Number of Message(s) in sendQueue = 1
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1601879793,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "d4d1d50c-9c44-40fa-943c-84c40c0d7550",
    "success": true,
    "type": "response",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "msDcqzA0tGgzJOB0uAeaiIEFvPSQ3ACTZPmk+lMty5o="
  }
}
[SRP] handleSendQueue: Sending to WebSocket
[SRP] handleSendQueue(): Message sent.

```

---

#### 8. [WIOT_MultiSwitch_LCD](examples/Generic/Switch/WIO_Terminal/WIOT_MultiSwitch_LCD) on SeeedStudio SAMD51 WIO Terminal

This is the terminal output when running terminal output when running [WIOT_MultiSwitch_LCD](examples/Generic/Switch/WIO_Terminal/WIOT_MultiSwitch_LCD) on **SeeedStudio SAMD51 WIO Terminal** with (_SRP_LOGLEVEL_ = 3)


```
Starting WIOT_MultiSwitch_LCD on WIO_TERMINAL
Version : SinricPro_Generic (v2.8.3)
[Wifi]: Connecting

[WiFi]: IP-Address is 192.168.2.150
Connected to SinricPro
SinricPro Connected
isSinricConnected Connected
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1606952787,
    "deviceAttributes": [],
    "deviceId": "5ec47b****************",
    "replyToken": "bbab5988-ffae-45ca-b1c2-fb13be4d0a48",
    "type": "request",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "efnmLaucg7UvjHSZiUyv9U1pzbTJqwgBPnX+yziNPAg="
  }
}
=======================================
Device 1 turned ON
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1606952787,
    "deviceId": "5ec47b****************",
    "message": "OK",
    "replyToken": "bbab5988-ffae-45ca-b1c2-fb13be4d0a48",
    "success": true,
    "type": "response",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "O0Hc0p2sxD5FzbOPCmw+Ex9NnjVxkMDo9HkNicChoZU="
  }
}
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1606952787,
    "deviceAttributes": [],
    "deviceId": "5ec47b****************",
    "replyToken": "be743078-60ad-4eb8-a6f8-05b13e9509c5",
    "type": "request",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "a9E1hS2dY7GDE+KCLZFXhcaMwZtMk5YH7yvsVDsPmoQ="
  }
}
=======================================
Device 3 turned ON
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1606952787,
    "deviceId": "5ec47b****************",
    "message": "OK",
    "replyToken": "be743078-60ad-4eb8-a6f8-05b13e9509c5",
    "success": true,
    "type": "response",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "NouzX0HUbxAh2/ATHPMpqMrKGfydHEFScu7cU7Qboec="
  }
}
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1606952787,
    "deviceAttributes": [],
    "deviceId": "5ec47b****************",
    "replyToken": "dcbe67e7-6add-44b9-820c-955c7efab625",
    "type": "request",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "d2T7p0jEUbm0jLs8GOTmqvwpkwSBA27q0UhAVjZ7v28="
  }
}
=======================================
Device 2 turned ON
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "sinricpro-web",
    "createdAt": 1606952787,
    "deviceId": "5ec47b****************",
    "message": "OK",
    "replyToken": "dcbe67e7-6add-44b9-820c-955c7efab625",
    "success": true,
    "type": "response",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "kFuxIwc5RZr1xAs5oLK66r1dYl4YrbDUcxS804cWQ+k="
  }
}
Device 1 with deviceID :5ec47b9276b86a477f5df3d0turned OFF (manually via flashbutton)
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "cause": {
      "type": "PHYSICAL_INTERACTION"
    },
    "createdAt": 1606952915,
    "deviceId": "5ec47b****************",
    "replyToken": "fc3e0648-7535-4765-85b4-f054bc3b2f01",
    "type": "event",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "0A0OmM/2k6AtUhfb3358c2rohjVHQKOVpu/qid7+A7U="
  }
}
```

and the LCD screenshots

<p align="center">
    <img src="https://github.com/khoih-prog/SinricPro_Generic/blob/master/examples/Generic/Switch/WIO_Terminal/WIOT_MultiSwitch_LCD/WIOT_MultiSwitch_LCD_1.jpg">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/SinricPro_Generic/blob/master/examples/Generic/Switch/WIO_Terminal/WIOT_MultiSwitch_LCD/WIOT_MultiSwitch_LCD_2.jpg">
</p>


---

#### 9. [Generic_WiFiNINA_Blinds](examples/Generic/Blinds/Generic_WiFiNINA_Blinds) on MBED NANO_RP2040_CONNECT

This is the terminal output when running terminal output when running [Generic_WiFiNINA_Blinds](examples/Generic/Blinds/Generic_WiFiNINA_Blinds) on **Arduino MBED NANO_RP2040_CONNECT**


```
Starting Generic_WiFiNINA_Blinds on MBED NANO_RP2040_CONNECT
Version : SinricPro_Generic (v2.8.3)

[Wifi]: Connecting[WiFi]: IP-Address is 192.168.2.153
Connected to SinricPro
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1622610381,
    "deviceId": "123456789012345678901234",
    "replyToken": "cef0abba-0fe3-44c1-9fad-426766e4c23e",
    "type": "request",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "CBksKuwCU3WagwFP0xyqmUqnaEl1+PI91OvBwQnt7pw="
  }
}Device 123456789012345678901234 power turned on
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1622610381,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "cef0abba-0fe3-44c1-9fad-426766e4c23e",
    "success": true,
    "type": "response",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "0TTkm+eAa/QmnkiF1239idHJS/uYcwhWVmGQ+Yo+7Ag="
  }
}
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1622610383,
    "deviceId": "123456789012345678901234",
    "replyToken": "059fa67e-1ecb-4378-8c49-83693441d9b6",
    "type": "request",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "fx7mxcIADdO7/l/HnfiZtUwya+nC0B1+mXSKwIOevMs="
  }
}Device 123456789012345678901234 power turned off
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1622610383,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "059fa67e-1ecb-4378-8c49-83693441d9b6",
    "success": true,
    "type": "response",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "/LQtlMLeej6ev665US/o+USwaV/3lx81KX+AhHa/+Yw="
  }
}
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setRangeValue",
    "clientId": "portal",
    "createdAt": 1622610386,
    "deviceId": "123456789012345678901234",
    "replyToken": "5e986c43-da36-40e0-83f7-a8ec4d4cac9f",
    "type": "request",
    "value": {
      "rangeValue": 100
    }
  },
  "signature": {
    "HMAC": "VPDM+vx74ILz0OzKdjhKDr/E31s6Zztg/UrZgKLf+5w="
  }
}Device 123456789012345678901234 set position to 100
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setRangeValue",
    "clientId": "portal",
    "createdAt": 1622610386,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "5e986c43-da36-40e0-83f7-a8ec4d4cac9f",
    "success": true,
    "type": "response",
    "value": {
      "rangeValue": 100
    }
  },
  "signature": {
    "HMAC": "hrmCNpSS8X90FPmmJE86tHWYfCTqIpIGNE7JFoTpdVY="
  }
}
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setRangeValue",
    "clientId": "portal",
    "createdAt": 1622610388,
    "deviceId": "123456789012345678901234",
    "replyToken": "b3af6342-bf52-4a7a-8919-c318bf9b9b3f",
    "type": "request",
    "value": {
      "rangeValue": 0
    }
  },
  "signature": {
    "HMAC": "oaAgz3MT50kVviDcqLyanwiNuZ/KVTslMSncg9veDnA="
  }
}Device 123456789012345678901234 set position to 0
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setRangeValue",
    "clientId": "portal",
    "createdAt": 1622610388,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "b3af6342-bf52-4a7a-8919-c318bf9b9b3f",
    "success": true,
    "type": "response",
    "value": {
      "rangeValue": 0
    }
  },
  "signature": {
    "HMAC": "HT6U+Q+rfdeE6lzqdUAtehOexNi5us17B5j1FKHS1dM="
  }
}
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setRangeValue",
    "clientId": "portal",
    "createdAt": 1622610394,
    "deviceId": "123456789012345678901234",
    "replyToken": "059e38ca-fce5-4188-99ab-7dba8863cb4f",
    "type": "request",
    "value": {
      "rangeValue": 40
    }
  },
  "signature": {
    "HMAC": "7Nz3oiW+zHVtNh8gokRHzNGdYu/Y7F4beJkAfJpgGGg="
  }
}Device 123456789012345678901234 set position to 40
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setRangeValue",
    "clientId": "portal",
    "createdAt": 1622610394,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "059e38ca-fce5-4188-99ab-7dba8863cb4f",
    "success": true,
    "type": "response",
    "value": {
      "rangeValue": 40
    }
  },
  "signature": {
    "HMAC": "nV7UpnelVTTWMrYJvBZBhnd2zV3tEOanhseYVeQcIMA="
  }
}
```

---

#### 10. [RP2040_WiFiNINA_Blinds](examples/Generic/Blinds/RP2040_WiFiNINA_Blinds) on MBED NANO_RP2040_CONNECT

This is the terminal output when running terminal output when running [Generic_WiFiNINA_Blinds](examples/Generic/Blinds/RP2040_WiFiNINA_Blinds) on **Arduino MBED NANO_RP2040_CONNECT**


```
Starting RP2040_WiFiNINA_Blinds on MBED NANO_RP2040_CONNECT
Version : SinricPro_Generic (v2.8.3)

[Wifi]: Connecting[WiFi]: IP-Address is 192.168.2.153
[SRP] Creating new device. No current DeviceId = 123456789012345678901234
[SRP] add(): Adding DeviceId = 123456789012345678901234
[SRP] begin(): App-Key = 12345678-1234-1234-1234-123456789012
[SRP] begin(): App-Secret = 12345678-1234-1234-1234-123456789012-12345678-1234-1234-1234-123456789012
[SRP] Websocket: Connecting to WebSocket Server:  ws.sinric.pro
Websocket: headers:
appkey:12345678-1234-1234-1234-123456789012
deviceids:123456789012345678901234
restoredevicestates:false
ip:192.168.2.153
mac:98:1F:2E:A8:CC:84
platform:MBED NANO_RP2040_CONNECT
version:2.8.0
Connected to SinricPro
[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1622609861
[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1622609961
[SRP] handleRequest(): handling request
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1622609961,
    "deviceId": "123456789012345678901234",
    "replyToken": "d2b469d3-aa7a-4fe8-a726-21f64fbf838e",
    "type": "request",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "4S+9TcRml7dUdapV9tbJnMmqz/bm7MTe4Kfqyo2bnjs="
  }
}
Device 123456789012345678901234 power turned on
[SRP] handleSendQueue(): Sending Number of Message(s) in sendQueue = 1
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1622609961,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "d2b469d3-aa7a-4fe8-a726-21f64fbf838e",
    "success": true,
    "type": "response",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "0Wfn7ozGRg1h3LlN+m+2x5c5XZNOl0akoYR8NlAX+fo="
  }
}
[SRP] handleSendQueue: Sending to WebSocket
[SRP] handleSendQueue(): Message sent.
[SRP] handleReceiveQueue(): Message(s) in receiveQueue = 1
[SRP] handleReceiveQueue(): Valid Signature. Processing message...
[SRP] extractTimestamp(): Got Timestamp = 1622609963
[SRP] handleRequest(): handling request
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1622609963,
    "deviceId": "123456789012345678901234",
    "replyToken": "22bb0f44-15d7-41ca-9df1-4411bad86d47",
    "type": "request",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "Di8m+/krnAZOGKvvLYVII07pwIWhzkY2auXfQNd1Ta0="
  }
}
Device 123456789012345678901234 power turned off
[SRP] handleSendQueue(): Sending Number of Message(s) in sendQueue = 1
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1622609963,
    "deviceId": "123456789012345678901234",
    "message": "OK",
    "replyToken": "22bb0f44-15d7-41ca-9df1-4411bad86d47",
    "success": true,
    "type": "response",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "LknB4L8yaPbDeVSEAfZ6bg16RcPELGScuBAiuOEGLnU="
  }
}
[SRP] handleSendQueue: Sending to WebSocket
[SRP] handleSendQueue(): Message sent.
```

---

#### 11. [Blinds](examples/WT32_ETH01/Blinds) on WT32-ETH01 with ETH_PHY_LAN8720

This is the terminal output when running terminal output when running [Blinds](examples/WT32_ETH01/Blinds) on **WT32-ETH01 with ETH_PHY_LAN8720**

```
Start Blinds on WT32-ETH01 with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.2.0
SinricPro_Generic (v2.8.3)
[ETH]: Connecting
ETH Started
ETH Connected
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.83
FULL_DUPLEX, 100Mbps
[ETH]: IP-Address is 192.168.2.83
Connected to SinricPro
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1626752759,
    "deviceId": "device-id",
    "replyToken": "ab499dd7-9846-4944-814e-21262e645809",
    "type": "request",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "i4exN7P/ScPsul8Cdn2hQa0hZ49zw6nc7TTwiKEVeYw="
  }
}Device device-id power turned on 
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1626752759,
    "deviceId": "device-id",
    "message": "OK",
    "replyToken": "ab499dd7-9846-4944-814e-21262e645809",
    "success": true,
    "type": "response",
    "value": {
      "state": "On"
    }
  },
  "signature": {
    "HMAC": "3V/YzNA6AjgAj97QlRUguJijMXtlTjq/KQyViulRPrs="
  }
}
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1626752762,
    "deviceId": "device-id",
    "replyToken": "86d11bc3-1711-48ca-8bdd-f4df119f02f2",
    "type": "request",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "UrmmYfZM0xcpVg20vVeh0/rdj1hs9K7B93Ge4ZmgYYE="
  }
}Device device-id power turned off 
{
  "header": {
    "payloadVersion": 2,
    "signatureVersion": 1
  },
  "payload": {
    "action": "setPowerState",
    "clientId": "portal",
    "createdAt": 1626752762,
    "deviceId": "device-id",
    "message": "OK",
    "replyToken": "86d11bc3-1711-48ca-8bdd-f4df119f02f2",
    "success": true,
    "type": "response",
    "value": {
      "state": "Off"
    }
  },
  "signature": {
    "HMAC": "gHrceMstnanDVixoRloVFalZREux+8CF9q6SnXn4F8Q="
  }
}
```

---
---

### Devices

* Switch
* Dimmable Switch
* Light
* TV
* Speaker
* Thermostat
* Fan (US and non US version)
* Lock
* DoorBell
* TemperatureSensor
* MotionSensor
* ContactSensor
* Windows Air Conditioner
* Interior Blinds
* Garage Door
* Camera (from v2.5.1)
* AirQualitySensor (from v2.6.1)


---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _SRP_LOGLEVEL_ to 0

```cpp
#define SRP_DEBUG_PORT                Serial

// Debug Level from 0 to 4
#define _SRP_LOGLEVEL_                4
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Libraries' Patches, Packages' Patches or this library latest version.

---
---


### Issues

Submit issues to: [**SinricPro_Generic issues**](https://github.com/khoih-prog/SinricPro_Generic/issues)

---
---

### TO DO

1. Bug Searching and Killing
2. Support more types of new boards
3. Support more types of Ethernet modules/shields, such as **LAN8742A, LAN8720, etc.**
4. Support more types of WiFi modules/shields, such as WiFi101, **ESP8266-AT, ESP32-AT**
5. Support **GSM/GPRS** modules/shields.
6. Support ENC28J60 Ethernet modules/shields, using new [EthernetENC](https://github.com/jandrassy/EthernetENC) library.

### DONE

 1. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 2. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
 3. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.)**.
 4. Add support to SAM DUE.
 5. Add support to Teensy.
 6. Add support to all **STM32F/L/H/G/WB/MP1 having 64K+ Flash program memory.**
 7. Add support to **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
 8. Add support to **W5x00, ENC28J60** Ethernet modules/shields.
 9. Add support to **Ethernet, EthernetLarge, Ethernet2, Ethernet3, UIPEthernet** libraries.
10. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
11. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)
12. Add support to **Arduino Nano RP2040 Connect** using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).
13. Add `Table of Contents`
14. Add support to **WT32_ETH01 boards** using ESP32-based boards and LAN8720 Ethernet

---

### Contributions and Thanks

1. Based on and modified from [Boris Jaeger's](https://github.com/sivar2311) [**SinricPro library**](https://github.com/sinricpro/esp8266-esp32-sdk) which is written for only ESP8266 and ESP32. 
2. Also thanks to the good [**Sinric**](https://sinric.com)/[**SinricPro**](https://sinric.pro) platform of [Aruna Tennakoon](https://github.com/kakopappa)
3. Thanks to good work of [Miguel Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially **U-Blox B302 running as nRF52840 and U-Box B112 running as nRF52832**, has never been started and finished.

<table>
  <tr>
    <td align="center"><a href="https://github.com/sivar2311"><img src="https://github.com/sivar2311.png" width="100px;" alt="sivar2311"/><br /><sub><b>⭐️ Boris Jaeger</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/kakopappa"><img src="https://github.com/kakopappa.png" width="100px;" alt="kakopappa"/><br /><sub><b>⭐️ Aruna Tennakoon</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>Miguel Wisintainer</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- Most of the credits go to original author [**Boris Jaeger**](https://github.com/sivar2311).

- The library is licensed under [CC-BY-SA](https://creativecommons.org/licenses/by/2.0/) and [MIT](https://github.com/khoih-prog/SinricPro_Generic/blob/master/LICENSE)

---

### Copyright

Copyright 2020- Boris Jaeger, Khoi Hoang

