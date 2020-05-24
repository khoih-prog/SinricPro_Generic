/****************************************************************************************************************************
  Generic_Ethernet_TemperatureSensor.ino
  For Generic boards, running W5x00 or ENC28J60 Ethernet shield

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

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0


#if defined(ESP8266) || defined(ESP32)
#error This code is not intended to run on the ESP32/ESP8266 boards ! Please check your Tools->Board setting.
#endif

// Uncomment the following line to enable serial debug output
#define ENABLE_DEBUG    true

#if ENABLE_DEBUG
  #define DEBUG_PORT            Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#define LOGWARN(x)     if(ENABLE_DEBUG) { Serial.print("[SINRIC_PRO] "); Serial.println(x); }
#define LOGWARN1(x,y)  if(ENABLE_DEBUG) { Serial.print("[SINRIC_PRO] "); Serial.print(x);\
                                          Serial.print(" "); Serial.println(y); }
                                          

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

//#define USE_UIP_ETHERNET   true
//#define USE_UIP_ETHERNET   false

#if USE_UIP_ETHERNET
  #define WEBSOCKETS_NETWORK_TYPE     NETWORK_ENC28J60
#endif

//#define USE_CUSTOM_ETHERNET     true

// Note: To rename ESP628266 Ethernet lib files to Ethernet_ESP8266.h and Ethernet_ESP8266.cpp
// In order to USE_ETHERNET_ESP8266
#if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )

  // To override the default CS/SS pin. Don't use unless you know exactly which pin to use
  //#define USE_THIS_SS_PIN   27//22  //21  //5 //4 //2 //15
  
  // Only one if the following to be true
  #define USE_ETHERNET2         false //true
  #define USE_ETHERNET3         false //true
  #define USE_ETHERNET_LARGE    false //true
  #define USE_ETHERNET_ESP8266  false //true
  
  #if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ESP8266 )
    #ifdef USE_CUSTOM_ETHERNET
      #undef USE_CUSTOM_ETHERNET
    #endif
    #define USE_CUSTOM_ETHERNET   true
  #endif
  
  #ifdef WEBSOCKETS_NETWORK_TYPE
    #undef WEBSOCKETS_NETWORK_TYPE
  #endif
  #define WEBSOCKETS_NETWORK_TYPE     NETWORK_W5100
  
  #if USE_ETHERNET3
    #include "Ethernet3.h"
    #warning Use Ethernet3 lib
  #elif USE_ETHERNET2
    #include "Ethernet2.h"
    #warning Use Ethernet2 lib
  #elif USE_ETHERNET_LARGE
    #include "EthernetLarge.h"
    #warning Use EthernetLarge lib
  #elif USE_ETHERNET_ESP8266
    #include "Ethernet_ESP8266.h"
    #warning Use Ethernet_ESP8266 lib
  #elif USE_CUSTOM_ETHERNET
    #include "Ethernet_XYZ.h"
    #warning Use Custom Ethernet library from EthernetWrapper. You must include a library here or error.
  #else
    #define USE_ETHERNET          true
    #include "Ethernet.h"
    #warning Use Ethernet lib
  #endif
  
  // Ethernet_Shield_W5200, EtherCard, EtherSia not supported
  // Select just 1 of the following #include if uncomment #define USE_CUSTOM_ETHERNET
  // Otherwise, standard Ethernet library will be used for W5x00

#endif    //#if !USE_UIP_ETHERNET

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

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


// setup function for setupEthernet connection
void setupEthernet() 
{
  #if USE_ETHERNET
    LOGWARN(F("=========== USE_ETHERNET ==========="));
  #elif USE_ETHERNET2
    LOGWARN(F("=========== USE_ETHERNET2 ==========="));
  #elif USE_ETHERNET3
    LOGWARN(F("=========== USE_ETHERNET3 ==========="));
  #elif USE_ETHERNET_LARGE
    LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
  #elif USE_ETHERNET_ESP8266
    LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
  #else
    LOGWARN(F("========================="));
  #endif
 
  LOGWARN(F("Default SPI pinout:"));
  LOGWARN1(F("MOSI:"), MOSI);
  LOGWARN1(F("MISO:"), MISO);
  LOGWARN1(F("SCK:"),  SCK);
  LOGWARN1(F("SS:"),   SS);
  LOGWARN(F("========================="));
   
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif
       
  LOGWARN1(F("Use default CS/SS pin : "), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries

    Ethernet.init (USE_THIS_SS_PIN);

  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
    
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
                    
  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

    // start the ethernet connection and the server:
  // Use Static IP
  //Ethernet.begin(mac, ip);
  // Use DHCP dynamic IP and random mac
  srand(millis());
  uint16_t index = rand() % NUMBER_OF_MAC;

  Serial.print("Index = ");
  Serial.println(index);

  Ethernet.begin(mac[index]);
  
  Serial.print("Connected!\n[Ethernet]: IP-Address is ");
  Serial.println(Ethernet.localIP());
}

// setup function for SinricPro
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

  Serial.println("\nStarting Generic_Ethernet_TemperatureSensor");

  dht.begin();

  setupEthernet();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
  handleTemperaturesensor();
}
