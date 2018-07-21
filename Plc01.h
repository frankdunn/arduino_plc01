#ifndef Plc01_h
#define Plc01_h

// arduino uno
//const int slaveSelectPin2 = 10;
//const int slaveSelectPin1 = 9;
//const int outEnablePin = 6;

// esp 8266
const int slaveSelectPin2 = D3;
const int slaveSelectPin1 = D4;
const int outEnablePin = D2;

class Plc01
{
  public:
        Plc01(); //constructor
        uint8_t* VNI8200XP_SendOutputData(uint8_t udata);
        uint8_t* CLT01_38S_GetInpData(void);
        void initRelay();
  private:
  ; 
  
  
  };
#endif
