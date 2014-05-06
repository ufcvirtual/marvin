#include <SPI.h>
//modificação
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#define Delay 630

union aux{
  unsigned long longs;
  byte bytes[4];
}
dado;

void setup(){
  Serial.begin(9600);
  Mirf.cePin = 8;
  Mirf.csnPin = 7;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();   
  Mirf.setRADDR((byte *)"Carro");   
  Mirf.payload = sizeof(unsigned long);
  Mirf.channel = 10;   
  Mirf.config();
  //Mirf.configRegister(RF_SETUP,0x0D);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop(){
  //byte data[Mirf.payload]; 
  if(Mirf.dataReady()){     
    Mirf.getData(dado.bytes);
  }
  if(Serial.available()){
    dado.bytes[0] = Serial.read();
  }  
  if(dado.bytes[0] == 'U' ){
    Serial.println("Frente");
    frente();
    delay(Delay);
    parar();
  }
  if(dado.bytes[0] == 'D' ){
    Serial.println("Ré");
    re();
    delay(Delay);
    parar();
  }
  if(dado.bytes[0] == 'L' ){
    Serial.println("Esquerda");
    esquerda();
    delay(Delay);
    parar();
  }
  if(dado.bytes[0] == 'R' ){
    Serial.println("Direita");
    direita();
    delay(Delay);
    parar();
  }
  dado.longs = 0;
}
void frente(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
}
void re(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
}
void esquerda(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
}
void direita(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
}
void parar(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}


