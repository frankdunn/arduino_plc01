#include "Plc01.h"


Plc01 myplc ;
uint8_t counter = 0;

void setup() {
  myplc.initRelay();
}

void loop() { // put your main code here, to run repeatedly:
  
  myplc.CLT01_38S_GetInpData();
  myplc.VNI8200XP_SendOutputData(counter);
  counter++;
  delay(40);
}


