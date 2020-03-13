//Author: Leonardo La Rocca info@melopero.com

#include "MP_UBX.h"


String msgClassToString(uint8_t msgClass){
    if (msgClass == NAV_CLASS)
        return "Navigation";
    else if (msgClass == RXM_CLASS)
        return "Receiver Manager";
    else if (msgClass == INF_CLASS)
        return "Information";
    else if (msgClass == ACK_CLASS)
        return "ACK/NAK";
    else if (msgClass == CFG_CLASS)
        return "Configuration";
    else if (msgClass == UPD_CLASS)
        return "Firmware update";
    else if (msgClass == MON_CLASS)
        return "Monitoring";
    else if (msgClass == AID_CLASS)
        return "AssistNow messages";
    else if (msgClass == TIM_CLASS)
        return "Timing";
    else if (msgClass == ESF_CLASS)
        return "External Sensor Fusion Messages";
    else if (msgClass == MGA_CLASS)
        return "Multiple GNSS Assistance Messages";
    else if (msgClass == LOG_CLASS)
        return "Logging";
    else if (msgClass == SEC_CLASS)
        return "Security";
    else if (msgClass == HNR_CLASS)
        return "High rate navigation results";

    return "Couldn't find class";
  }


String getGNSSFixType(uint8_t fixFlag){
  if (fixFlag == 0)
    return "no fix";
  else if (fixFlag == 1)
    return "dead reckoning only";
  else if (fixFlag == 2)
    return "2D-fix";
  else if (fixFlag == 3)
    return "3D-fix";
  else if (fixFlag == 4)
    return "GNSS + dead reckoning combined";
  else if (fixFlag == 5)
    return "time only fix";
  else
    return "reserved / no fix";
}

void computeChecksum(UbxMessage &msg){
  msg.checksumA = msg.msgClass;
  msg.checksumB = msg.checksumA;

  msg.checksumA += msg.msgId;
  msg.checksumB += msg.checksumA;

  msg.checksumA += msg.length % (1<<8);
  msg.checksumB += msg.checksumA;

  msg.checksumA += msg.length >> 8;
  msg.checksumB += msg.checksumA;

  for (int i = 0; i < msg.length; i++){
    msg.checksumA += msg.payload[i];
    msg.checksumB += msg.checksumA;
  }
}

/* Resets the payload to all zero's*/
void resetPayload(UbxMessage &msg){
  for (int i = 0; i < msg.length; i++)
    msg.payload[i] = 0;
}

String ubxMessageToString(UbxMessage &msg){
  String string = "Class : ";
  string += msg.msgClass;
  string += "\n";
  string += "ID : ";
  string += msg.msgId;
  string += "\n";
  string += "Length : ";
  string += msg.length;
  string += "\n";
  string += "Payload : ";
  for (int i = 0; i < msg.length; i++){
    string += msg.payload[i];
    string += " ";
  }
  string += "\n";
  string += "checksum : ";
  string += msg.checksumA;
  string += " ";
  string += msg.checksumB;
  string += "\n";
  return string;
}
