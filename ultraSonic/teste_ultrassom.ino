//#include <TimerThree.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Servo.h> 
#define Delay 630
#define DISTANCIA 3
#define DELAY_BUSCA 50
/***********************************************************************/
union aux{
  unsigned long longs;
  byte bytes[4];
}
dado;
/***********************************************************************/
Servo myservo; 
void setup(){
  //Timer3.initialize(250000);
  //Timer3.attachInterrupt(callback);
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
  myservo.attach(9);
  myservo.write(90);
}
/***********************************************************************/
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
    for(uint8_t i = 0;i<10;i++){
      long dst = cheque_ultrassom(A0,A1,Delay/10);
      if(dst <= DISTANCIA){
        parar();
        delay(500);
        re();
        delay(500);
        break;
        }
      }
      //cheque_caminho(630);
      //delay(Delay);
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
    //cheque_caminho(630);
    delay(Delay/5);
    parar();
  }
  if(dado.bytes[0] == 'R' ){
    Serial.println("Direita");
    direita();
    //cheque_caminho(630);
    delay(Delay/5);
    parar();
  }
  dado.longs = 0;
}
/***********************************************************************/
void frente(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
}
/***********************************************************************/
void re(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
}
/***********************************************************************/
void esquerda(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
}
/***********************************************************************/
void direita(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
}
/***********************************************************************/
void parar(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}
/***********************************************************************/
void cheque_caminho(int tempo){
  uint16_t atraso = tempo/24;//atraso para cada leitura do sensor ultrasonico
  for(uint8_t pos = 30;pos<150;pos+=10){
    myservo.write(pos);
    //delay(100);   
    long dst = cheque_ultrassom(A0,A1,atraso);
    if(dst <= DISTANCIA){
      parar();
      Serial.println("Obstaculo");
      myservo.write(90);
      re();
      delay(500);
      parar();
      return;
    }
  }
  for(uint8_t pos = 150;pos>30;pos-=10){
    myservo.write(pos);
    //delay(100);  
    long dst = cheque_ultrassom(A0,A1,atraso);
    if(dst <= DISTANCIA){
      parar();
      Serial.println("Obstaculo");
      myservo.write(90);
      re();
      delay(500);
      parar();
      return;
    }  
  }
}
/***********************************************************************/
long cheque_ultrassom(uint8_t trigPin,uint8_t echoPin,uint16_t tempo){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  long duracao, distancia; 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW); 
  duracao = pulseIn(echoPin, HIGH);  
  //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado
  //porque é o tempo de ida e volta do ultrassom
  delay(tempo);
  distancia = (duracao/2) / 29.1;
  Serial.println(distancia);
  if (distancia >= 200 || distancia <= 0){
    return 0xff;
  }
  else {
    return distancia;
  }
}
/***********************************************************************/



