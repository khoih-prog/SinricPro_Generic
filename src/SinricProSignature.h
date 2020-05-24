/****************************************************************************************************************************
  SinricProSignature.h - Sinric Pro Library for boards

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

#ifndef _SIGNATURE_H_
#define _SIGNATURE_H_

#include "extralib/Crypto/Crypto.h"
#include "extralib/Crypto/Base64.h"

String calculateSignature(const char* key, JsonDocument &jsonMessage)
{
  if (!jsonMessage.containsKey("payload"))
    return String("");

  String jsonPayload; serializeJson(jsonMessage["payload"], jsonPayload);

  byte rawSigBuf[SHA256HMAC_SIZE];
  String test;

  SHA256HMAC hmac((byte*) key, strlen(key));
  hmac.doUpdate(jsonPayload.c_str(), jsonPayload.length());
  hmac.doFinal(rawSigBuf);

  int b64_len = base64_enc_len(SHA256HMAC_SIZE);
  char sigBuf[b64_len + 1];
  base64_encode(sigBuf, (char*) rawSigBuf, SHA256HMAC_SIZE);
  sigBuf[b64_len] = 0;
  String result = sigBuf;

  return result;
}

bool verifyMessage(String key, JsonDocument &jsonMessage)
{
  String jsonHash = jsonMessage["signature"]["HMAC"];
  String calculatedHash = calculateSignature(key.c_str(), jsonMessage);
  return jsonHash == calculatedHash;
}

String signMessage(String key, JsonDocument &jsonMessage)
{
  if (!jsonMessage.containsKey("signature"))
    jsonMessage.createNestedObject("signature");

  jsonMessage["signature"]["HMAC"] = calculateSignature(key.c_str(), jsonMessage);
  String signedMessageString;
  serializeJson(jsonMessage, signedMessageString);
  return signedMessageString;
}

#endif // _SIGNATURE_H_
