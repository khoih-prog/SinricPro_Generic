/****************************************************************************************************************************
  nRF52_Ethernet_Fan.ino
  For Adafruit nRF52 boards, running W5x00 or ENC28J60 Ethernet shield

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

// setup function for setupEthernet connection
void setupEthernet() 
{
  #if USE_ETHERNET
    LOGWARN(F("=========== USE_ETHERNET ==========="));
  #elif USE_ETHERNET2
    LOGWARN(F("=========== USE_ETHERNET2 ==========="));
  #elif USE_ETHERNET3
    LOGWARN(F("=========== USE_ETHERNET3 ==========="));
  #elif USE_ETHERNET_LARGE
    LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
  #elif USE_ETHERNET_ESP8266
    LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
  #else
    LOGWARN(F("========================="));
  #endif
 
  LOGWARN(F("Default SPI pinout:"));
  LOGWARN1(F("MOSI:"), MOSI);
  LOGWARN1(F("MISO:"), MISO);
  LOGWARN1(F("SCK:"),  SCK);
  LOGWARN1(F("SS:"),   SS);
  LOGWARN(F("========================="));
   
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif
       
  LOGWARN1(F("Use default CS/SS pin : "), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries

    Ethernet.init (USE_THIS_SS_PIN);

  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
    
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
                    
  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

    // start the ethernet connection and the server:
  // Use Static IP
  //Ethernet.begin(mac, ip);
  // Use DHCP dynamic IP and random mac
  srand(millis());
  uint16_t index = rand() % NUMBER_OF_MAC;

  Serial.print("Index = ");
  Serial.println(index);

  Ethernet.begin(mac[index]);
  
  Serial.print("Connected!\n[Ethernet]: IP-Address is ");
  Serial.println(Ethernet.localIP());
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

  Serial.println("\nStarting nRF52_Ethernet_Fan on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupEthernet();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
