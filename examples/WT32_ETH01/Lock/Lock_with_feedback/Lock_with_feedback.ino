/****************************************************************************************************************************
  Lock_with_feedback.ino
  For ESP32/ESP8266 boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
/*
   Example for smart lock with feedback

   The lock must give a feedback signal on pin defined in LOCK_STATE_PIN
   Alternative: Use a contact sensor, indicating the current lock state
   HIGH on LOCK_STATE_PIN means lock is locked
   LOW on LOCK_STATE_PIN means lock is unlocked

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
#include "SinricProLock.h"

#define APP_KEY           "YOUR_APP_KEY_HERE"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR_APP_SECRET_HERE"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define LOCK_ID           "YOUR_DEVICE_ID_HERE"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200                   // Change baudrate to your need

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

// LOCK_PIN where the lock is connected to: HIGH = locked, LOW = unlocked
// LOCK_STATE_PIN where the lock feedback is connected to (HIGH:locked, LOW:unlocked)
#define LOCK_PIN                  2              // Pin D2 mapped to pin GPIO2 of WT32_ETH01
#define LOCK_STATE_PIN            4              // Pin D4 mapped to pin GPIO4 of WT32_ETH01

bool lastLockState;

bool onLockState(String deviceId, bool &lockState) 
{
  Serial.printf("Device %s is %s\r\n", deviceId.c_str(), lockState ? "locked" : "unlocked");
  digitalWrite(LOCK_PIN, lockState);
  
  return true;
}

void checkLockState() 
{
  bool currentLockState = digitalRead(LOCK_STATE_PIN);                                    // get current lock state
  
  if (currentLockState == lastLockState) 
    return;                                                                               // do nothing if state didn't changed
    
  Serial.printf("Lock has been %s manually\r\n", currentLockState ? "locked" : "unlocked"); // print current lock state to serial
  
  lastLockState = currentLockState;                                                       // update last known lock state
  SinricProLock &myLock = SinricPro[LOCK_ID];                                             // get the LockDevice
  myLock.sendLockStateEvent(currentLockState);                                            // update LockState on Server
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
  SinricProLock &myLock = SinricPro[LOCK_ID];
  myLock.onLockState(onLockState);

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
  
  Serial.print(F("\nStart Lock_with_feedback on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  Serial.println(SINRICPRO_VERSION_STR);

  pinMode(LOCK_PIN, OUTPUT);
  pinMode(LOCK_STATE_PIN, INPUT);

  setupETH();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
  checkLockState();
}
