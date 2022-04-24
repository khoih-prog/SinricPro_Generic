# SinricPro_Generic


[![arduino-library-badge](https://www.ardu-badge.com/badge/SinricPro_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/SinricPro_Generic.svg)](https://github.com/khoih-prog/SinricPro_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/SinricPro_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/SinricPro_Generic.svg)](http://github.com/khoih-prog/SinricPro_Generic/issues)

---
---

## Table of Contents


* [Changelog](#changelog)
  * [Version 2.8.5](#Version-285)
  * [Version 2.8.4](#Version-284)
  * [Version 2.8.3](#Version-283)
  * [Version 2.8.2](#Version-282)
  * [Version 2.8.0](#Version-280)
  * [Version 2.7.4](#Version-274)
  * [Version 2.7.0](#Version-270)
  * [Version 2.6.1](#Version-261)
  * [Version 2.6.0](#Version-260)
  * [Version 2.5.0](#Version-250)
  * [Version 2.4.0](#Version-240)
  * [Version 2.3.0](#Version-230)
  * [Version 2.2.7](#Version-227)
  * [Version 2.2.6](#Version-226)
  * [Version 2.2.5](#Version-225)
  * [Version 2.2.4](#Version-224)
  * [Version 2.2.3](#Version-223)
  * [Version 2.2.2](#Version-222)
  * [Version 2.2.1](#Version-221)
  * [Version 2.2.0](#Version-220)
  * [Version 2.1.1](#Version-211)
  * [Version 2.1.0](#Version-210)
  * [Version 2.0.5](#Version-205)
  * [Version 2.0.4](#Version-204)
  * [Version 2.0.2](#Version-202) 
  
---
---


# Changelog

## Version 2.8.5

1. Use [Ethernet_Generic](https://github.com/khoih-prog/Ethernet_Generic) library as default for W5x00 Ethernet.
2. Add support to Portenta_H7
3. Add support to WIZNet W5100S, such as  [**WIZnet Ethernet HAT**](https://docs.wiznet.io/Product/Open-Source-Hardware/wiznet_ethernet_hat) and [**W5100S-EVB-Pico**](https://docs.wiznet.io/Product/iEthernet/W5100S/w5100s-evb-pico)
4. Update `Packages' Patches`

## Version 2.8.4

1. Auto detect ESP32 core version.
2. Fix bug in examples for WT32_ETH01
3. Update `Packages' Patches`

## Version 2.8.3

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

## Version 2.8.2

1. Add support to WT32_ETH01 (ESP32 + LAN8720A) using WEBSOCKET_SSL or not

## Version 2.8.1

1. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
2. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico) using LittleFS

## Version 2.8.0

- Removed QueueList.h and use std::queue instead

- Many new Examples 
  - examples / Light / RGB_LED_Stripe_5050
  - examples / Light / Light_FastLED_WS2812
- 

  
## Version 2.7.4

- Add support and many new examples for SeeedStudio WIO Terminal

- New
  - Speaker & TV `onAdjustVolume` callback changed:
    The new format is `bool onAdjustVolume(const String &deviceId, int &volumeDelta, bool volumeDefault);`
    `volumeDefault`: `false` if the user specified the amount by which to change the volume; otherwise `true`

- Fixed
  - `.c_str()` for AppKey, AppSecret and DeviceId return now a valid `const char*`
  - Switch example
    `SinricProDevice.getDeviceId()` returns `SinricProId` instead of `char*` since version 2.7.0

## Version 2.7.0
New:
- Added new classes for AppKey, AppSecret and DeviceId
  This allows to store credentials efficiently in EEPROM and reduces the internal RAM usage
  
- Added function to measure the RTT between device and SinricPro Server (SinricPro.onPong())

Fixed:
- Type mismatches in Crypto.h / Crypto.cpp (to reduce compiler warnings)

## Version 2.6.1
Fixed:
  Air Quality Sensor example for sensor type GP2Y1014AU0F

## Version 2.6.0
New:
- Devices
  - AirQualitySensor
	
- Examples
  - AirQualitySensor

Changed:
  - SinricProCamera device type added to support Camera. Camera example updated

## Version 2.5.0
New:
- Devices
  - Camera

- Examples
  -  Camera

## Version 2.4.0
New:
- Devices
  - PowerSensor

- Examples
  -  PowerSensor

## Version 2.3.0
New:
- Devices
  - Blinds
  - GarageDoor

- Examples
  - Thermostat
  - Blinds
  - GarageDoor

## Version 2.2.7

New:
- Examples
  - Dimmable Switch
  - Light
  - Speaker

Updated:
- User documentation
  - added SinricPro.onConnected() / SinricPro.onDisconnected()

Fixed:
- Examples
  - Some examples didn't use BAUD_RATE

## Version 2.2.6

New:
- User Documentation using Doxygen available at https://sinricpro.github.io/esp8266-esp32-sdk

Fixed: 
- Some sendEvent functions didn't return `true`/`false`
- Arduino TV example

## Version 2.2.5

New:
- Added new `callback` for TV `onChangeChannelNumber`
  This is to support changing channels using a
  channel number instead of channel name.
- New TV Example
- Added this `changelog.md`

Fixed: 
- Some sendEvent functions didn't return `true`/`false`
- Fixed json in `skipChannels` response
- Fixed json in `sendChangeChannels` event

Updated Readme
- about return values of sendEvent functions
  
---

## Version 2.2.4 

New:
- Added example for `SinricProTemperaturesensor`

Bugfix:
- Fixed typo in `onTargetTemperature` event

---

## Version 2.2.3

New :
- Added GarageDoorExample (ArudinoIDE) including wiring diagram
  This is based on `SinricProLock` device

Code optimizations:
- Changed callbacks to use `const String&` in callback functions
  to avoid unnecessary string copying
- Changed event limitiation to prevent server flooding

---

## Version 2.2.2

New Feature:
- `SinricPro.setResponseMessage(String &&message)`  allows to return a meaningful error message if callback returned false. 
  This message will shown in a red box on SinricPro portal website.  

- SinricProLock return state "JAMMED" now if callback failed (returned false)

Code optimization
- SinricProDevice is now default handler for powerState event/request

- SinricProSwitch is now a typedef to SinricProDevice since SinricProDevice handles onPowerState

- removed unneccessary includes

Bug fixes
- Fixed json protocol on events
- Fixed URL in library.properties
- Fixed UDP

---

## Version 2.2.1

New features:

- New Callback functions for onConnected / onDisconnected
  - SinricPro.onConnected(std::function<void(void)>);
  - SinricPro.onDisconnected(std::function<void(void)>);

- Automatic device addition
  - You can use ```SinricProSwitch& mySwitch = SinricPro[DEVICEID];``` to add a new device.

Changed:
- Stronger id validation (app-key, app-secret and deviceIds)
- Added more details to debug log about wrong id's

Fixed:
- Typos

---

## Version 2.2.0

New features:
- Removed NTPClient dependency
- Extract timeStamp from messages
  Keep timestamp in sync without NTP
- RestoreDeviceStates
  Request last known device states from server

Changed:
- Processessing of incomming messages
  Prepared for client-sided requests and server-sided responses
- Processing of outgoing messages
  Messages stored without signature / timestamp in sendQueue
  Timestamp and signature will applied while sendQueue is processed

---

## Version 2.1.1

Limited temperature and humidity to one decimal point

---

## Version 2.1.0

New interfaces introduced:
- SinricProInterface
- SinricProDeviceInterface

Marked deprecated functions:
- add(SinricProDeviceInterface& newDevice);
- add(SinricProDeviceInterface* newDevice);

---

## Version 2.0.5

fixed UDP problems on ESP32

---

## Version 2.0.4

**SinricPro.add()**
added deviceId validation check to avoid wrong deviceId's

---

## Version 2.0.2

**Devices**: Thermostat & WindowAC
fixed "adjustTargetTemperature" request

**SinricProWebsocket.h**
added server-address on websocket debug output

---
