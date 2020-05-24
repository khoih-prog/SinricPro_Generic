/****************************************************************************************************************************
  Generic_WiFiNINA_PowerSensor.ino
  For Generic boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  How this example works:
   - if this device is turned on, it makes a power measurement
   - after SAMPLE_EVERY_SEC seconds, this data is sent to SinricPro server and a new mesurement is taken
     (this step repeats until device is turned off)

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
#include "SinricProPowerSensor.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define POWERSENSOR_ID    "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200                // Change baudrate to your need

#define SAMPLE_EVERY_SEC  60                  // Send every 60 seconds new data to server


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

  Serial.println("\nStarting Generic_WiFiNINA_PowerSensor");

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
  sendPowerSensorData();
}
