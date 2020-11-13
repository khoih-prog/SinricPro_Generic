/****************************************************************************************************************************
  AirQualitySensor_GP2Y1014AU0F.ino
  For ESP32/ESP8266 boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
 
/*
   Example for how to use SinricPro Air Quality Sensor with Sharp Dust Sensor (GP2Y1014AU0F) connected to WemosD1 Mini
   More information is here
   https://github.com/sharpsensoruser/sharp-sensor-demos/wiki/Application-Guide-for-Sharp-GP2Y1014AU0F-Dust-Sensor

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

#include <GP2YDustSensor.h> // https://github.com/luciansabo/GP2YDustSensor

#if (ESP8266)
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #include <WiFi.h>
#endif

#include "SinricPro_Generic.h"
#include "SinricProAirQualitySensor.h"

#define WIFI_SSID         ""
#define WIFI_PASS         ""
#define APP_KEY           ""      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        ""      // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define DEVICE_ID         ""      // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200  // Change baudrate to your need

// Air quality sensor event dispatch time.  Min is every 1 min.
#define MIN (1000UL * 60 * 1)
unsigned long dispatchTime = millis() + MIN;

#if (ESP32)
  #define SHARP_LED_PIN           5             // Pin D5 mapped to pin GPIO5/SPISS/VSPI_SS of ESP32
  #define SHARP_VO_PIN            32            // Pin D32 mapped to pin GPIO32/ADC4/TOUCH9 of ESP32 for analog input
#elif (ESP8266)
  #define SHARP_LED_PIN           5             // Pin D5 mapped to pin GPIO14/HSCLK of ESP8266
  #define SHARP_VO_PIN            A0            // pin A0 of ESP8266 for analog input
#endif

GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1014AU0F, SHARP_LED_PIN, SHARP_VO_PIN);

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
  SinricProAirQualitySensor& mySinricProAirQualitySensor = SinricPro[DEVICE_ID];

  // set callback function to device

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

void setupDustSensor() 
{
  //dustSensor.setBaseline(0.4); // set no dust voltage according to your own experiments
  //dustSensor.setCalibrationFactor(1.1); // calibrate against precision instrument
  dustSensor.begin();
}

void setup() 
{
  Serial.begin(BAUD_RATE); 
  while (!Serial);
  
  Serial.println("\nStarting AirQualitySensor_GP2Y1014AU0F on " + String(ARDUINO_BOARD));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));
  
  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();

  if ((long)(millis() - dispatchTime) >= 0) 
  {
    Serial.print("Dust density: ");
    Serial.print(dustSensor.getDustDensity());
    Serial.print(" ug/m3; Running average: ");
    Serial.print(dustSensor.getRunningAverage());
    Serial.println(" ug/m3");

    SinricProAirQualitySensor &mySinricProAirQualitySensor = SinricPro[DEVICE_ID]; // get air q sensor device

    int pm1 = 0;
    int pm2_5 = dustSensor.getRunningAverage();
    int pm10 = 0;

    mySinricProAirQualitySensor.sendAirQualityEvent(pm1, pm2_5, pm10, "PERIODIC_POLL");
    dispatchTime += MIN;

    Serial.println("Sending Air Quality event ..");
  }
}
