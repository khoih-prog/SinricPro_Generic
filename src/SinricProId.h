/*********************************************************************************************************************************
  SinricProId.h - Sinric Pro Library for boards

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
 **********************************************************************************************************************************/

#ifndef _SINRIC_PRO_ID_H_
#define _SINRIC_PRO_ID_H_

#include "SinricProDebug.h"

#define DEVICEID_BINLEN 12 // 12 bytes long
#define DEVICEID_STRLEN 24 // string needs to hold 24 characters

struct DeviceId_Bin_t 
{
  
#if (ESP8266 || ESP32)
  DeviceId_Bin_t() : _data{} {}
  
  uint8_t   _data[DEVICEID_BINLEN];
#else
  DeviceId_Bin_t() : _charData{} {}
  
  char      _charData[DEVICEID_STRLEN + 1];
#endif  
  
  void      fromString(const char * other);
  String    toString() const;


};

void DeviceId_Bin_t::fromString(const char* other) 
{

#if (ESP8266 || ESP32)

  char tmp;
  
  int sscanf_Value = sscanf(other,"%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%c",
    &_data[11], &_data[10], &_data[9], &_data[8], &_data[7],  &_data[6],  &_data[5], &_data[4],
    &_data[3],  &_data[2],  &_data[1], &_data[0], &tmp);
    
  bool _isValid = (sscanf_Value == sizeof(_data)) && (strlen(other) == DEVICEID_STRLEN);
  
  if (!_isValid) 
    memset((void*) &_data, 0, sizeof(_data));
   
#else
  
  //memset(_charData, 0, sizeof(_charData));
  strncpy(_charData, other, sizeof(_charData));
  
  SRP_LOGDEBUG1("DeviceId_Bin_t::fromString. DeviceId =", _charData);
    
  bool _isValid = (strlen(_charData) == DEVICEID_STRLEN);
  
  if (!_isValid) 
    memset(_charData, 0, sizeof(_charData));
  
#endif
}

String DeviceId_Bin_t::toString() const 
{

#if (ESP8266 || ESP32)

  char temp[DEVICEID_STRLEN + 1];

  sprintf(temp, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
    _data[11], _data[10], _data[9], _data[8], _data[7],  _data[6],  _data[5], _data[4],
    _data[3],  _data[2],  _data[1], _data[0]
  );
  
  SRP_LOGDEBUG1("DeviceId_Bin_t::toString. DeviceId =", temp);
  
  return String(temp);
  
#else
  
  SRP_LOGDEBUG1("DeviceId_Bin_t::toString. DeviceId =", _charData);
  
  return String(_charData);
  
#endif
}


#define APPKEY_BINLEN 16
#define APPKEY_STRLEN 36

struct AppKey_Bin_t 
{
  
#if (ESP8266 || ESP32)  
  AppKey_Bin_t() : _data{} {}
  
  uint8_t   _data[APPKEY_BINLEN];
#else
  AppKey_Bin_t() : _charData{} {}
  
  char      _charData[APPKEY_STRLEN + 1];
#endif 
  
  void      fromString(const char * other);
  String    toString() const;
  
 
};

void AppKey_Bin_t::fromString(const char* other) 
{
   
#if (ESP8266 || ESP32)

  char tmp;
   
  int sscanf_Value = sscanf(other,"%2hhx%2hhx%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%c",
    &_data[15], &_data[14], &_data[13], &_data[12], &_data[11], &_data[10], &_data[9],  &_data[8],
    &_data[7],  &_data[6],  &_data[5],  &_data[4],  &_data[3],  &_data[2],  &_data[1],  &_data[0], &tmp);

  bool _isValid = (sscanf_Value == sizeof(_data)) && (strlen(other) == APPKEY_STRLEN);
  
  if (!_isValid) 
    memset((void*) &_data, 0, sizeof(_data));
    
#else

  //memset(_charData, 0, sizeof(_charData));
  strncpy(_charData, other, sizeof(_charData));
  
  SRP_LOGDEBUG1("AppKey_Bin_t::fromString. AppKey =", _charData);
  
  bool _isValid = (strlen(_charData) == APPKEY_STRLEN);
  
  if (!_isValid) 
    memset(_charData, 0, sizeof(_charData));
    
#endif  
}

String AppKey_Bin_t::toString() const 
{
  
  
#if (ESP8266 || ESP32)

  char temp[APPKEY_STRLEN + 1];
  
  sprintf(temp, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
    _data[15], _data[14], _data[13], _data[12], _data[11], _data[10], _data[9],  _data[8],
    _data[7],  _data[6],  _data[5],  _data[4],  _data[3],  _data[2],  _data[1],  _data[0]
  );

  SRP_LOGDEBUG1("AppKey_Bin_t::toString. AppKey =", temp);
  
  return String(temp);
    
#else

  SRP_LOGDEBUG1("AppKey_Bin_t::toString. AppKey =", _charData);
  
  return String(_charData);
  
#endif
}

#define APPSECRET_BINLEN 32
#define APPSECRET_STRLEN 73

struct AppSecret_Bin_t 
{
#if (ESP8266 || ESP32)
  AppSecret_Bin_t() : _data{} {}
  
  uint8_t   _data[APPSECRET_BINLEN];
#else
  AppSecret_Bin_t() : _charData{} {}
  
  char      _charData[APPSECRET_STRLEN + 1];
#endif    
  
  void      fromString(const char * other);
  String    toString() const;


};

void AppSecret_Bin_t::fromString(const char* other) 
{
  
  
#if (ESP8266 || ESP32)

  char tmp;
  
  int sscanf_Value = sscanf(other, "%2hhx%2hhx%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%c",
    &_data[31], &_data[30], &_data[29], &_data[28], &_data[27], &_data[26], &_data[25], &_data[24],
    &_data[23], &_data[22], &_data[21], &_data[20], &_data[19], &_data[18], &_data[17], &_data[16],
    &_data[15], &_data[14], &_data[13], &_data[12], &_data[11], &_data[10], &_data[ 9], &_data[ 8],
    &_data[ 7], &_data[ 6], &_data[ 5], &_data[ 4], &_data[ 3], &_data[ 2], &_data[ 1], &_data[ 0], &tmp);
    
  bool _isValid = (sscanf_Value == sizeof(_data)) && (strlen(other) == APPSECRET_STRLEN); 
  
  if (!_isValid) 
    memset((void*) &_data, 0, sizeof(_data)); 
  
#else
 
  //memset(_charData, 0, sizeof(_charData));
  strncpy(_charData, other, sizeof(_charData));

  SRP_LOGDEBUG1("AppSecret_Bin_t::fromString. AppSecret =", _charData);
  
  bool _isValid = (strlen(_charData) == APPSECRET_STRLEN);
  
  if (!_isValid) 
    memset(_charData, 0, sizeof(_charData));
  
#endif
 
  
}

String AppSecret_Bin_t::toString() const 
{
  
#if (ESP8266 || ESP32)

  char temp[APPSECRET_STRLEN + 1];
  
  sprintf(temp, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
    _data[31], _data[30], _data[29], _data[28], _data[27], _data[26], _data[25], _data[24],
    _data[23], _data[22], _data[21], _data[20], _data[19], _data[18], _data[17], _data[16],
    _data[15], _data[14], _data[13], _data[12], _data[11], _data[10], _data[ 9], _data[ 8],
    _data[ 7], _data[ 6], _data[ 5], _data[ 4], _data[ 3], _data[ 2], _data[ 1], _data[ 0]
  );
   
  SRP_LOGDEBUG1("AppSecret_Bin_t::toString. AppSecret =", temp);
  
  return String(temp);
  
#else

  SRP_LOGDEBUG1("AppSecret_Bin_t::toString. AppSecret =", _charData);
  
  return String(_charData);
  
#endif  
}

template <class T>
class SinricProId 
{
  public:
    SinricProId() : _data() {};
    SinricProId(const char* other) { _data.fromString(other); }
    SinricProId(const String &other) { _data.fromString(other.c_str()); }
    SinricProId(const SinricProId &other) { copy(other); }
    SinricProId(const T &other) { copy(other); }
    SinricProId(const uint8_t other[], size_t size) { copy(other, size); }

    SinricProId operator=(const SinricProId &other) { copy(other); return *this; }
    SinricProId operator=(const char* other) { fromString(other); return *this; }
    SinricProId operator=(const String &other) { fromString(other.c_str()); return *this; }
    SinricProId operator=(const T &other) { copy(other); }

    bool operator==(const SinricProId &other) const { return compare(other); }
    bool operator==(const char* other) const { return compare((SinricProId) other); }
    bool operator==(const String& other) const { return compare((SinricProId) other); }
    bool operator==(const T &other) const { return compare((SinricProId) other); }

    bool operator!=(const SinricProId &other) const { return !compare(other); }
    bool operator!=(const char* other) const { return !compare(other); }
    bool operator!=(const String &other) const { return !compare(other); }
    bool operator!=(const T &other) const { return !compare(other); }
    
    operator bool() const { return isValid(); }
    operator String() const { return _data.toString(); }
    
    String toString() const { return _data.toString(); };
    
    // From v2.7.4
    //const char* c_str() const { return _data.toString().c_str(); }
    const char* c_str() const { static String str = _data.toString(); return str.c_str(); }
    //////
    
    bool isValid() const { return !compare(SinricProId<T>()); }
  
  private:
    void fromString(const char * other) { _data.fromString(other); }
    
#if (ESP8266 || ESP32)

    void copy(const SinricProId &other) 
    { 
      memcpy(_data._data, other._data._data, sizeof(_data._data)); 
    }    
    
    void copy(const T &other) 
    { 
      memcpy(_data, other, sizeof(_data)); 
    }
    
    void copy(const uint8_t other[], size_t size) 
    { 
      memcpy(_data._data, other, min(sizeof(_data._data), size)); 
    }
    
    bool compare(const SinricProId &other) const 
    { 
      return memcmp(_data._data, other._data._data, sizeof(_data._data)) == 0;
    }
    
#else

    void copy(const SinricProId &other) 
    { 
      memcpy(_data._charData, other._data._charData, sizeof(_data._charData)); 
    }
    
    void copy(const T &other) 
    { 
      memcpy(_data, other, sizeof(_data)); 
    }
    
    //void copy(const uint8_t other[], size_t size) { memcpy(_data._charData, other, min(sizeof(_data._charData), size)); }
    void copy(const uint8_t other[], size_t size) 
    { 
      memcpy(_data._charData, other, sizeof(_data._charData) < size ? sizeof(_data._charData) : size); 
    }
    
    bool compare(const SinricProId &other) const 
    { 
      return memcmp(_data._charData, other._data._charData, sizeof(_data._charData)) == 0;
    } 
    
#endif
    
    T _data;
};

typedef SinricProId<DeviceId_Bin_t>   DeviceId;
typedef SinricProId<AppKey_Bin_t>     AppKey;
typedef SinricProId<AppSecret_Bin_t>  AppSecret;

#endif  // _SINRIC_PRO_ID_H_
