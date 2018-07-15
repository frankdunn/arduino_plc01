#include "Arduino.h"
#include "Plc01.h"
#include <SPI.h>
Plc01::Plc01()
{
  pinMode(slaveSelectPin1, OUTPUT);
  pinMode(slaveSelectPin2, OUTPUT);
  pinMode(outEnablePin, OUTPUT);
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
}

uint8_t* Plc01::VNI8200XP_SendOutputData(uint8_t udata)
{
  static uint8_t P0, P1, P2, nP0, parityData, txData[2], rxData[2];
  
  P0 = udata^(udata>>1);
  P0 = P0 ^(P0 >> 2);
  P0 = P0 ^(P0 >> 4);
  P0 = P0 & 0x01;
  
  P1 = udata^(udata>>2);
  P1 = P1 ^ (P1 >> 4);
  
  P2 = P1 & 0x01;
  
  P1 = P1 & 0x02;
  P1 = P1 >> 1;
  
  nP0 = (~P0) & 0x01;
  
  parityData = (P2<<3)|(P1<<2)|(P0<<1)|nP0;
  
  *txData = parityData; 
  *(txData+1) = udata;
  
  digitalWrite(slaveSelectPin2,LOW);
  rxData[1] = SPI.transfer(txData[1]);
  rxData[0] = SPI.transfer(txData[0]);
  digitalWrite(slaveSelectPin2,HIGH);
  return rxData;
}

uint8_t* Plc01::CLT01_38S_GetInpData(void)
{
  static uint8_t txData[2],rxData[2];
  
  digitalWrite(slaveSelectPin1,LOW);
  rxData[0] =  SPI.transfer(0);
  rxData[1] =  SPI.transfer(0);
  digitalWrite(slaveSelectPin1,HIGH);
 // Serial.print("rxData[0] : "); 
 // Serial.println(rxData[0]); 
 // Serial.println(rxData[1]);
  return rxData;
}

void Plc01::initRelay(){
  digitalWrite(slaveSelectPin1,LOW);
  digitalWrite(slaveSelectPin1,HIGH);
  delay(10);
  digitalWrite(slaveSelectPin1,HIGH);
  digitalWrite(outEnablePin,HIGH);
  }
