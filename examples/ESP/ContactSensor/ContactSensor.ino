/****************************************************************************************************************************
  ContactSensor.ino
  For ESP32/ESP8266 boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/

/*
   Example for SinricPro Contactsensor device:
   - Setup contactsensor device
   - Support onPowerState to turn on / turn off contactsensor
   - Checks a contact sensor connected to CONTACT_PIN and send event if state changed

   If you encounter any issues:
   - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
   - ensure all dependent libraries are installed
     - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
     - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
   - open serial monitor and check whats happening
   - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
   - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
*/

#if !(defined(ESP8266) || defined(ESP32))
  #error This code is intended to run on the ESP32/ESP8266 boards ! Please check your Tools->Board setting.
#endif

// Uncomment the following line to enable serial debug output
//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
  #define DEBUG_ESP_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#if (ESP8266)
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #include <WiFi.h>
#endif

#include "SinricPro_Generic.h"
#include "SinricProContactsensor.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"
#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define CONTACT_ID        "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200              // Change baudrate to your need

#define CONTACT_PIN       5                   // PIN where contactsensor is connected to
// LOW  = contact is open
// HIGH = contact is closed

bool myPowerState = true;                     // assume device is turned on
bool lastContactState = false;
unsigned long lastChange = 0;

/**
   @brief Checks contactsensor connected to CONTACT_PIN

   If contactsensor state has changed, send event to SinricPro Server
   state from digitalRead():
        HIGH = contactsensor is closed
        LOW  = contactsensor is open
*/
void handleContactsensor() 
{
  if (!myPowerState) return;                            // if device switched off...do nothing

  unsigned long actualMillis = millis();
  
  if (actualMillis - lastChange < 250) 
    return;          // debounce contact state transitions (same as debouncing a pushbutton)

  bool actualContactState = digitalRead(CONTACT_PIN);   // read actual state of contactsensor

  if (actualContactState != lastContactState) 
  {         
    // if state has changed
    Serial.printf("Contactsensor is %s now\r\n", actualContactState ? "open" : "closed");
    
    lastContactState = actualContactState;              // update last known state
    lastChange = actualMillis;                          // update debounce time
    SinricProContactsensor &myContact = SinricPro[CONTACT_ID]; // get contact sensor device
    myContact.sendContactEvent(actualContactState);      // send event with actual state
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
  Serial.printf("Device %s turned %s (via SinricPro) \r\n", deviceId.c_str(), state ? "on" : "off");
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
  
  Serial.print("\n[WiFi]: IP-Address is ");
  Serial.println(WiFi.localIP());
}


// setup function for SinricPro
void setupSinricPro() 
{
  // add device to SinricPro
  SinricProContactsensor& myContact = SinricPro[CONTACT_ID];

  // set callback function to device
  myContact.onPowerState(onPowerState);

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
  
  Serial.println("\nStarting ContactSensor on " + String(ARDUINO_BOARD));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  pinMode(CONTACT_PIN, INPUT);

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  handleContactsensor();
  SinricPro.handle();
}
