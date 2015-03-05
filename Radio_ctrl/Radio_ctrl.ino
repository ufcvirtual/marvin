/******************************************************************************
 * Controle do Marvin via acelerometro e radio
 ******************************************************************************/
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Radio.h>
#include <AcceleroMMA7361.h>

//#define MOVE_COMMANDS 11
//#define START_MOVE 10
#define MOVE_FORWARD_RL 1
#define MOVE_BACK_RL 2
#define MOVE_RIGHT_RL 3
#define MOVE_LEFT_RL 4

Radio radio(8,7,10,"carro");
uint8_t dado; //dado recebido pela serial ou bluetooth.
char msg[25];

uint8_t remote_address[5]={
  'c','a','r','r','o'};
uint8_t wheels[2];
int direction;

AcceleroMMA7361 accelero;
int x;
int y;
//int z;

void setup(){
  Serial.begin(9600);
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(3.3);                   //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW);                   //sets the sensitivity to +/-6G
  accelero.calibrate();
}

void loop(){
  x = accelero.getXAccel();
  y = accelero.getYAccel();
  //z = accelero.getZAccel();
  /**************************/
  //Correções e conversões para transmissão
  if(x>0){
    x = min(x,100);
    x = map(x,0,100,0,255);
    direction = MOVE_FORWARD_RL;
  }
  else{
    x = max(x,0);
    x = map(x,-100,0,0,255);
   direction = MOVE_BACK_RL; 
  }
  /**************************/
  if(y>0){
    y = min(y,100);
//    y = map(y,0,100,0,255);
  }
  else{
    y = max(y,0);
//    y = map(y,-100,0,0,255);
  }
  /**************************/
  //Envie via radio,o valor em pwm de cada roda
  radio.writePacket(remote_address,direction,wheels,sizeof(wheels));
}





