/****************************************************************************************************************************
  Generic_WiFiNINA_Fan.ino
  For Generic boards, running WiFiNINA

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
#include "SinricProFanUS.h"

// we use a struct to store all states and values for our fan
// fanSpeed (1..3)
struct 
{
  bool powerState = false;
  int fanSpeed = 1;
} device_state;

bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.println("Fan turned " + String(state ? "on" : "off"));
  device_state.powerState = state;
  return true; // request handled properly
}

// Fan rangeValue is from 1..3
bool onRangeValue(const String &deviceId, int &rangeValue) 
{
  device_state.fanSpeed = rangeValue;
  
  Serial.println("Fan speed changed to " + String(device_state.fanSpeed));
  
  return true;
}

// Fan rangeValueDelta is from -3..+3
bool onAdjustRangeValue(const String &deviceId, int rangeValueDelta) 
{
  device_state.fanSpeed += rangeValueDelta;
  
  Serial.println("Fan speed changed about " + String(rangeValueDelta) + " to " + String(device_state.fanSpeed));

  rangeValueDelta = device_state.fanSpeed; // return absolute fan speed
  return true;
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

void setupSinricPro() 
{
  SinricProFanUS &myFan = SinricPro[FAN_ID];

  // set callback function to device
  myFan.onPowerState(onPowerState);
  myFan.onRangeValue(onRangeValue);
  myFan.onAdjustRangeValue(onAdjustRangeValue);

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
  
  Serial.println("\nStarting Generic_WiFiNINA_Fan on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
