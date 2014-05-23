#define PASSOS 40
#define _PWM 255

mobile mobil(2,3,4,5,9,10,A0,A1);//(a,b,c,d) = pinos de saida para o drive;(e,f) = pinos de pwm;(g,h) = pinos de encoder
void setup(){
  Serial.begin(9600);
}
byte dado;
void loop(){
  if(Serial.available()){
    dado = Serial.read();
  }  
  if(dado == 'U' ){
    Serial.println("Frente");
    mobil.forward(PASSOS,_PWM);
  }
  if(dado == 'D' ){
    Serial.println("Ré");
    mobil.back(PASSOS,_PWM);
  }
  if(dado == 'L' ){
    Serial.println("Esquerda");
    mobil.left(PASSOS,_PWM);
  }
  if(dado == 'R' ){
    Serial.println("Direita");
      mobil.right(PASSOS,_PWM);
  }
  dado = 0;
}
