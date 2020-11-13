/****************************************************************************************************************************
  nRF52_WiFiNINA_TemperatureSensor.ino
  For Adafruit nRF52 boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 **********************************************************************************************************************************/

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0

#include "defines.h"

#include "SinricPro_Generic.h"
#include "SinricProTemperaturesensor.h"

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

  Serial.println("\nStarting SAMD_WiFiNINA_TemperatureSensor on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  dht.begin();

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
  handleTemperaturesensor();
}
