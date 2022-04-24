/****************************************************************************************************************************
  Generic_Ethernet_Light.ino
  For Generic boards, running W5x00 or ENC28J60 Ethernet shield

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
#include "SinricProLight.h"

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

// setup function for setupEthernet connection
void setupEthernet() 
{
#if USE_ETHERNET_PORTENTA_H7
  SRP_LOGWARN(F("======== USE_PORTENTA_H7_ETHERNET ========"));
#elif USE_NATIVE_ETHERNET
  SRP_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_ETHERNET_GENERIC
  SRP_LOGWARN(F("=========== USE_ETHERNET_GENERIC ==========="));  
#elif USE_ETHERNET_ESP8266
  SRP_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
#elif USE_ETHERNET_ENC
  SRP_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));  
#else
  SRP_LOGWARN(F("========================="));
#endif

#if !(USE_NATIVE_ETHERNET || USE_ETHERNET_PORTENTA_H7)

#if (USING_SPI2)
  #if defined(CUR_PIN_MISO)
    SRP_LOGWARN(F("Default SPI pinout:"));
    SRP_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
    SRP_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
    SRP_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
    SRP_LOGWARN1(F("SS:"),   CUR_PIN_SS);
    SRP_LOGWARN(F("========================="));
  #endif
#else
  SRP_LOGWARN(F("Default SPI pinout:"));
  SRP_LOGWARN1(F("MOSI:"), MOSI);
  SRP_LOGWARN1(F("MISO:"), MISO);
  SRP_LOGWARN1(F("SCK:"),  SCK);
  SRP_LOGWARN1(F("SS:"),   SS);
  SRP_LOGWARN(F("========================="));
#endif

#if ETHERNET_USE_RPIPICO

  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);
  
  // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
  #ifndef USE_THIS_SS_PIN
    #if defined(ARDUINO_ARCH_MBED)
      #define USE_THIS_SS_PIN   5     // For Arduino Mbed core
    #else  
      #define USE_THIS_SS_PIN   17    // For E.Philhower core
    #endif
  #endif

  SRP_LOGWARN1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    // Default pin 5/17 to SS/CS
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
     
  #endif    //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#else   // ETHERNET_USE_RPIPICO
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif

  #if defined(BOARD_NAME)
    SRP_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
  #else
    SRP_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
  #endif

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
    
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#endif    // ETHERNET_USE_RPIPICO

#endif    // #if !(USE_NATIVE_ETHERNET)

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[0], ip);
  Ethernet.begin(mac[index]);

#if !(USE_NATIVE_ETHERNET || USE_ETHERNET_PORTENTA_H7)
  SRP_LOGWARN(F("========================="));
  
  #if defined(CUR_PIN_MISO)
    SRP_LOGWARN(F("Currently Used SPI pinout:"));
    SRP_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
    SRP_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
    SRP_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
    SRP_LOGWARN1(F("SS:"),   CUR_PIN_SS);
  #else
    SRP_LOGWARN(F("Currently Used SPI pinout:"));
    SRP_LOGWARN1(F("MOSI:"), MOSI);
    SRP_LOGWARN1(F("MISO:"), MISO);
    SRP_LOGWARN1(F("SCK:"),  SCK);
    SRP_LOGWARN1(F("SS:"),   SS);
  #endif
  
  SRP_LOGWARN(F("========================="));

#elif (USE_ETHERNET_PORTENTA_H7)
  if (Ethernet.hardwareStatus() == EthernetNoHardware) 
  {
    Serial.println("No Ethernet found. Stay here forever");
    
    while (true) 
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  
  if (Ethernet.linkStatus() == LinkOFF) 
  {
    Serial.println("Not connected Ethernet cable");
  }
#endif

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());
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

  Serial.println("\nStarting Generic_Ethernet_Light on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupColorTemperatureIndex(); // setup our helper map
  setupEthernet();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
