/****************************************************************************************************************************
  nRF52_WiFiNINA_PowerSensor.ino
  For Adafruit nRF52 boards, running WiFiNINA

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

// Uncomment the following line to enable serial debug output
#define ENABLE_DEBUG    true

#if ENABLE_DEBUG
  #define DEBUG_PORT            Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) | defined(NINA_B302_ublox) )
  #if defined(WIFININA_USE_NRF52)
    #undef WIFININA_USE_NRF52
  #endif
  #define WIFININA_USE_NRF52          true
  #define WIFI_USE_NRF52              true
  #define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA
#else
  #error This code is intended to run only on the Adafruit nRF52 boards ! Please check your Tools->Board setting.
#endif


#if defined(NRF52840_FEATHER)
  #define BOARD_TYPE      "NRF52840_FEATHER"
#elif defined(NRF52832_FEATHER)
  #define BOARD_TYPE      "NRF52832_FEATHER"
#elif defined(NRF52840_FEATHER_SENSE)
  #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
#elif defined(NRF52840_ITSYBITSY)
  #define BOARD_TYPE      "NRF52840_ITSYBITSY"
#elif defined(NRF52840_CIRCUITPLAY)
  #define BOARD_TYPE      "NRF52840_CIRCUITPLAY"
#elif defined(NRF52840_CLUE)
  #define BOARD_TYPE      "NRF52840_CLUE"
#elif defined(NRF52840_METRO)
  #define BOARD_TYPE      "NRF52840_METRO"
#elif defined(NRF52840_PCA10056)
  #define BOARD_TYPE      "NRF52840_PCA10056"
#elif defined(PARTICLE_XENON)
  #define BOARD_TYPE      "PARTICLE_XENON"
#elif defined(NINA_B302_ublox)
  #define BOARD_TYPE      "NINA_B302_ublox"
#elif defined(ARDUINO_NRF52_ADAFRUIT)
  #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
#elif defined(NRF52_SERIES)
  #define BOARD_TYPE      "NRF52_SERIES"
#else
  #define BOARD_TYPE      "NRF52_UNKNOWN"
#endif

#include "SinricPro_Generic.h"
#include "SinricProPowerSensor.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define POWERSENSOR_ID    "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200              // Change baudrate to your need

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

#if defined(BOARD_TYPE)
  Serial.println("\nStarting nRF52_WiFiNINA_PowerSensor on " + String(BOARD_TYPE));
#else
  Serial.println("\nStarting nRF52_WiFiNINA_PowerSensor on unknown nRF52 board");
#endif

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
  sendPowerSensorData();
}
