#include "Plc01.h"


Plc01 myplc ;
uint8_t counter = 0;
const int interval = 20;
unsigned long previousMillis = 0; 
void setup() {
  myplc.initRelay();
}

void loop() { // put your main code here, to run repeatedly:
  if(millis() - previousMillis > interval) {
    previousMillis = millis();
    myplc.CLT01_38S_GetInpData();
    myplc.VNI8200XP_SendOutputData(counter);
    counter++;
  }
}



