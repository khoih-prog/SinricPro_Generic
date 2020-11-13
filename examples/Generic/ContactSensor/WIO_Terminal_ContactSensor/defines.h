/****************************************************************************************************************************
  defines.h
  For WIO Terminal boards, running RTL8720DN WiFi, using Seeed_Arduino_rpcWiFi and Seeed_Arduino_rpcUnified libraries

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 **********************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#define SINRIC_PRO_USING_RTL8720DN        true

#define WEBSOCKETS_NETWORK_TYPE           NETWORK_RTL8720DN

#if !defined(SEEED_WIO_TERMINAL)
  #error This code is intended to run on the SEEED_WIO_TERMINAL ! Please check your Tools->Board setting.
#endif

#warning Using SEEED_WIO_TERMINAL

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

#define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <rpcWiFi.h>

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 222);

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define CONTACT_ID        "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200              // Change baudrate to your need


#define CONTACT_PIN       5                   // PIN where contactsensor is connected to
// LOW  = contact is open
// HIGH = contact is closed

#endif    //defines_h
