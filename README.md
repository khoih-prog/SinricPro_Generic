## SinricPro_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/SinricPro_Generic.svg?)](https://www.ardu-badge.com/BlynkEthernet_Manager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/SinricPro_Generic.svg)](https://github.com/khoih-prog/SinricPro_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/SinricPro_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/SinricPro_Generic.svg)](http://github.com/khoih-prog/SinricPro_Generic/issues)

### Releases v2.4.0

1. Add support to :

  - ***Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.)***.
  - ***Adafruit SAM21 (Itsy-Bitsy M0, Metro M0, Feather M0, Gemma M0, etc.)***.
  - ***Adafruit SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)***.
  - ***AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B30_ublox, etc.***.
  - ***Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0.***
  - ***STM32 (Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.)***.
  - ***SAM DUE***
  
2. Bump up to sync with v2.4.0 of original SinricPro library

---

## Prerequisite
 1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. `Arduino AVR core 1.8.2 or later` for Arduino (Use Arduino Board Manager)
 3. [`Teensy core 1.52 or later`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 4. [`Arduino SAM DUE core 1.6.12 or later`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.5 or later`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards  (Nano 33 IoT, etc.)
 6. [`Adafruit SAMD core 1.5.11 or later`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Itsy-Bitsy M0/M4, etc.)
 7. [`Adafruit nRF52 v0.20.1 or later`](https://www.adafruit.com/) for nRF52 boards such as AdaFruit Feather nRF52840 Express, NINA_B302_ublox, etc.
 8. [ArduinoJson Version 6.15.0 or later](https://github.com/bblanchon/ArduinoJson)
 9. [WebSockets_Generic Version 2.2.1 or later](https://github.com/khoih/WebSockets_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebSockets_Generic.svg?)](https://www.ardu-badge.com/WebSockets_Generic)
10. Depending on which Ethernet card you're using:
   - [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) for W5200 and W5500
   - [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) for W5500 (Deprecated, use Arduino Ethernet library)
   - [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.
   - [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500.
   - [`Ethernet_Shield_W5200 library`](https://github.com/khoih-prog/Ethernet_Shield_W5200) for W5200
   - [`UIPEthernet library v2.0.8 or later`](https://github.com/khoih-prog/UIPEthernet) for ENC28J60
11. [`WiFiNINA_Generic library v1.5.2 or later`](https://github.com/khoih-prog/WiFiNINA_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) if using WiFiNINA for boards such as Nano 33 IoT, nRF52, etc.

---

## Installation

### ArduinoIDE
1. Open Library Manager (*Tools / Manage Libraries*)
2. Search for *SinricPro_Generic* and click *Install*
3. Repeat step 2 for all [dependent libraries](#Prerequisite)!
4. Open example in ArduinoIDE (*File / Examples / SinricPro_Generic / ...*)

You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/SinricPro_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic) for more detailed instructions.

### VS Code & PlatformIO:
1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **SinricPro_Generic** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/)
4. Use included [platformio.ini](examples/platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automaticly.

[![arduino-library-badge](https://www.ardu-badge.com/badge/SinricPro_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic)

---

#### Important notes

1. To be able to compile and run on nRF52840 boards, you have to copy the whole [nRF52 0.20.1](https://github.com/khoih-prog/SinricPro_Generic/tree/master/Packages_Patches/adafruit/hardware/nrf52/0.20.1) directory into Adafruit nRF52 directory (./packages/adafruit/hardware/nrf52/0.20.1). 

Supposing the Adafruit nRF52 version is 0.20.1. These files must be copied into the directory:
- `packages/adafruit/hardware/nrf52/0.20.1/platform.txt`
- `packages/adafruit/hardware/nrf52/0.20.1/boards.txt`
- `packages/adafruit/hardware/nrf52/0.20.1/variants/variant.h`
- `packages/adafruit/hardware/nrf52/0.20.1/variants/variant.cpp`

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `packages/adafruit/hardware/nrf52/x.yy.z/variants/variant.h`
- `packages/adafruit/hardware/nrf52/x.yy.z/variants/variant.cpp`

2. To be able to compile and run on Teensy boards, you have to copy the file [Teensy boards.txt](https://github.com/khoih-prog/SinricPro_Generic/blob/master/Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.12/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.12. This file must be copied into the directory:

- `./arduino-1.8.12/hardware/teensy/avr/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`

3. To be able to compile and run on SAM DUE boards, you have to copy the whole [SAM DUE](https://github.com/khoih-prog/SinricPro_Generic/tree/master/Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (./packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino sam version is 1.6.12. This file must be copied into the directory:

- `packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `packages/arduino/hardware/sam/x.yy.zz/platform.txt`

---

## Full user documentation
Please see here for [full user documentation](https://sinricpro.github.io/esp8266-esp32-sdk)

---

## Examples
See [examples](https://github.com/khoih-prog/SinricPro_Generic/tree/master/examples) on GitHub

---

## Usage
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
bool onPowerState(const String &deviceId, bool &state) {
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
## How to add a device?
Syntax is
```C++
  DeviceType& myDevice = SinricPro[DEVICE_ID];
```
Example
```C++
  SinricProSwitch& mySwitch = SinricPro["YOUR-SWITCH-ID-HERE"];
```
*Example 2 (alternatively)*
```C++
  SinricProSwitch& mySwitch = SinricPro.add<SinricProSwitch>("YOUR-SWITCH-ID-HERE");
```

---
## How to retrieve a device for sending an event?
Syntax is
```C++
  DeviceType& myDevice = SinricPro[DEVICE_ID];
```
Example 1
```C++
  SinricProDoorbell& myDoorbell = SinricPro["YOUR-DOORBELL-ID-HERE"];
  myDoorbell.sendDoorbellEvent();
```

*Example 2 (alternatively)*
```C++
  SinricPro["YOUR-DOORBELL-ID-HERE"].as<SinricProDoorbell>().sendDoorbellEvent();
```

---

## Example [SAMD_WiFiNINA_Switch](examples/Generic/Switch/SAMD_WiFiNINA/SAMD_WiFiNINA_Switch)

Please take a look at other examples, as well.

```cpp
// Uncomment the following line to enable serial debug output
#define ENABLE_DEBUG    true   

#if ENABLE_DEBUG
#define DEBUG_ESP_PORT Serial
#define NODEBUG_WEBSOCKETS
#define NDEBUG
#endif

#if (  defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )
#if defined(WIFININA_USE_SAMD)
#undef WIFININA_USE_SAMD
#undef WIFI_USE_SAMD
#endif
#define WIFININA_USE_SAMD      true
#define WIFI_USE_SAMD          true
#define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA
#else
#error This code is intended to run only on the SAMD boards ! Please check your Tools->Board setting.
#endif

#if defined(ARDUINO_SAMD_ZERO)
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
#elif defined(__SAMD21G18A__)
#define BOARD_TYPE      "SAMD21G18A"
#elif defined(__SAMD51G19A__)
#define BOARD_TYPE      "SAMD51G19"
#elif defined(__SAMD51J19A__)
#define BOARD_TYPE      "SAMD51J19A"
#elif defined(__SAMD51J20A__)
#define BOARD_TYPE      "SAMD51J20A"
#elif defined(__SAMD51__)
#define BOARD_TYPE      "SAMD51"
#else
#define BOARD_TYPE      "SAMD Unknown"
#endif

#include <WebSockets_Generic.h>

#include "SinricPro_Generic.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"
#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200                // Change baudrate to your need

#define BUTTON_PIN        0   // GPIO for BUTTON (inverted: LOW = pressed, HIGH = released)
#define LED_PIN           2   // GPIO for LED (inverted)

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
  //Serial.printf("Device %s turned %s (via SinricPro) \r\n", deviceId.c_str(), state ? "on" : "off");
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
    //Serial.printf("Device %s turned %s (manually via flashbutton)\r\n", mySwitch.getDeviceId(), myPowerState ? "on" : "off");
    Serial.print("Device ");
    Serial.print(mySwitch.getDeviceId());
    Serial.print(myPowerState ? "turned on" : "turn off");
    Serial.println(" (manually via flashbutton)");

    lastBtnPress = actualMillis;  // update last button press variable
  }
}

// setup function for WiFi connection
void setupWiFi() 
{
  Serial.print("\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) 
  {
    //Serial.printf(".");
    Serial.print(".");
    delay(250);
  }
  //Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
  Serial.print("connected!\n[WiFi]: IP-Address is ");
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
    //Serial.printf("Connected to SinricPro\r\n");
    Serial.println("Connected to SinricPro");
  });
  
  SinricPro.onDisconnected([]() 
  {
    //Serial.printf("Disconnected from SinricPro\r\n");
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
  
#if defined(BOARD_TYPE)  
  Serial.println("\nStarting Switch on " + String(BOARD_TYPE));
#else
  Serial.println("\nStarting Switch on unknown board");
#endif  
  
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

---

### Releases v2.4.0

1. Add support to :

  - ***Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.)***.
  - ***Adafruit SAM21 (Itsy-Bitsy M0, Metro M0, Feather M0, Gemma M0, etc.)***.
  - ***Adafruit SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)***.
  - ***AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B30_ublox, etc.***.
  - ***Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0.***
  - ***STM32 (Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.)***.
  - ***SAM DUE***
  
2. Bump up to sync with v2.4.0 of original SinricPro library

---

### Contributions and thanks

1. Based on and modified from [Boris Jaeger's SinricPro library](https://github.com/sinricpro/esp8266-esp32-sdk) which is written for only ESP8266 and ESP32.

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library


### License and credits ###

- All credits go to original author [Boris Jaeger](https://github.com/sivar2311).

- The library is licensed under [CC-BY-SA](https://creativecommons.org/licenses/by/2.0/) and [MIT](https://github.com/khoih-prog/WebSockets_Generic/blob/master/LICENSE)

