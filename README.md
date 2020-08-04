## SinricPro_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/SinricPro_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/SinricPro_Generic.svg)](https://github.com/khoih-prog/SinricPro_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/SinricPro_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/SinricPro_Generic.svg)](http://github.com/khoih-prog/SinricPro_Generic/issues)

---

### Releases v2.5.1

1. Add support to :

  - ***STM32F/L/H/G/WB/MP1 (Nucleo-64 L053R8,Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32Fx, STM32H7, STM32Lx, STM32Gx, STM32WB, STM32MP1, etc.) having 64K+ Flash program memory.***
  - ***Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)***

2. Add support to :

  - ***W5x00's Ethernet2, Ethernet3, EthernetLarge Libraries.***
  
3. Add sample Packages_Patches for ***STM32 stm32*** (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8)
4. Add Ethernet Library Patches to support ***new WobSockets headers.***
5. Add more Packages' Patches.
6. Bump up to sync with v2.5.1 of original SinricPro library to add Speaker SelectInput and ESP32 Camera.
7. Restructure examples.

### Releases v2.4.0

1. Add support to :

  - ***Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.)***.
  - ***Adafruit SAM21 (Itsy-Bitsy M0, Metro M0, Feather M0, Gemma M0, etc.)***.
  - ***Adafruit SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)***.
  - ***AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox etc.***.
  - ***Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0.***
  - ***STM32 (Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.)***.
  - ***SAM DUE***
  
2. Bump up to sync with v2.4.0 of original SinricPro library

---

## Prerequisite
 1. [`Arduino IDE 1.8.12+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. `Arduino AVR core 1.8.2 or later` for Arduino (Use Arduino Board Manager)
 3. [`ESP32 core 1.0.4+`](https://github.com/espressif/arduino-esp32/releases) for ESP32 boards
 4. [`ESP8266 core 2.7.3+` for Arduino](https://github.com/esp8266/Arduino#installing-with-boards-manager) for ESP8266 boards. To use ESP8266 core 2.7.1+ for LittleFS.
 5. `Arduino AVR core 1.8.2+` for Arduino (Use Arduino Board Manager)
 6. [`Teensy core 1.53+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 7. [`Arduino SAM DUE core 1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 8. [`Arduino SAMD core 1.8.7+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards (Nano 33 IoT, etc.).
 9. [`Adafruit SAMD core 1.6.0+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Itsy-Bitsy M4, etc.)
10. [`Adafruit nRF52 v0.20.5+`](https://www.adafruit.com/) for nRF52 boards such as AdaFruit Feather nRF52840 Express, NINA_B302_ublox, etc.
11. [`Arduino Core for STM32 v1.9.0+`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. To install go to Arduino IDE, select Boards Manager, search for ***`STM32`***
12. [`ArduinoJson Version 6.16.0+`](https://github.com/bblanchon/ArduinoJson)
13. [`WebSockets_Generic Version 2.2.3+`](https://github.com/khoih-prog/WebSockets_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebSockets_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic)
14. Depending on which Ethernet card you're using:
   - [`Ethernet library v2.0.0+`](https://www.arduino.cc/en/Reference/Ethernet) for W5100, W5200 and W5500. ***Ready*** from v1.0.1.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500 (Deprecated, use Arduino Ethernet library).
   - [`Ethernet3 library v1.5.3+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500.
   - [`UIPEthernet library v2.0.8+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60.
   - [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in Ethernet LAN8742A on (Nucleo-144, Discovery). To be used with [`STM32duino_LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP).
15. [`WiFiNINA_Generic library v1.6.2+`](https://github.com/khoih-prog/WiFiNINA_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) if using WiFiNINA for boards such as Nano 33 IoT, nRF52, Teensy, etc.

---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `SinricPro_Generic`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/SinricPro_Generic.svg?)](https://www.ardu-badge.com/SinricPro_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [SinricPro_Generic](https://github.com/khoih-prog/SinricPro_Generic) page.
2. Download the latest release `SinricPro_Generic-master.zip`.
3. Extract the zip file to `SinricPro_Generic-master` directory 
4. Copy whole `SinricPro_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:
1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **SinricPro_Generic** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for SinricPro_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](examples/platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automaticly.

---

### Packages' Patches

 1. ***To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards***, you have to copy the whole [nRF52 0.20.5](Packages_Patches/adafruit/hardware/nrf52/0.20.5) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5). 

Supposing the Adafruit nRF52 version is 0.20.5. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B112_ublox/variant.cpp`
- ***`~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/cores/nRF5/Udp.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- ***`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`***

 2. ***To be able to compile and run on Teensy boards***, you have to copy the file [Teensy boards.txt](Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.12/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.12. This file must be copied into the directory:

- `./arduino-1.8.12/hardware/teensy/avr/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`

 3. ***To be able to compile and run on SAM DUE boards***, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

 4. ***To be able to automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the file [Arduino SAMD platform.txt](Packages_Patches/arduino/hardware/samd/1.8.6) into Arduino samd directory (~/.arduino15/packages/arduino/hardware/samd/1.8.6). 

Supposing the Arduino SAMD core version is 1.8.6. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.6/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`

 5. ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.0) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.0). 

Supposing the Adafruit SAMD core version is 1.6.0. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

 6. ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.7.7) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.7.7). 

Supposing the Seeeduino SAMD core version is 1.7.7. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.7.7/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

7. ***To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards***, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---

### Libraries' Patches

1. If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

2. To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

3. To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

4. To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:
- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

6. ***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

7. To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.12/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

---

### Important Notes

1. Code is restructured to provide flexibility to make it easy to support many more ***WiFi/Ethernet*** modules/shields in the future. Please delete the *.cpp files, replaced by *.hpp files, in the src directory, if *.cpp files still exist after installing new version.

2. For ***Adafruit nRF52***, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = MO(SI)
  - SPI_MISO  = MI(SO)
  - SPI_SCK   = SCK

3. For ***Adafruit SAMD21/SAMD51***, use the SPI's CS/SS pin as follows:

  - Itsy-Bitsy M0/M4, Feather M0 (Express), Hallowing M0 Express, Zero, Metro M0 => use CS = 16 = pin A2
  - Feather M4 (SAMD51)   => use SS/CS = 9
  - Grand Central M4      => use SS/CS = 53
  - Hallowing M4          => use SS/CS = 10
  - Metro M4 AirLift      => use SS/CS = 36

To know the default CS/SS pins of not listed boards, check the related `variant.h` files in 

`~/.arduino15/packages/adafruit/hardware/samd/x.y.zz/variants/board_name/variant.h`

4. For ***Arduino SAM DUE***, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = 75 ( pin 4 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_MISO  = 74 ( pin 1 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_SCK   = 76 ( pin 3 @ [ICSP connector](pics/ICSP_connector.jpg) )
  
<p align="center">
    <img src="https://github.com/khoih-prog/WebSockets2_Generic/blob/master/pics/ICSP_connector.jpg">
</p>
  
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

1. File [SAMD_WiFiNINA_Switch.ino](examples/Generic/Switch/SAMD_WiFiNINA/SAMD_WiFiNINA_Switch/SAMD_WiFiNINA_Switch.ino)

```cpp
/ STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
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
    Serial.print(mySwitch.getDeviceId());
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
  
  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  handleButtonPress();
  SinricPro.handle();
}

```

2. File [defines.h](examples/Generic/Switch/SAMD_WiFiNINA/SAMD_WiFiNINA_Switch/defines.h)

---

#### Debug terminal output when running [SAMD_WiFiNINA_TV](examples/Generic/TV/SAMD_WiFiNINA_TV) on NANO_33_IOT

```
Starting SAMD_WiFiNINA_TV on SAMD NANO_33_IOT
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

#### Debug terminal output when running [SAMD_WiFiNINA_Light](examples/Generic/Light/SAMD_WiFiNINA_Light) on NANO_33_IOT

```
Starting SAMD_WiFiNINA_Light on SAMD NANO_33_IOT
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

#### Debug terminal output when running [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on nRD52 NRF52840_ITSYBITSY with W5500 Ethernet using "fixed" Ethernet2 Library

```
Starting Generic_Ethernet_Blinds on NRF52840_ITSYBITSY
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

#### Debug terminal output when running [Generic_Ethernet_Blinds](examples/Generic/Blinds/Generic_Ethernet_Blinds) on Seeeduino SEEED_XIAO_M0 with W5500 Ethernet using "fixed" Ethernet3 Library

```
Starting Generic_Ethernet_Blinds on SEEED_XIAO_M0
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

---

### Releases v2.5.1

1. Add support to :

  - ***STM32F/L/H/G/WB/MP1 (Nucleo-64 L053R8,Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32Fx, STM32H7, STM32Lx, STM32Gx, STM32WB, STM32MP1, etc.) having 64K+ Flash program memory.***
  - ***Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)***

2. Add support to :

  - ***W5x00's Ethernet2, Ethernet3, EthernetLarge Libraries.***
  
3. Add sample Packages_Patches for ***STM32 stm32*** (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8)
4. Add Ethernet Library Patches to support ***new WobSockets headers.***
5. Add more Packages' Patches.
6. Bump up to sync with v2.5.1 of original SinricPro library to add Speaker SelectInput and ESP32 Camera.
7. Restructure examples.

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

### TO DO

1. Bug Searching and Killing
2. Support more types of new boards
3. Support more types of Ethernet modules/shields, such as ***LAN8742A, LAN8720, etc.***
4. Support more types of WiFi modules/shields, such as WiFi101, ***ESP8266-AT, ESP32-AT***
5. Support ***GSM/GPRS*** modules/shields.

### DONE

 1. Add support to ***Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)***.
 2. Add support to ***Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)***.
 3. Add support to ***Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.)***.
 4. Add support to SAM DUE.
 5. Add support to Teensy.
 6. Add support to all ***STM32F/L/H/G/WB/MP1 having 64K+ Flash program memory.****
 7. Add support to ***Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)***
 8. Add support to ***W5x00, ENC28J60*** Ethernet modules/shields.
 9. Add support to ***Ethernet, EthernetLarge, Ethernet2, Ethernet3, UIPEthernet*** libraries.

 ---

### Contributions and thanks

1. Based on and modified from [Boris Jaeger's](https://github.com/sivar2311) [SinricPro library](https://github.com/sinricpro/esp8266-esp32-sdk) which is written for only ESP8266 and ESP32. 
2. Also thanks to the good [Sinric](https://sinric.com)/[SinricPro](https://sinric.pro) platform of [Aruna Tennakoon](https://github.com/kakopappa)
3. Thanks to good work of [Miguel Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially ***U-Box B302 running as nRF52840 and U-Box B112 running as nRF52832***, has never been started and finished.

<table>
  <tr>
    <td align="center"><a href="https://github.com/sivar2311"><img src="https://github.com/sivar2311.png" width="100px;" alt="sivar2311"/><br /><sub><b>⭐️ Boris Jaeger</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/kakopappa"><img src="https://github.com/kakopappa.png" width="100px;" alt="kakopappa"/><br /><sub><b>⭐️ Aruna Tennakoon</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>tcpipchip</b></sub></a><br /></td>
  </tr> 
</table>


## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License and credits ###

- All credits go to original author [Boris Jaeger](https://github.com/sivar2311).

- The library is licensed under [CC-BY-SA](https://creativecommons.org/licenses/by/2.0/) and [MIT](https://github.com/khoih-prog/SinricPro_Generic/blob/master/LICENSE)

