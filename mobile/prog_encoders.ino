#define PASSOS 22//40
#define _PWM 255
#define MOVE_COMMANDS 11
#define START_MOVE 10

mobile mobil(2,3,4,5,9,10,A0,A1);//(a,b,c,d) = pinos de saida para o drive;(e,f) = pinos de pwm;(g,h) = pinos de encoder.
Radio radio(8,7,10,"carro");
byte dado; //dado recebido pela serial ou bluetooth.
char msg[25];

void setup(){
  Serial.begin(9600);
}

void loop(){
  /******************************************/
  //verifica o radio
  if(radio.available()){
    radio.readPacket();
    Serial.print("fnc: ");
    Serial.println(radio.fnc);
    if(radio.fnc == MOVE_COMMANDS){
      for(uint8_t i=0;i<25;i++){
        msg[i] = (char)radio.data[i];
        Serial.println((char)radio.data[i]);
      }
    }
    if(radio.fnc == START_MOVE){
      for(uint8_t i=0;i<25;i++){
        Serial.print("msg[i]: ");
        Serial.println(msg[i]);
        if(msg[i] == 'F'){
          Serial.println("Frente");
          mobil.forward(PASSOS,_PWM);
          Serial.println("Fim");
        }
        if(msg[i] == 'B'){
          Serial.println("Ré");
          mobil.back(PASSOS,_PWM);
          Serial.println("Fim");
        }
        if(msg[i] == 'L'){
          Serial.println("Esquerda");
          mobil.left(PASSOS,_PWM);
          Serial.println("Fim");
        }
        if(msg[i] == 'R'){
          Serial.println("Direita");
          mobil.right(PASSOS,_PWM);
          Serial.println("Fim");
        }
      }
    }
  }
  //verifica a serial
  if(Serial.available()){
    dado = Serial.read();
  }  
  /******************************************/

  /******************************************/
  dado = 0;
}


