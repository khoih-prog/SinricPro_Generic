/****************************************************************************************************************************
  WIO_Terminal_AQSensor.ino
  For WIO Terminal boards, running RTL8720DN WiFi, using Seeed_Arduino_rpcWiFi and Seeed_Arduino_rpcUnified libraries

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 **********************************************************************************************************************************/

/*
   Example for how to use SinricPro Air Quality Sensor device

   If you encounter any issues:
   - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
   - ensure all dependent libraries are installed
     - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
     - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
   - open serial monitor and check whats happening
   - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
   - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
*/

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0

#include "defines.h"

#include "SinricPro_Generic.h"
#include "SinricProAirQualitySensor.h"

// Air quality sensor event dispatch time.  Min is every 1 min.
#define MIN (1000UL * 60 * 1)
unsigned long dispatchTime = millis() + MIN;

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
  Serial.print("\n[WiFi]: IP-Address is ");
  Serial.println(WiFi.localIP());
}

// setup function for SinricPro
void setupSinricPro() 
{
  // add device to SinricPro
  SinricProAirQualitySensor& mySinricProAirQualitySensor = SinricPro[DEVICE_ID];

  // set callback function to device

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

void setup() 
{
  Serial.begin(BAUD_RATE); 
  while (!Serial);
  
  Serial.println("\nStarting WIO_Terminal_AQSensor on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));
  
  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();

  if ((long)(millis() - dispatchTime) >= 0) 
  {
    SinricProAirQualitySensor &mySinricProAirQualitySensor = SinricPro[DEVICE_ID]; // get sensor device

    int pm1   = 0;
    int pm2_5 = 0;
    int pm10  = 0;

    mySinricProAirQualitySensor.sendAirQualityEvent(pm1, pm2_5, pm10, "PERIODIC_POLL");
    dispatchTime += MIN;
    
    Serial.println("Sending Air Quality event ..");
  }
}
