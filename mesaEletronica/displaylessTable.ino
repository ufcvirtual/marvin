
// Define the LED digit patters, from 0 - 9
// Note that these patterns are for common cathode displays
// For common anode displays, change the 1's to 0's and 0's to 1's
// 1 = LED on, 0 = LED off, in this order:
//                                    Arduino pin: 2,3,4,5,6,7,8
//byte seven_seg_digits[10][7] =                           { { 0,0,0,0,0,1,0 },  // = 0
//                                                           { 1,0,0,1,1,1,1 },  // = 1
//                                                           { 0,0,1,0,0,0,1 },  // = 2
//                                                           { 0,0,0,0,1,0,1 },  // = 3
//                                                           { 1,0,0,1,1,0,0 },  // = 4
//                                                           { 0,1,0,0,1,0,0 },  // = 5
//                                                           { 0,1,0,0,0,0,0 },  // = 6
//                                                           { 0,0,0,1,1,1,1 },  // = 7
//                                                           { 0,0,0,0,0,0,0 },  // = 8
//                                                           { 0,0,0,1,1,0,0 }   // = 9
//                                                           };
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

const int buttonPin = 3;
int buttonState = 0;
int sensorPin[5] = {0,1,2,3,4};
int sensorValue = 0;

void setup() {                
//  pinMode(2, OUTPUT);   
//  pinMode(3, OUTPUT);
//  pinMode(4, OUTPUT);
//  pinMode(5, OUTPUT);
//  pinMode(6, OUTPUT);
//  pinMode(7, OUTPUT);
//  pinMode(8, OUTPUT);
//  pinMode(9, OUTPUT);
//  writeDot(1);  // start with the "dot" off
  Mirf.cePin = 53  ;
  Mirf.csnPin = 48;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"Contr");//endereço deste radio
  Mirf.payload = sizeof(unsigned long);
  Mirf.channel = 10;
  Mirf.config();
  Mirf.setTADDR((byte *)"Carro");
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  //sevenSegWrite(0);
  
}
void analogResists(int sensorPin){
  int resistanceRead;
  int up = 1001;
  int down = 127;
  int left = 930;
  int right = 510;
  resistanceRead = analogRead (sensorPin);
  Serial.println (resistanceRead);
  unsigned long message = 0;
  if((resistanceRead>down-50)&&(resistanceRead<down+50))
  message='D';
  if((resistanceRead>up-50)&&(resistanceRead<up+50))
  message='U';
  if((resistanceRead>left-50)&&(resistanceRead<left+50))
  message='L';
  if((resistanceRead>right-50)&&(resistanceRead<right+50))
  message='R';
  Serial.println (message);
  Mirf.send((byte *)&message);//Envia os dados.
  while(Mirf.isSending())
    {//loop enquanto não terminar a transmissão.
     
  }
  //sevenSegWrite(sensorPin);
  delay(1000);
  //Verificar qual comando
  //Enviar comando
}

void writeDot(byte dot) {
  digitalWrite(9, dot);
}
    
//void sevenSegWrite(byte digit) {
//  byte pin = 2;
//  for (byte segCount = 0; segCount < 7; ++segCount) {
//    digitalWrite(pin, seven_seg_digits[digit][segCount]);
//    ++pin;
//  }
//}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {     
    for (int i=0 ; i<5; i++){ 
      analogResists(i);
    }
    //sevenSegWrite(0);    
  } 
  else {
    // turn LED off:
     
  }



//  for (byte count = 10; count > 0; --count) {
//   delay(1000);
//   sevenSegWrite(count - 1); 
//  }
//  delay(4000);
}
