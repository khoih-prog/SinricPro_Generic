/****************************************************************************************************************************
  SinricProUDP.h - Sinric Pro Library for boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as SAMD21, SAMD51, Adafruit's nRF52 boards, Teensy, SAM DUE, STM32, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license 

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version: 2.8.5
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
  2.5.1   K Hoang      02/08/2020 Add support to STM32F/L/H/G/WB/MP1. Add debug feature, examples. Restructure examples.
                                  Sync with SinricPro v2.5.1: add Speaker SelectInput, Camera. Enable Ethernetx lib support.
  2.6.1   K Hoang      15/08/2020 Sync with SinricPro v2.6.1: add AirQualitySensor, Camera Class.
  2.7.0   K Hoang      06/10/2020 Sync with SinricPro v2.7.0: Added AppKey, AppSecret and DeviceId classes and RTT function.
  2.7.4   K Hoang      12/11/2020 Sync with SinricPro v2.7.4. Add WIO Terminal support and examples
  2.8.0   K Hoang      10/12/2020 Sync with SinricPro v2.8.0. Add examples. Use std::queue instead of QueueList. SSL Option.
  2.8.1   K Hoang      02/06/2021 Add support to RP2040 using Arduino-mbed or arduino-pico core with WiFiNINA or Ethernet
  2.8.2   K Hoang      20/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720A)
  2.8.3   K Hoang      12/10/2021 Update `platform.ini` and `library.json`
  2.8.4   K Hoang      01/12/2021 Auto detect ESP32 core for LittleFS. Fix bug in examples for WT32_ETH01
  2.8.5   K Hoang      23/04/2022 Use Ethernet_Generic library as default. Add support to Portenta_H7, etc.
 *****************************************************************************************************************************/

#ifndef __SINRIC_PRO_UDP_H__
#define __SINRIC_PRO_UDP_H__

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiUdp.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiUdp.h>
#elif (SINRIC_PRO_USING_RTL8720DN)
  #warning Use SINRIC_PRO_USING_RTL8720DN rpcWiFi Library in SinricProUDP
  #include <rpcWiFi.h>
  #include <WiFiUdp.h>
// KH
#elif (WEBSOCKETS_NETWORK_TYPE == NETWORK_WIFININA)
  #warning Use NETWORK_WIFININA WiFiUdp_Generic in SinricProUDP
  #include <WiFiUdp_Generic.h>
#elif (WEBSOCKETS_NETWORK_TYPE == NETWORK_W5100)
  // KH, add in v2.5.1 to support Ethernet2, Ethernet3 and EthernetLarge libraries
  #if (USE_ETHERNET || USE_ETHERNET_LARGE)
    #include <EthernetUdp.h>
    #warning Use NETWORK_W5100 EthernetUdp in SinricProUDP
  #elif USE_ETHERNET2
    #include <EthernetUdp2.h>
    #warning Use NETWORK_W5100 EthernetUdp2 in SinricProUDP
  #elif USE_ETHERNET3
    #include <EthernetUdp3.h>
    #warning Use NETWORK_W5100 EthernetUdp3 in SinricProUDP
  #endif
  //////
#elif (WEBSOCKETS_NETWORK_TYPE == NETWORK_ENC28J60)
  #warning Use NETWORK_ENC28J60 UIPUdp in SinricProUDP
  #include <UIPUdp.h>
#else
  #warning Use default WiFi in SinricProUDP
  #include <WiFiUdp.h>
#endif


#include "SinricProQueue.h"

class udpListener
{
  public:
    void begin(SinricProQueue_t* receiveQueue);
    void handle();
    void sendMessage(String &message);
    void stop();
  private:
#if (WEBSOCKETS_NETWORK_TYPE == NETWORK_WIFININA)
    WiFiUDP _udp;
#elif (WEBSOCKETS_NETWORK_TYPE == NETWORK_W5100)
    EthernetUDP _udp;
#elif (WEBSOCKETS_NETWORK_TYPE == NETWORK_ENC28J60)
    UIPUDP  _udp;
#else
    WiFiUDP _udp;
#endif

    SinricProQueue_t* receiveQueue;
};

void udpListener::begin(SinricProQueue_t* receiveQueue)
{
  this->receiveQueue = receiveQueue;
#if defined ESP8266
  _udp.beginMulticast(WiFi.localIP(), UDP_MULTICAST_IP, UDP_MULTICAST_PORT);
#elif ( defined(ESP32) || SINRIC_PRO_USING_RTL8720DN)
  _udp.beginMulticast(UDP_MULTICAST_IP, UDP_MULTICAST_PORT);
#endif
}

void udpListener::handle()
{
  if (!_udp.available())
    return;

  int len = _udp.parsePacket();

  if (len)
  {
    char buffer[1024];
    int n = _udp.read(buffer, 1024);
    buffer[n] = 0;
    SinricProMessage* request = new SinricProMessage(IF_UDP, buffer);
    SRP_LOGDEBUG("SinricPro:UDP: receiving request");
    receiveQueue->push(request);
  }
}

void udpListener::sendMessage(String &message)
{
  _udp.beginPacket(_udp.remoteIP(), _udp.remotePort());
  _udp.print(message);
  _udp.endPacket();
  // restart UDP??
#if defined ESP8266
  _udp.beginMulticast(WiFi.localIP(), UDP_MULTICAST_IP, UDP_MULTICAST_PORT);
#elif (defined(ESP32) || SINRIC_PRO_USING_RTL8720DN)
  _udp.beginMulticast(UDP_MULTICAST_IP, UDP_MULTICAST_PORT);
#endif
}

/*
  void udpListener::sendMessage(String &message) 
  {
  WiFiUDP UDPsender;
  UDPsender.beginPacket(_udp.remoteIP(), _udp.remotePort());
  UDPsender.print(message);
  UDPsender.endPacket();
  }
*/

void udpListener::stop()
{
  _udp.stop();
}

#endif    //__SINRIC_PRO_UDP_H__
