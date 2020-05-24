/****************************************************************************************************************************
  SAMD_WiFiNINA_Switch.ino
  For Arduino SAMD21, Adafruit SAMD21, SAMD51 boards, running WiFiNINA

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

#include <WebSockets_Generic.h>
#include "SinricPro_Generic.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"
#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200                // Change baudrate to your need

#define BUTTON_PIN        0   // GPIO for BUTTON (inverted: LOW = pressed, HIGH = released)
#define LED_PIN           2   // GPIO for LED (inverted)

bool myPowerState = false;
unsigned long lastBtnPress = 0;

/* bool onPowerState(String deviceId, bool &state)

   Callback for setPowerState request
   parameters
    String deviceId (r)
      contains deviceId (useful if this callback used by multiple devices)
    bool &state (r/w)
      contains the requested state (true:on / false:off)
      must return the new state

   return
    true if request should be marked as handled correctly / false if not
*/
bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.print("Device ");
  Serial.print(deviceId.c_str());
  Serial.print(state ? " turned on" : " turn off");
  Serial.println(" (via SinricPro)");
  
  myPowerState = state;
  digitalWrite(LED_PIN, myPowerState ? LOW : HIGH);
  return true; // request handled properly
}

void handleButtonPress() 
{
  unsigned long actualMillis = millis(); // get actual millis() and keep it in variable actualMillis
  if (digitalRead(BUTTON_PIN) == LOW && actualMillis - lastBtnPress > 1000)  
  { 
    // is button pressed (inverted logic! button pressed = LOW) and debounced?
    if (myPowerState) 
    {     
      // flip myPowerState: if it was true, set it to false, vice versa
      myPowerState = false;
    } 
    else 
    {
      myPowerState = true;
    }
    digitalWrite(LED_PIN, myPowerState ? LOW : HIGH); // if myPowerState indicates device turned on: turn on led (builtin led uses inverted logic: LOW = LED ON / HIGH = LED OFF)

    // get Switch device back
    SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];
    // send powerstate event
    mySwitch.sendPowerStateEvent(myPowerState); // send the new powerState to SinricPro server
    Serial.print("Device ");
    Serial.print(mySwitch.getDeviceId());
    Serial.print(myPowerState ? "turned on" : "turn off");
    Serial.println(" (manually via flashbutton)");

    lastBtnPress = actualMillis;  // update last button press variable
  }
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
  // add device to SinricPro
  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];

  // set callback function to device
  mySwitch.onPowerState(onPowerState);

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
  pinMode(BUTTON_PIN, INPUT_PULLUP); // GPIO 0 as input, pulled high
  pinMode(LED_PIN, OUTPUT); // define LED GPIO as output
  digitalWrite(LED_PIN, HIGH); // turn off LED on bootup

  Serial.begin(BAUD_RATE); 
  while (!Serial);
  
#if defined(BOARD_TYPE)  
  Serial.println("\nStarting SAMD_WiFiNINA_Switch on " + String(BOARD_TYPE));
#else
  Serial.println("\nStarting SAMD_WiFiNINA_Switch on unknown board");
#endif  
  
  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  handleButtonPress();
  SinricPro.handle();
}
