/****************************************************************************************************************************
  Generic_WiFiNINA_MultiSwitch_beginner.ino
  For Generic boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.5.1

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
  2.5.1   K Hoang      02/08/2020 Add support to STM32F/L/H/G/WB/MP1. Add debug feature, examples. Restructure examples.
                                  Sync with SinricPro v2.5.1: add Speaker SelectInput, Camera. Enable Ethernetx lib support.
 **********************************************************************************************************************************/

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0

#include "defines.h"

#include "SinricPro_Generic.h"
#include "SinricProSwitch.h"

bool onPowerState1(const String &deviceId, bool &state)
{
  Serial.println("Device 1 turned " + String(state ? "on" : "off"));
  return true; // request handled properly
}

bool onPowerState2(const String &deviceId, bool &state)
{
  Serial.println("Device 2 turned " + String(state ? "on" : "off"));
  return true; // request handled properly
}

bool onPowerState3(const String &deviceId, bool &state)
{
  Serial.println("Device 3 turned " + String(state ? "on" : "off"));
  return true; // request handled properly
}

bool onPowerState4(const String &deviceId, bool &state)
{
  Serial.println("Device 4 turned " + String(state ? "on" : "off"));
  return true; // request handled properly
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
  // add devices and callbacks to SinricPro
  SinricProSwitch& mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);

  SinricProSwitch& mySwitch2 = SinricPro[SWITCH_ID_2];
  mySwitch2.onPowerState(onPowerState2);

  SinricProSwitch& mySwitch3 = SinricPro[SWITCH_ID_3];
  mySwitch3.onPowerState(onPowerState3);

  SinricProSwitch& mySwitch4 = SinricPro[SWITCH_ID_4];
  mySwitch4.onPowerState(onPowerState4);

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
  Serial.begin(BAUD_RATE); 
  while (!Serial);
  
  Serial.println("\nStarting Generic_WiFiNINA_MultiSwitch_beginner on " + String(BOARD_NAME));
  
  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
