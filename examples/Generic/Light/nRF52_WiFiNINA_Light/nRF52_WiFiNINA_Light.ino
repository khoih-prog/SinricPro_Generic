/****************************************************************************************************************************
  nRF52_WiFiNINA_Light.ino
  For Adafruit nRF52 boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

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
#include "SinricProLight.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define LIGHT_ID         "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200                // Change baudrate to your need

// define array of supported color temperatures
int colorTemperatureArray[] = { 2200, 2700, 4000, 5500, 7000 };
int max_color_temperatures = sizeof(colorTemperatureArray) / sizeof(colorTemperatureArray[0]); // calculates how many elements are stored in colorTemperature array

// a map used to convert a given color temperature into color temperature index (used for colorTemperatureArray)
std::map<int, int> colorTemperatureIndex;

// initializes the map above with color temperatures and index values
// so that the map can be used to do a reverse search like
// int index = colorTemperateIndex[4000]; <- will result in index == 2
void setupColorTemperatureIndex() 
{
  Serial.println("Setup color temperature lookup table");
  for (int i = 0; i < max_color_temperatures; i++) 
  {
    colorTemperatureIndex[colorTemperatureArray[i]] = i;
    Serial.println("colorTemperatureIndex[" + String(colorTemperatureArray[i]) + "] = " + String(colorTemperatureIndex[colorTemperatureArray[i]]));
  }
}

// we use a struct to store all states and values for our light
struct 
{
  bool powerState = false;
  int brightness = 0;
  struct 
  {
    byte r = 0;
    byte g = 0;
    byte b = 0;
  } color;
  
  int colorTemperature = colorTemperatureArray[0]; // set colorTemperature to first element in colorTemperatureArray array
} device_state;

bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.println("Device " + deviceId + String(state ? " turned on" : " turn off") + " (via SinricPro)" );
  
  device_state.powerState = state;
  return true; // request handled properly
}

bool onBrightness(const String &deviceId, int &brightness) 
{
  device_state.brightness = brightness;
  
  Serial.println("Device " + deviceId + " brightness level changed to " + String(brightness));
  
  return true;
}

bool onAdjustBrightness(const String &deviceId, int brightnessDelta) 
{
  device_state.brightness += brightnessDelta;
  
  Serial.println("Device " + deviceId + " brightness level changed about " + String(brightnessDelta) + " to " + String(device_state.brightness));
  
  brightnessDelta = device_state.brightness;
  return true;
}

bool onColor(const String &deviceId, byte &r, byte &g, byte &b) 
{
  device_state.color.r = r;
  device_state.color.g = g;
  device_state.color.b = b;
  
  Serial.println("Device " + deviceId + " color changed to " + String(device_state.color.r) + ", " 
                    + String(device_state.color.g) + ", " + String(device_state.color.g) + "(RGB)");
  
  return true;
}

bool onColorTemperature(const String &deviceId, int &colorTemperature) 
{
  device_state.colorTemperature = colorTemperature;
  
  Serial.println("Device " + deviceId + " color temperature changed to " + String(device_state.colorTemperature));
  
  return true;
}

bool onIncreaseColorTemperature(const String &deviceId, int &colorTemperature) 
{
  int index = colorTemperatureIndex[device_state.colorTemperature];               // get index of stored colorTemperature
  index++;                                                                        // do the increase
  if (index < 0)
    index = 0;                                                                    // make sure that index stays within array boundaries
  if (index > max_color_temperatures - 1) 
    index = max_color_temperatures - 1;                                           // make sure that index stays within array boundaries
    
  device_state.colorTemperature = colorTemperatureArray[index];                  // get the color temperature value
  
  Serial.println("Device " + deviceId + " increased color temperature to " + String(device_state.colorTemperature));
  
  colorTemperature = device_state.colorTemperature;                              // return current color temperature value
  return true;
}

bool onDecreaseColorTemperature(const String &deviceId, int &colorTemperature) 
{
  int index = colorTemperatureIndex[device_state.colorTemperature];               // get index of stored colorTemperature
  index--;                                                                        // do the decrease
  if (index < 0)
    index = 0;                                                                    // make sure that index stays within array boundaries
  if (index > max_color_temperatures - 1) 
    index = max_color_temperatures - 1;                                           // make sure that index stays within array boundaries
    
  device_state.colorTemperature = colorTemperatureArray[index];                  // get the color temperature value
  
  Serial.println("Device " + deviceId + " decreased color temperature to " + String(device_state.colorTemperature));
  
  colorTemperature = device_state.colorTemperature;                              // return current color temperature value
  return true;
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
  // get a new Light device from SinricPro
  SinricProLight &myLight = SinricPro[LIGHT_ID];

  // set callback function to device
  myLight.onPowerState(onPowerState);
  myLight.onBrightness(onBrightness);
  myLight.onAdjustBrightness(onAdjustBrightness);
  myLight.onColor(onColor);
  myLight.onColorTemperature(onColorTemperature);
  myLight.onIncreaseColorTemperature(onIncreaseColorTemperature);
  myLight.onDecreaseColorTemperature(onDecreaseColorTemperature);

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
  Serial.println("\nStarting nRF52_WiFiNINA_Light on " + String(BOARD_TYPE));
#else
  Serial.println("\nStarting nRF52_WiFiNINA_Light on unknown nRF52 board");
#endif

  setupColorTemperatureIndex(); // setup our helper map
  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
