/****************************************************************************************************************************
  Light_FastLED_WS2812.ino
  For ESP32/ESP8266 boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
/*
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

#include <Arduino.h>

#if (ESP8266)
  #define WEBSOCKET_SSL       true
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #define WEBSOCKET_SSL       true
  #include <WiFi.h>
#endif

#define FASTLED_ESP8266_DMA
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

#include "SinricPro_Generic.h"
#include "SinricProLight.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"
#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define LIGHT_ID          "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200              // Change baudrate to your need

#define NUM_LEDS          1                   // how much LEDs are on the stripe
#define LED_PIN           3                   // LED stripe is connected to PIN 3

bool powerState;
int globalBrightness = 100;
CRGB leds[NUM_LEDS];

bool onPowerState(const String &deviceId, bool &state) 
{
  (void) deviceId;
  
  powerState = state;
  
  if (state) 
  {
    FastLED.setBrightness(map(globalBrightness, 0, 100, 0, 255));
  } 
  else 
  {
    FastLED.setBrightness(0);
  }
  
  FastLED.show();
  
  return true; // request handled properly
}

bool onBrightness(const String &deviceId, int &brightness) 
{
  (void) deviceId;
  
  globalBrightness = brightness;
  FastLED.setBrightness(map(brightness, 0, 100, 0, 255));
  FastLED.show();
  
  return true;
}

bool onAdjustBrightness(const String &deviceId, int brightnessDelta) 
{
  (void) deviceId;
  
  globalBrightness += brightnessDelta;
  brightnessDelta = globalBrightness;
  FastLED.setBrightness(map(globalBrightness, 0, 100, 0, 255));
  FastLED.show();
  
  return true;
}

bool onColor(const String &deviceId, byte &r, byte &g, byte &b) 
{
  (void) deviceId;
  
  fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
  FastLED.show();
  
  return true;
}

void setupFastLED() 
{
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(map(globalBrightness, 0, 100, 0, 255));
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
}

// setup function for WiFi connection
void setupWiFi() 
{
  Serial.print("\n[WiFi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(250);
  }
  
  Serial.print("\n[WiFi]: IP-Address is ");
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

  // setup SinricPro
  SinricPro.onConnected([]() 
  {
    Serial.println("Connected to SinricPro");
  });
  
  SinricPro.onDisconnected([]() 
  {
    Serial.println("Disconnected from SinricPro");
  });
  
  SinricPro.restoreDeviceStates(true);
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() 
{
  Serial.begin(BAUD_RATE); 
  while (!Serial);
  
  Serial.println("\nStarting Light_FastLED_WS2812 on " + String(ARDUINO_BOARD));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));
  
  setupFastLED();
  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
