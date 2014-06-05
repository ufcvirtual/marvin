#define PASSOS 20//40
#define _PWM 255

mobile mobil(2,3,4,5,9,10,A0,A1);//(a,b,c,d) = pinos de saida para o drive;(e,f) = pinos de pwm;(g,h) = pinos de encoder.
Radio radio(8,7,10,"carro",sizeof(long));
byte dado; //dado recebido pela serial ou bluetooth.
uint8_t radio_dado[4];//dado recebido pelo radio.
void setup(){
  Serial.begin(9600);
}

void loop(){
  /******************************************/
  //verifica o radio
  if(radio.available()){
    radio.read(radio_dado);
  }
  //verifica a serial
  if(Serial.available()){
    dado = Serial.read();
  }  
  /******************************************/
  if(dado == 'F' || radio_dado[0] == 'F'){
    Serial.println("Frente");
    mobil.forward(PASSOS+6,_PWM);
  }
  if(dado == 'B' || radio_dado[0] == 'B'){
    Serial.println("Ré");
    mobil.back(PASSOS+6,_PWM);
  }
  if(dado == 'L' || radio_dado[0] == 'L'){
    Serial.println("Esquerda");
    mobil.left(PASSOS,_PWM);
  }
  if(dado == 'R' || radio_dado[0] == 'R'){
    Serial.println("Direita");
      mobil.right(PASSOS,_PWM);
  }
  /******************************************/
  dado = 0;
}
