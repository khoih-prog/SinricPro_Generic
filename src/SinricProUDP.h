/****************************************************************************************************************************
  SinricProUDP.h - Sinric Pro Library for boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
 *****************************************************************************************************************************/

#ifndef __SINRIC_PRO_UDP_H__
#define __SINRIC_PRO_UDP_H__

#if defined ESP8266
#include <ESP8266WiFi.h>
#endif
#if defined ESP32
#include <WiFi.h>
#endif

// KH
#if (WEBSOCKETS_NETWORK_TYPE == NETWORK_WIFININA)
#warning Use NETWORK_WIFININA WiFiUdp_Generic in SinricProUDP
#include <WiFiUdp_Generic.h>
#elif (WEBSOCKETS_NETWORK_TYPE == NETWORK_W5100)
#warning Use NETWORK_W5100 EthernetUdp in SinricProUDP
#include <EthernetUdp.h>
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
#endif
#if defined ESP32
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
    DEBUG_SINRIC("[SinricPro:UDP]: receiving request\r\n");
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
#endif
#if defined ESP32
  _udp.beginMulticast(UDP_MULTICAST_IP, UDP_MULTICAST_PORT);
#endif
}

/*
  void udpListener::sendMessage(String &message) {
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
