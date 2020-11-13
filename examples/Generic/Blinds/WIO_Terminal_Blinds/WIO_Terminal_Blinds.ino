/****************************************************************************************************************************
  WIO_Terminal_Blinds.ino
  For WIO Terminal boards, running RTL8720DN WiFi, using Seeed_Arduino_rpcWiFi and Seeed_Arduino_rpcUnified libraries

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 **********************************************************************************************************************************/

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0

#include "defines.h"

#include "SinricPro_Generic.h"
#include "SinricProBlinds.h"

int blindsPosition = 0;
bool powerState = false;

bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.println("Device " + deviceId + " power turned " + String(state ? "on" : "off"));
  
  powerState = state;
  return true; // request handled properly
}

bool onSetPosition(const String &deviceId, int &position) 
{
  Serial.println("Device " + deviceId + " set position to " + String(position));
  
  return true; // request handled properly
}

bool onAdjustPosition(const String &deviceId, int &positionDelta) 
{
  blindsPosition += positionDelta;
  
  Serial.println("Device " + deviceId + " position changed about " + String(positionDelta) + " to " + String(blindsPosition));
  
  positionDelta = blindsPosition; // calculate and return absolute position
  return true; // request handled properly
}


// setup function for WiFi connection
void setupWiFi()
{
  Serial.print("\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }
  Serial.print("[WiFi]: IP-Address is ");
  Serial.println(WiFi.localIP());
}

void setupSinricPro() 
{
  // get a new Blinds device from SinricPro
  SinricProBlinds &myBlinds = SinricPro[BLINDS_ID];
  myBlinds.onPowerState(onPowerState);
  myBlinds.onSetPosition(onSetPosition);
  myBlinds.onAdjustPosition(onAdjustPosition);

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

  Serial.println("\nStarting WIO_Terminal_Blinds on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
