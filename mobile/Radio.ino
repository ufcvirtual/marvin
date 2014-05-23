#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
/**********************************************************************************************************************************************/
class Radio{
  public:
  Radio(uint8_t cePIN,uint8_t csnPIN,uint8_t CH,char *address,uint8_t PAYload);
  void write(uint8_t remoteAddress,long data);
  void write(uint8_t remoteAddress,int data);
  void write(uint8_t remoteAddress,int8_t data);
  void write(uint8_t remoteAddress,uint32_t data);
  void write(uint8_t remoteAddress,uint16_t data);
  void write(uint8_t remoteAddress,uint8_t data);
  void read(uint8_t *data);
  boolean available();

};
/**********************************************************************************************************************************************/
Radio::Radio(uint8_t cePIN,uint8_t csnPIN,uint8_t CH,char *Myaddress,uint8_t PAYload){
  Mirf.cePin = cePIN;
  Mirf.csnPin = csnPIN;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();   
  Mirf.setRADDR((uint8_t *)Myaddress);   
  Mirf.payload = PAYload;
  Mirf.channel = CH;   
  Mirf.config();
}
/**********************************************************************************************************************************************/
void Radio::write(uint8_t remoteAddress,long data){
  Mirf.setTADDR((byte *)remoteAddress);
  Mirf.send((uint8_t *)&data);//Envia os dados.
  while(Mirf.isSending());//loop enquanto não terminar a transmissão.  
}
/**********************************************************************************************************************************************/
void Radio::write(uint8_t remoteAddress,int data){
  Mirf.setTADDR((byte *)remoteAddress);
  Mirf.send((uint8_t *)&data);//Envia os dados.
  while(Mirf.isSending());//loop enquanto não terminar a transmissão.
}
/**********************************************************************************************************************************************/
void Radio::write(uint8_t remoteAddress,int8_t data){
  Mirf.setTADDR((byte *)remoteAddress);
  Mirf.send((uint8_t *)&data);//Envia os dados.
  while(Mirf.isSending());//loop enquanto não terminar a transmissão.
}
/**********************************************************************************************************************************************/
void Radio::write(uint8_t remoteAddress,uint32_t data){
  Mirf.setTADDR((byte *)remoteAddress);
  Mirf.send((uint8_t *)&data);//Envia os dados.
  while(Mirf.isSending());//loop enquanto não terminar a transmissão.
}
/**********************************************************************************************************************************************/
void Radio::write(uint8_t remoteAddress,uint16_t data){
  Mirf.setTADDR((byte *)remoteAddress);
  Mirf.send((uint8_t *)&data);//Envia os dados.
  while(Mirf.isSending());//loop enquanto não terminar a transmissão.  
}
/**********************************************************************************************************************************************/
void Radio::write(uint8_t remoteAddress,uint8_t data){
  Mirf.setTADDR((byte *)remoteAddress);
  Mirf.send((uint8_t *)&data);//Envia os dados.
  while(Mirf.isSending());//loop enquanto não terminar a transmissão.  
}
/**********************************************************************************************************************************************/
void Radio::read(uint8_t *data){ 
    Mirf.getData(data);  
}
/**********************************************************************************************************************************************/
boolean Radio::available(){
  return Mirf.dataReady();
}
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/


