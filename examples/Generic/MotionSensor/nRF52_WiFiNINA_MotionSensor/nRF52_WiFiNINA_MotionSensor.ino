/****************************************************************************************************************************
  nRF52_WiFiNINA_MotionSensor.ino
  For Adafruit nRF52 boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Example for SinricPro Motionsensor device:
   - Setup motionsensor device
   - Support onPowerState to turn on / turn off motion sensor
   - Checks a motion sensor connected to MOTIONSENSOR_PIN and send event if state changed

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
#include "SinricProMotionsensor.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define MOTIONSENSOR_ID   "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200              // Change baudrate to your need

#define MOTIONSENSOR_PIN  5                   // PIN where motionsensor is connected to
// LOW  = motion is not detected
// HIGH = motion is detected

bool myPowerState = true;                     // assume device is turned on
bool lastMotionState = false;
unsigned long lastChange = 0;

/**
   @brief Checks motionsensor connected to MOTIONSENSOR_PIN

   If motion sensor state has changed, send event to SinricPro Server
   state from digitalRead():
        HIGH = motion detected
        LOW  = motion not detected
*/
void handleMotionsensor() 
{
  // if device switched off...do nothing
  if (!myPowerState) 
    return;                            // if device switched off...do nothing

  unsigned long actualMillis = millis();

  // debounce motionsensor state transitions (same as debouncing a pushbutton)
  if (actualMillis - lastChange < 250) 
    return;

  bool actualMotionState = digitalRead(MOTIONSENSOR_PIN);   // read actual state of motion sensor

  if (actualMotionState != lastMotionState) 
  {         
    // if state has changed
    Serial.println("Motion " + String(actualMotionState ? "detected" : "not detected"));
    
    lastMotionState = actualMotionState;              // update last known state
    lastChange = actualMillis;                        // update debounce time
    SinricProMotionsensor &myMotionsensor = SinricPro[MOTIONSENSOR_ID]; // get motion sensor device
    myMotionsensor.sendMotionEvent(actualMotionState);
  }
}

/**
   @brief Callback for setPowerState request

   @param deviceId      String containing deviceId (useful if this callback used by multiple devices)
   @param[in] state     bool true=turn on device / false=turn off device
   @param[out] state    bool true=device turned on / false=device turned off
   @return true         request handled properly
   @return false        request can't be handled because some kind of error happened
*/
bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.println("Device " + deviceId + " turned " + String(state ? "on" : "off"));
  
  myPowerState = state;
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

// setup function for SinricPro
void setupSinricPro() 
{
  // add device to SinricPro
  SinricProMotionsensor& myMotionsensor = SinricPro[MOTIONSENSOR_ID];

  // set callback function to device
  myMotionsensor.onPowerState(onPowerState);

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
  Serial.println("\nStarting nRF52_WiFiNINA_MotionSensor on " + String(BOARD_TYPE));
#else
  Serial.println("\nStarting nRF52_WiFiNINA_MotionSensor on unknown nRF52 board");
#endif

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  handleMotionsensor();
  SinricPro.handle();
}
