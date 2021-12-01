/****************************************************************************************************************************
  Blinds.ino
  For ESP32/ESP8266 boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
/*
   Example for how to use Thermostat device

   If you encounter any issues:
   - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
   - ensure all dependent libraries are installed
     - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
     - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
   - open serial monitor and check whats happening
   - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
   - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
*/

#if !(defined(ESP32))
  #error This code is intended to run on the WT32 boards and ESP32 platform ! Please check your Tools->Board setting.
#endif

// Uncomment the following line to enable serial debug output
//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
  #define DEBUG_ESP_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#define WEBSOCKET_SSL     true

#include <WebServer_WT32_ETH01.h>

#include "SinricPro_Generic.h"
#include "SinricProThermostat.h"

#define APP_KEY           "YOUR_APP_KEY_HERE"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR_APP_SECRET_HERE"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define THERMOSTAT_ID     "YOUR_DEVICE_ID_HERE"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200                   // Change baudrate to your need

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

float globalTemperature;
bool globalPowerState;

bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.printf("Thermostat %s turned %s\r\n", deviceId.c_str(), state ? "on" : "off");
  globalPowerState = state;
  
  return true; // request handled properly
}

bool onTargetTemperature(const String &deviceId, float &temperature) 
{
  Serial.printf("Thermostat %s set temperature to %f\r\n", deviceId.c_str(), temperature);
  globalTemperature = temperature;
  
  return true;
}

bool onAdjustTargetTemperature(const String & deviceId, float &temperatureDelta) 
{
  globalTemperature += temperatureDelta;  // calculate absolut temperature
  Serial.printf("Thermostat %s changed temperature about %f to %f", deviceId.c_str(), temperatureDelta, globalTemperature);
  temperatureDelta = globalTemperature; // return absolut temperature
  
  return true;
}

bool onThermostatMode(const String &deviceId, String &mode) 
{
  Serial.printf("Thermostat %s set to mode %s\r\n", deviceId.c_str(), mode.c_str());
  
  return true;
}

// setup function for ETH connection
void setupETH() 
{
  Serial.print("[ETH]: Connecting");
  
  // To be called before ETH.begin()
  WT32_ETH01_onEvent();

  //bool begin(uint8_t phy_addr=ETH_PHY_ADDR, int power=ETH_PHY_POWER, int mdc=ETH_PHY_MDC, int mdio=ETH_PHY_MDIO, 
  //           eth_phy_type_t type=ETH_PHY_TYPE, eth_clock_mode_t clk_mode=ETH_CLK_MODE);
  //ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  WT32_ETH01_waitForConnect();
  
  Serial.print("[ETH]: IP-Address is ");
  Serial.println(ETH.localIP());
}

void setupSinricPro() 
{
  SinricProThermostat &myThermostat = SinricPro[THERMOSTAT_ID];
  myThermostat.onPowerState(onPowerState);
  myThermostat.onTargetTemperature(onTargetTemperature);
  myThermostat.onAdjustTargetTemperature(onAdjustTargetTemperature);
  myThermostat.onThermostatMode(onThermostatMode);

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
  
  Serial.print(F("\nStart Thermostat on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  Serial.println(SINRICPRO_VERSION_STR);
  
  setupETH();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
