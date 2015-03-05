#ifndef RADIO_H
#define RADIO_H

#include "Arduino.h"
#define TENTATIVAS 2
#define ACK 6
#define NACK 21
/**********************************************************************************************************************************************/
//Mirf.configRegister(RF_SETUP,0x0D);
class Radio{
public:
  char myAddress[5];
  uint8_t fnc;
  uint8_t data[32];
  Radio(uint8_t cePIN,uint8_t csnPIN,uint8_t CH,char *address);
  boolean available();
  uint8_t writePacket(uint8_t *remoteAddress,uint8_t fnc,uint8_t *array,uint8_t len);
  uint8_t writePacket(uint8_t *remoteAddress,uint8_t fnc);
  uint8_t readPacket();

};
/**********************************************************************************************************************************************/
#endif // RADIO_H
