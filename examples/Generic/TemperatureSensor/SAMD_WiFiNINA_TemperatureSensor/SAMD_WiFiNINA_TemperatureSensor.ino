/****************************************************************************************************************************
  SAMD_WiFiNINA_TemperatureSensor.ino
  For Arduino SAMD21, Adafruit SAMD21, SAMD51 boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Example for how to use SinricPro Temperaturesensor device:
   - setup a temperature sensor device
   - send temperature event to SinricPro server when temperature has changed

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
#include "SinricProTemperaturesensor.h"

#include "DHT.h"                              // https://github.com/adafruit/DHT-sensor-library

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define TEMP_SENSOR_ID    "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200              // Change baudrate to your need

#define EVENT_WAIT_TIME   60000               // send event every 60 seconds

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic, connect pin 1 to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHT_PIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
#define DHT_PIN           5

// Uncomment whatever type you're using!
//#define DHT_TYPE      DHT11   // DHT 11
#define DHT_TYPE        DHT22   // DHT 22  (AM2302), AM2321
//#define DHT_TYPE      DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHT_PIN, DHT_TYPE);

bool  deviceIsOn;                               // Temeprature sensor on/off state
float temperature;                              // actual temperature
float humidity;                                 // actual humidity
float lastTemperature;                          // last known temperature (for compare)
float lastHumidity;                             // last known humidity (for compare)
unsigned long lastEvent = (-EVENT_WAIT_TIME);   // last time event has been sent


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
  Serial.println("TemperatureSensor turned " + String(state ? "on" : "off"));
  deviceIsOn = state; // turn on / off temperature sensor
  return true; // request handled properly
}

/* handleTemperatatureSensor()
   - Checks if Temperaturesensor is turned on
   - Checks if time since last event > EVENT_WAIT_TIME to prevent sending too much events
   - Get actual temperature and humidity and check if these values are valid
   - Compares actual temperature and humidity to last known temperature and humidity
   - Send event to SinricPro Server if temperature or humidity changed
*/
void handleTemperaturesensor() 
{
  // device is off...do nothing
  if (deviceIsOn == false) 
    return; 

  unsigned long actualMillis = millis();
  
  if (actualMillis - lastEvent < EVENT_WAIT_TIME) 
    return; //only check every EVENT_WAIT_TIME milliseconds

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //  temperature = dht.readTemperature(true);
  humidity = dht.readHumidity();                          // get actual humidity

  if (isnan(temperature) || isnan(humidity)) 
  { 
    // reading failed...
    Serial.println("DHT reading failed");       // print error message
    return;                                     // try again next time
  }

  // Check if any reads failed and exit early (to try again).
  if (temperature == lastTemperature || humidity == lastHumidity) 
    return; 

  SinricProTemperaturesensor &mySensor = SinricPro[TEMP_SENSOR_ID];     // get temperaturesensor device
  bool success = mySensor.sendTemperatureEvent(temperature, humidity);  // send event
  
  if (success) 
  {  
    // if event was sent successfuly, print temperature and humidity to serial
    Serial.println("Temperature: " + String(temperature, 1) + " Celsius\tHumidity: " + String(humidity, 1) + " %");
  } 
  else 
  {  
    // if sending event failed, print error message
    Serial.println("Something went wrong...Could not send Event to server!");
  }

  lastTemperature = temperature;  // save actual temperature for next compare
  lastHumidity = humidity;        // save actual humidity for next compare
  lastEvent = actualMillis;       // save actual time for next compare
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
  SinricProTemperaturesensor &mySensor = SinricPro[TEMP_SENSOR_ID];
  mySensor.onPowerState(onPowerState);

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
  
  SinricPro.restoreDeviceStates(true); // get latest known deviceState from server (is device turned on?)
}

// main setup function
void setup() 
{
  Serial.begin(BAUD_RATE);
  while (!Serial);

#if defined(BOARD_TYPE)
  Serial.println("\nStarting SAMD_WiFiNINA_TemperatureSensor on " + String(BOARD_TYPE));
#else
  Serial.println("\nStarting SAMD_WiFiNINA_TemperatureSensor on unknown SAMD board");
#endif

  dht.begin();

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
  handleTemperaturesensor();
}
