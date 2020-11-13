/****************************************************************************************************************************
  SAMD_Ethernet_PowerSensor.ino
  For Arduino SAMD21, Adafruit SAMD21, SAMD51 boards, running W5x00 or ENC28J60 Ethernet shield

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
#include "SinricProPowerSensor.h"

bool powerState = false;

// struct to store measurement from powersensor
struct 
{
  float voltage;
  float current;
  float power;
  float apparentPower;
  float reactivePower;
  float factor;
} powerMeasure;

// this is where you read from power sensor
// in this example, random values are used
void doPowerMeasure() 
{
  powerMeasure.voltage = random(2200, 2300) / 10.0f;
  powerMeasure.current = random(1, 20) / 10.0f;
  powerMeasure.power = powerMeasure.voltage * powerMeasure.current;
  powerMeasure.apparentPower = powerMeasure.power + (random(10, 20) / 10.0f);
}

bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.println("Device " + deviceId + " power turned " + String(state ? "on" : "off"));
  
  powerState = state;
  
  if (powerState) 
    doPowerMeasure(); // start a measurement when device is turned on
    
  return true; // request handled properly
}

bool sendPowerSensorData() 
{
  // dont send data if device is turned off
  if (!powerState) 
    return false;

  // limit data rate to SAMPLE_EVERY_SEC
  static unsigned long lastEvent = 0;
  unsigned long actualMillis = millis();
  
  if (actualMillis - lastEvent < (SAMPLE_EVERY_SEC * 1000)) 
    return false;
    
  lastEvent = actualMillis;

  // send measured data
  SinricProPowerSensor &myPowerSensor = SinricPro[POWERSENSOR_ID];
  bool success = myPowerSensor.sendPowerSensorEvent(powerMeasure.voltage, powerMeasure.current, powerMeasure.power, powerMeasure.apparentPower);
  
  // if measured data was sent do a new measure
  if (success) 
    doPowerMeasure();
    
  return success;
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
  uint16_t index = millis() % NUMBER_OF_MAC;

  Serial.print("Index = ");
  Serial.println(index);

  Ethernet.begin(mac[index]);
  
  Serial.print("Connected!\n[Ethernet]: IP-Address is ");
  Serial.println(Ethernet.localIP());
}

void setupSinricPro() 
{
  SinricProPowerSensor &myPowerSensor = SinricPro[POWERSENSOR_ID];

  // set callback function to device
  myPowerSensor.onPowerState(onPowerState);

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

  Serial.println("\nStarting SAMD_Ethernet_PowerSensor on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupEthernet();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
  sendPowerSensorData();
}
