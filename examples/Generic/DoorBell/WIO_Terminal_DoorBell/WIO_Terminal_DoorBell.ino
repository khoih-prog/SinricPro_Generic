/****************************************************************************************************************************
  WIO_Terminal_DoorBell.ino
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
#include "SinricProDoorbell.h"

// checkButtonpress
// reads if BUTTON_PIN gets LOW and send Event
void checkButtonPress() 
{
  static unsigned long lastBtnPress;
  unsigned long actualMillis = millis();

  if (actualMillis - lastBtnPress > 500) 
  {
    if (digitalRead(BUTTON_PIN) == LOW) 
    {
      Serial.println("Ding dong...");
      lastBtnPress = actualMillis;

      // get Doorbell device back
      SinricProDoorbell& myDoorbell = SinricPro[DOORBELL_ID];

      // send doorbell event
      myDoorbell.sendDoorbellEvent();
    }
  }
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

// setup function for SinricPro
void setupSinricPro() 
{
  // add doorbell device to SinricPro
  SinricPro.add<SinricProDoorbell>(DOORBELL_ID);
  
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
  pinMode(BUTTON_PIN, INPUT_PULLUP); // BUTTIN_PIN as INPUT

  Serial.begin(BAUD_RATE);
  while (!Serial);

  Serial.println("\nStarting WIO_Terminal_DoorBell on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  checkButtonPress();
  SinricPro.handle();
}
