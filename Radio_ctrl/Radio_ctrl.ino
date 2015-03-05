#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Radio.h>

#define MOVE_F_RL 1
#define MOVE_B_RL 2

Radio radio(8,7,10,"carro");
uint8_t dado; //dado recebido pela serial ou bluetooth.
char msg[25];
uint8_t remote_address[5]={'c','a','r','r','o'};
uint8_t wheels[2];
void setup(){
  Serial.begin(9600);
}

void loop(){
  //Envie via radio,o valor em pwm de cada roda
  radio.writePacket(remote_address,MOVE_RL,wheels,sizeof(wheels));
}



