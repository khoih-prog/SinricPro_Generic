/****************************************************************************************************************************
  Generic_Ethernet_AQSensor_GP2Y1014AU0F.ino
  For Generic boards, running W5x00 or ENC28J60 Ethernet shield

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

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0

#include "defines.h"

#include "SinricPro_Generic.h"
#include "SinricProAirQualitySensor.h"

#include <GP2YDustSensor.h> // https://github.com/luciansabo/GP2YDustSensor

// Air quality sensor event dispatch time.  Min is every 1 min.
#define MIN (1000UL * 60 * 1)
unsigned long dispatchTime = millis() + MIN;

#define SHARP_LED_PIN           5             // Select a digital output pin for LED according to your board
#define SHARP_VO_PIN            6             // Select an analog input pin to read dust density according to your board

GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1014AU0F, SHARP_LED_PIN, SHARP_VO_PIN);

// setup function for setupEthernet connection
void setupEthernet() 
{
  #if USE_ETHERNET
    SRP_LOGWARN(F("=========== USE_ETHERNET ==========="));
  #elif USE_ETHERNET2
    SRP_LOGWARN(F("=========== USE_ETHERNET2 ==========="));
  #elif USE_ETHERNET3
    SRP_LOGWARN(F("=========== USE_ETHERNET3 ==========="));
  #elif USE_ETHERNET_LARGE
    SRP_LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
  #elif USE_ETHERNET_ESP8266
    SRP_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
  #else
    SRP_LOGWARN(F("========================="));
  #endif
 
  SRP_LOGWARN(F("Default SPI pinout:"));
  SRP_LOGWARN1(F("MOSI:"), MOSI);
  SRP_LOGWARN1(F("MISO:"), MISO);
  SRP_LOGWARN1(F("SCK:"),  SCK);
  SRP_LOGWARN1(F("SS:"),   SS);
  SRP_LOGWARN(F("========================="));
   
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif
       
  SRP_LOGWARN1(F("Use default CS/SS pin : "), USE_THIS_SS_PIN);

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
  //srand(millis());
  //uint16_t index = rand() % NUMBER_OF_MAC;
  uint16_t index = millis() % NUMBER_OF_MAC;

  Serial.print("Index = ");
  Serial.println(index);

  Ethernet.begin(mac[index]);
  
  Serial.print("Connected!\n[Ethernet]: IP-Address is ");
  Serial.println(Ethernet.localIP());
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
  
  Serial.println("\nStarting Generic_Ethernet_AQSensor_GP2Y1014AU0F on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));
  
  setupEthernet();
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

    int pm1   = 0;
    int pm2_5 = dustSensor.getRunningAverage();
    int pm10  = 0;

    mySinricProAirQualitySensor.sendAirQualityEvent(pm1, pm2_5, pm10, "PERIODIC_POLL");
    dispatchTime += MIN;

    Serial.println("Sending Air Quality event ..");
  }
}
