/****************************************************************************************************************************
  Generic_WiFiNINA_MultiSwitch_intermediate.ino
  For Generic boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Example for how to use SinricPro Switch device:
   - setup a switch device
   - handle request using callback (turn on/off builtin led indicating device power state)
   - send event to sinricPro server (flash button is used to turn on/off device manually)

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
 *****************************************************************************************************************************/

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0


#if defined(ESP8266) || defined(ESP32)
#error This code is not intended to run on the ESP32/ESP8266 boards ! Please check your Tools->Board setting.
#endif

// Uncomment the following line to enable serial debug output
#define ENABLE_DEBUG    true   

#if ENABLE_DEBUG
  #define DEBUG_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA

#include "SinricPro_Generic.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"
#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define DEVICES           4                   // define how much devices are in SWITCH_IDs array

#define SWITCH_ID_1       "YOUR_DEVICE_ID_1"    // Office Lamp
#define SWITCH_ID_2       "YOUR_DEVICE_ID_2"    // Toy Car
#define SWITCH_ID_3       "YOUR_DEVICE_ID_3"    // Relay
#define SWITCH_ID_4       "YOUR_DEVICE_ID_4"    // TV

String SWITCH_IDs[DEVICES] = 
{                
  // define deviceIds in an array
  SWITCH_ID_1,    // Office Lamp
  SWITCH_ID_2,    // Toy Car
  SWITCH_ID_3,    // Relay
  SWITCH_ID_4     // TV
};

#define BAUD_RATE         115200                // Change baudrate to your need

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
  
  Serial.println("\nStarting Generic_WiFiNINA_MultiSwitch_intermediate");

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
