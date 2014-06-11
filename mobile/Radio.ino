#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#define FRENTE 70
#define RE 66
#define DIREITA 82
#define ESQUERDA 76
#define TENTATIVAS 2
/**********************************************************************************************************************************************/
class Radio{
public:
  uint8_t func; 
  Radio(uint8_t cePIN,uint8_t csnPIN,uint8_t CH,char *address,uint8_t PAYload);
  void write(uint8_t *remoteAddress,long data);
  //void write(uint8_t remoteAddress,int data);
  //void write(uint8_t remoteAddress,int8_t data);
  void write(uint8_t *remoteAddress,uint32_t data);
  //void write(uint8_t remoteAddress,uint16_t data);
  //void write(uint8_t remoteAddress,uint8_t data);
  void read(uint8_t *data);
  boolean available();
  uint8_t moveCar(uint8_t *remoteAddress,uint8_t *array,uint8_t len);
  uint8_t readPacket();

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
void Radio::write(uint8_t *remoteAddress,long data){
  Mirf.setTADDR((byte *)remoteAddress);
  Mirf.send((uint8_t *)&data);//Envia os dados.
  while(Mirf.isSending());//loop enquanto não terminar a transmissão.  
}
/**********************************************************************************************************************************************/
/*void Radio::write(uint8_t remoteAddress,int data){
 Mirf.setTADDR((byte *)remoteAddress);
 Mirf.send((uint8_t *)&data);//Envia os dados.
 while(Mirf.isSending());//loop enquanto não terminar a transmissão.
 }*/
/**********************************************************************************************************************************************/
/*void Radio::write(uint8_t remoteAddress,int8_t data){
 Mirf.setTADDR((byte *)remoteAddress);
 Mirf.send((uint8_t *)&data);//Envia os dados.
 while(Mirf.isSending());//loop enquanto não terminar a transmissão.
 }*/
/**********************************************************************************************************************************************/
void Radio::write(uint8_t *remoteAddress,uint32_t data){
  Mirf.setTADDR((byte *)remoteAddress);
  Mirf.send((uint8_t *)&data);//Envia os dados.
  while(Mirf.isSending());//loop enquanto não terminar a transmissão.
}
/**********************************************************************************************************************************************/
/*void Radio::write(uint8_t remoteAddress,uint16_t data){
 Mirf.setTADDR((byte *)remoteAddress);
 Mirf.send((uint8_t *)&data);//Envia os dados.
 while(Mirf.isSending());//loop enquanto não terminar a transmissão.  
 }*/
/**********************************************************************************************************************************************/
/*void Radio::write(uint8_t remoteAddress,uint8_t data){
 Mirf.setTADDR((byte *)remoteAddress);
 Mirf.send((uint8_t *)&data);//Envia os dados.
 while(Mirf.isSending());//loop enquanto não terminar a transmissão.  
 }*/
/**********************************************************************************************************************************************/
void Radio::read(uint8_t *data){ 
  Mirf.getData(data);  
}
/**********************************************************************************************************************************************/
boolean Radio::available(){
  return Mirf.dataReady();
}
/**********************************************************************************************************************************************/
uint8_t Radio::moveCar(uint8_t *remoteAddress,uint8_t *array,uint8_t len){
  Mirf.setTADDR((byte *)remoteAddress);
  uint8_t err = 0;
  uint8_t checksum = 0;
  uint8_t data[32];
  while(1){
    checksum = 0;
    //calcule checksum
    checksum = 2;
    checksum ^=(len+1);
    checksum ^= 11;
    /**********************/
    //configure o payload
    Mirf.payload = 4;
    Mirf.config();
    /**********************/
    //transmissão
    data[0] = 2;
    data[0] = len+1;
    data[0] = 11; 
    data[0] = checksum;
    Mirf.send((uint8_t*)data);//Envia os dados.
    while(Mirf.isSending());//loop enquanto não terminar a transmissão.
    /***********************************************************************/
    //ACK
    for(uint8_t i=0; i<100; i++){//esperar 1 segundo pela resposta
      if(Mirf.dataReady()){
        Mirf.getData(data); 
        break; 
      }
      delay(10);
    }
    if(data[0] == 6){//mensagem recebida com sucesso
      break;
    }
    //NACK
    else err++;
    if(err < TENTATIVAS)return 1;
  }
  while(err < TENTATIVAS){
    checksum = 0;
    //construindo o pacote 
    for(uint8_t i=0;i<len;i++){
      data[i] = *(array+i);
      checksum ^= *(array+i);
    }
    data[len] = checksum;
    /*configure o payload**/
    Mirf.payload = len+1;
    Mirf.config();
    /**********************/
    Mirf.send((uint8_t*)data);//envio do pacote
    while(Mirf.isSending());//loop enquanto não terminar a transmissão.
    //ACK
    for(uint8_t i=0; i<100; i++){//esperar 1 segundo pela resposta
      if(Mirf.dataReady()){
        Mirf.getData(data); 
        break; 
      }
      delay(10);
    }
    if(data[0] == 6){//mensagem recebida com sucesso
      break;
    }
    //NACK
    else err++;
    if(err < TENTATIVAS)return 2;
  }
  return 0;
}
/**********************************************************************************************************************************************/
uint8_t Radio::readPacket(){
  uint8_t data[32];
  Mirf.getData(data);
  switch(data[0]){
    case 2:
    break;
    default:
    return 0;
  }
}
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/







