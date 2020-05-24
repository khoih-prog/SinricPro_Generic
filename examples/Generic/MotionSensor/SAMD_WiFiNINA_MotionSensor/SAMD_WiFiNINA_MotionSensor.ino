/****************************************************************************************************************************
  SAMD_WiFiNINA_MotionSensor.ino
  For Arduino SAMD21, Adafruit SAMD21, SAMD51 boards, running WiFiNINA

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
  #define DEBUG_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#if ( defined(ADAFRUIT_FEATHER_M0) || defined(ADAFRUIT_FEATHER_M0_EXPRESS) || defined(ADAFRUIT_METRO_M0_EXPRESS) \
   || defined(ADAFRUIT_CIRCUITPLAYGROUND_M0) || defined(ADAFRUIT_GEMMA_M0) || defined(ADAFRUIT_TRINKET_M0) \
   || defined(ADAFRUIT_ITSYBITSY_M0) || defined(ADAFRUIT_PIRKEY) || defined(ARDUINO_SAMD_HALLOWING_M0) \
   || defined(ADAFRUIT_CRICKIT_M0)  || defined(ADAFRUIT_METRO_M4_EXPRESS) || defined(ADAFRUIT_GRAND_CENTRAL_M4) \
   || defined(ADAFRUIT_CRICKIT_M0)  || defined(ADAFRUIT_METRO_M4_EXPRESS) || defined(ADAFRUIT_GRAND_CENTRAL_M4) \
   || defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)  || defined(ADAFRUIT_FEATHER_M4_EXPRESS) || defined(ADAFRUIT_TRELLIS_M4_EXPRESS) \
   || defined(ADAFRUIT_PYPORTAL)  || defined(ADAFRUIT_PYPORTAL_M4_TITANO) || defined(ADAFRUIT_PYBADGE_M4_EXPRESS) \
   || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)  || defined(ADAFRUIT_PYGAMER_M4_EXPRESS) || defined(ADAFRUIT_PYBADGE_AIRLIFT_M4) \
   || defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)  || defined(ADAFRUIT_HALLOWING_M4_EXPRESS) || defined(ADAFRUIT_GRAND_CENTRAL_M4) \
   || defined(__SAMD21E18A__) || defined(__SAMD21G18A__) || defined(__SAMD51__) \
   || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) \
   || defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )
  #if defined(WIFININA_USE_SAMD)
    #undef WIFININA_USE_SAMD
    #undef WIFI_USE_SAMD
  #endif
  #define WIFININA_USE_SAMD         true
  #define WIFI_USE_SAMD             true
  #define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA
#else  
  #error This code is intended to run only on the SAMD boards ! Please check your Tools->Board setting.
#endif

#if defined(ADAFRUIT_FEATHER_M0)
  #define BOARD_TYPE      "ADAFRUIT_FEATHER_M0"
#elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_FEATHER_M0_EXPRESS"
#elif defined(ADAFRUIT_METRO_M0_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_METRO_M0_EXPRESS"
#elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
  #define BOARD_TYPE      "ADAFRUIT_CIRCUITPLAYGROUND_M0"
#elif defined(ADAFRUIT_GEMMA_M0)
  #define BOARD_TYPE      "ADAFRUIT_GEMMA_M0"
#elif defined(ADAFRUIT_TRINKET_M0)
  #define BOARD_TYPE      "ADAFRUIT_TRINKET_M0"
#elif defined(ADAFRUIT_ITSYBITSY_M0)
  #define BOARD_TYPE      "ADAFRUIT_ITSYBITSY_M0"
#elif defined(ADAFRUIT_PIRKEY)
  #define BOARD_TYPE      "ADAFRUIT_PIRKEY"
#elif defined(ARDUINO_SAMD_HALLOWING_M0)
  #define BOARD_TYPE      "ARDUINO_SAMD_HALLOWING_M0"
#elif defined(ADAFRUIT_CRICKIT_M0)
  #define BOARD_TYPE      "ADAFRUIT_CRICKIT_M0"
#elif defined(ADAFRUIT_METRO_M4_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_METRO_M4_EXPRESS"
#elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
  #define BOARD_TYPE      "ADAFRUIT_GRAND_CENTRAL_M4"
#elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_ITSYBITSY_M4_EXPRESS"
#elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_FEATHER_M4_EXPRESS"
#elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_TRELLIS_M4_EXPRESS"
#elif defined(ADAFRUIT_PYPORTAL)
  #define BOARD_TYPE      "ADAFRUIT_PYPORTAL"
#elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
  #define BOARD_TYPE      "ADAFRUIT_PYPORTAL_M4_TITANO"
#elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_PYBADGE_M4_EXPRESS"
#elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #define BOARD_TYPE      "ADAFRUIT_METRO_M4_AIRLIFT_LITE"
#elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_PYGAMER_M4_EXPRESS"
#elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
  #define BOARD_TYPE      "ADAFRUIT_PYBADGE_AIRLIFT_M4"
#elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_MONSTER_M4SK_EXPRESS"
#elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
  #define BOARD_TYPE      "ADAFRUIT_HALLOWING_M4_EXPRESS"
#elif defined(ARDUINO_SAMD_ZERO)
  #define BOARD_TYPE      "SAMD Zero"
#elif defined(ARDUINO_SAMD_MKR1000)
  #define BOARD_TYPE      "SAMD MKR1000"
#elif defined(ARDUINO_SAMD_MKRWIFI1010)
  #define BOARD_TYPE      "SAMD MKRWIFI1010"
#elif defined(ARDUINO_SAMD_NANO_33_IOT)
  #define BOARD_TYPE      "SAMD NANO_33_IOT"
#elif defined(ARDUINO_SAMD_MKRFox1200)
  #define BOARD_TYPE      "SAMD MKRFox1200"
#elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
  #define BOARD_TYPE      "SAMD MKRWAN13X0"
#elif defined(ARDUINO_SAMD_MKRGSM1400)
  #define BOARD_TYPE      "SAMD MKRGSM1400"
#elif defined(ARDUINO_SAMD_MKRNB1500)
  #define BOARD_TYPE      "SAMD MKRNB1500"
#elif defined(ARDUINO_SAMD_MKRVIDOR4000)
  #define BOARD_TYPE      "SAMD MKRVIDOR4000"
#elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
  #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
#elif defined(__SAMD21E18A__)
  #define BOARD_TYPE      "SAMD21E18A"
#elif defined(__SAMD21G18A__)
  #define BOARD_TYPE      "SAMD21G18A"
#elif defined(__SAMD51G19A__)
  #define BOARD_TYPE      "SAMD51G19A"
#elif defined(__SAMD51J19A__)
  #define BOARD_TYPE      "SAMD51J19A"
#elif defined(__SAMD51J20A__)
  #define BOARD_TYPE      "SAMD51J20A"
#elif defined(__SAMD51__)
  #define BOARD_TYPE      "SAMD51"
#else
  #define BOARD_TYPE      "SAMD Unknown"
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
  Serial.println("\nStarting SAMD_WiFiNINA_MotionSensor on " + String(BOARD_TYPE));
#else
  Serial.println("\nStarting SAMD_WiFiNINA_MotionSensor on unknown SAMD board");
#endif

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  handleMotionsensor();
  SinricPro.handle();
}
