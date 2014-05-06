#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

void setup(){
  Serial.begin(9600);
  Mirf.cePin = 8;
  Mirf.csnPin = 7;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"Contr");//endereço deste radio
  Mirf.payload = sizeof(unsigned long);
  Mirf.channel = 10;
  Mirf.config();
  //Mirf.configRegister(RF_SETUP,0x0D);
}
void loop(){
  if(Serial.available()){
    unsigned long menssagem = 0;
    char dado = Serial.read();
    Mirf.setTADDR((byte *)"Carro");//Endereço de destino.
    if(dado == 'U' ||dado == 'D'||dado == 'R'||dado == 'L'){
      menssagem = dado;
      Mirf.send((byte *)&mensagem);//Envia os dados.
      while(Mirf.isSending()){//loop enquanto não terminar a transmissão.
      }
    }
  }
} 



