/****************************************************************************************************************************
  nRF52_WiFiNINA_MultiSwitch_intermediate.ino
  For nRF52 boards, running WiFiNINA

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
#include "SinricProSwitch.h"

String SWITCH_IDs[DEVICES] = 
{                
  // define deviceIds in an array
  SWITCH_ID_1,    // Office Lamp
  SWITCH_ID_2,    // Toy Car
  SWITCH_ID_3,    // Relay
  SWITCH_ID_4     // TV
};

bool onPowerState(const String &deviceId, bool &state) 
{
  for (int i = 0; i < DEVICES; i++) 
  {   
    // go through the devices
    if (deviceId == SWITCH_IDs[i]) 
    {    
      // if deviceId matches, print power state for device
      Serial.println("Device " + String(i) + " turned " + String(state ? "on" : "off"));
    }
  }
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
  // add devices to SinricPro and set callback function
  for (int i = 0; i < DEVICES; i++) 
  {
    SinricProSwitch& mySwitch = SinricPro[SWITCH_IDs[i]];
    mySwitch.onPowerState(onPowerState);
  }

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
  
  Serial.println("\nStarting nRF52_WiFiNINA_MultiSwitch_intermediate on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
