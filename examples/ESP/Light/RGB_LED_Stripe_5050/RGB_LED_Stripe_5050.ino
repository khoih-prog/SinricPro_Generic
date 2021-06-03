/****************************************************************************************************************************
  RGB_LED_Stripe_5050.ino
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
#else
  #define WEBSOCKET_SSL       true
  #include <WiFi.h>
#endif

#include "SinricPro_Generic.h"
#include "SinricProLight.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASS"

#define APP_KEY           "YOUR-APPKEY"             // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APPSECRET"          // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define LIGHT_ID          "YOUR-DEVICEID"           // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200                    // Change baudrate to your need for serial log

#if (ESP8266)
  #define BLUE_PIN          D5                        // PIN for BLUE Mosfet  - change this to your need (D5 = GPIO14 on ESP8266)
  #define RED_PIN           D6                        // PIN for RED Mosfet   - change this to your need (D6 = GPIO12 on ESP8266)
  #define GREEN_PIN         D7                        // PIN for GREEN Mosfet - change this to your need (D7 = GPIO13 on ESP8266)
#else
  #define BLUE_PIN          25                        // PIN for BLUE Mosfet  - change this to your need (25 = GPIO25/ADC18/DAC1 of ESP32)
  #define RED_PIN           26                        // PIN for RED Mosfet   - change this to your need (26 = GPIO26/ADC19/DAC2 of ESP32)
  #define GREEN_PIN         27                        // PIN for GREEN Mosfet - change this to your need (27 = GPIO27/ADC17/TOUCH7 of ESP32)

  // setting PWM properties
  #define FREQUENCY         5000
  #define LED_CHANNEL_R     0
  #define LED_CHANNEL_G     1
  #define LED_CHANNEL_B     2
  #define RESOLUTION_BITS   10                       // 1024
#endif

// Stores current device state with following initial values:
struct 
{                                            
  bool powerState = false;                          // initial state is off
  int brightness = 100;                             // initial brightness is set to 100
  struct 
  {
    byte r = 255;                                   // color
    byte g = 255;                                   // is set
    byte b = 255;                                   // to white
  } color;
} device_state;

// setStripe: sets the mosfets values corresponding to values stored in device_state
void setStripe() 
{
  int rValue = map(device_state.color.r * device_state.brightness, 0, 255 * 100, 0, 1023);  // calculate red value and map between 0 and 1023 for analogWrite
  int gValue = map(device_state.color.g * device_state.brightness, 0, 255 * 100, 0, 1023);  // calculate green value and map between 0 and 1023 for analogWrite
  int bValue = map(device_state.color.b * device_state.brightness, 0, 255 * 100, 0, 1023);  // calculate blue value and map between 0 and 1023 for analogWrite

  if (device_state.powerState == false) 
  {           
    // turn off?
    digitalWrite(RED_PIN,   LOW);                   // set
    digitalWrite(GREEN_PIN, LOW);                   // mosfets
    digitalWrite(BLUE_PIN,  LOW);                   // low
  } 
  else 
  {
#if (ESP8266)    
    analogWrite(RED_PIN,   rValue);                 // write red value to pin
    analogWrite(GREEN_PIN, gValue);                 // write green value to pin
    analogWrite(BLUE_PIN,  bValue);                 // write blue value to pin
#else
    ledcWrite(LED_CHANNEL_R, rValue);               // write red value to pin
    ledcWrite(LED_CHANNEL_G, gValue);               // write green value to pin
    ledcWrite(LED_CHANNEL_B, bValue);               // write blue value to pin
#endif
  }
}

bool onPowerState(const String &deviceId, bool &state) 
{
  (void) deviceId;
  
  device_state.powerState = state;                  // store the new power state
  setStripe();                                      // update the mosfets
  
  return true;
}

bool onBrightness(const String &deviceId, int &brightness) 
{
  (void) deviceId;
  
  device_state.brightness = brightness;             // store new brightness level
  setStripe();                                      // update the mosfets
  
  return true;
}

bool onAdjustBrightness(const String &deviceId, int &brightnessDelta) 
{
  (void) deviceId;
  
  device_state.brightness += brightnessDelta;       // calculate and store new absolute brightness
  brightnessDelta = device_state.brightness;        // return absolute brightness
  setStripe();                                      // update the mosfets
  
  return true;
}

bool onColor(const String &deviceId, byte &r, byte &g, byte &b) 
{
  (void) deviceId;
  
  device_state.color.r = r;                         // store new red value
  device_state.color.g = g;                         // store new green value
  device_state.color.b = b;                         // store new blue value
  setStripe();                                      // update the mosfets
  
  return true;
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
  
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() 
{
#if (ESP8266)  
  pinMode(RED_PIN,   OUTPUT);                       // set red-mosfet pin as output
  pinMode(GREEN_PIN, OUTPUT);                       // set green-mosfet pin as output
  pinMode(BLUE_PIN,  OUTPUT);                       // set blue-mosfet pin as output
#else
  // configure LED PWM functionalitites
  ledcSetup(LED_CHANNEL_R, FREQUENCY, RESOLUTION_BITS);
  ledcSetup(LED_CHANNEL_G, FREQUENCY, RESOLUTION_BITS);
  ledcSetup(LED_CHANNEL_B, FREQUENCY, RESOLUTION_BITS);
  
  // attach the channel to the pins to be controlled
  ledcAttachPin(RED_PIN,    LED_CHANNEL_R);
  ledcAttachPin(GREEN_PIN,  LED_CHANNEL_G);
  ledcAttachPin(BLUE_PIN,   LED_CHANNEL_B);
#endif


  Serial.begin(BAUD_RATE); 
  while (!Serial);
  
  Serial.println("\nStarting RGB_LED_Stripe_5050 on " + String(ARDUINO_BOARD));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();                               // handle SinricPro communication
}
