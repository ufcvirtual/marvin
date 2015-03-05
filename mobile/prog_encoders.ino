#define PASSOS 18//22//40
#define _PWM 255
#define MOVE_COMMANDS 11
#define START_MOVE 10
#define MOVE_FORWARD_RL 1
#define MOVE_BACK_RL 2
#define MOVE_RIGHT_RL 3
#define MOVE_LEFT_RL 4

mobile mobil(2,3,9,10,A0,A1);//(a,b,c,d) = pinos de saida para o drive;(e,f) = pinos de pwm;(g,h) = pinos de encoder.
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
    if(radio.fnc == MOVE_COMMANDS){//se a função for uma função de movimentação...
      for(uint8_t i=0;i<25;i++){//guarde os parametros
        msg[i] = (char)radio.data[i];
        Serial.println((char)radio.data[i]);
      }
    }
    if(radio.fnc == START_MOVE){//se a função for a função de "play"...
      for(uint8_t i=0;i<25;i++){
        Serial.print("msg[i]: ");
        Serial.println(msg[i]);
        if(msg[i] == 'F'){
          Serial.println("Frente");
          mobil.forward_stop(PASSOS,_PWM);
          Serial.println("Fim");
        }
        if(msg[i] == 'B'){
          Serial.println("Ré");
          mobil.back_stop(PASSOS,_PWM);
          Serial.println("Fim");
        }
        if(msg[i] == 'L'){
          Serial.println("Esquerda");
          mobil.left_stop(PASSOS,_PWM);
          Serial.println("Fim");
        }
        if(msg[i] == 'R'){
          Serial.println("Direita");
          mobil.right_stop(PASSOS,_PWM);
          Serial.println("Fim");
        }
      }
    }
    //Controle por acelerometro
    /*************************************/
    int move,percentage;
    float result_a,result_b;
    
    move = radio.data[0];
    percentage = radio.data[1];
    result_a = ((float)move * (float)percentage)/100.0;
    result_b = ((float)move * 100.0-(float)percentage)/100.0;
    
    if(radio.fnc == MOVE_FORWARD_RL){
      mobil.right_direct((uint8_t)result_a);  //Primeiro byte corresponde ao pwm para roda direita
      mobil.left_reverse((uint8_t)result_b);  //Segundo byte corresponde ao pwm para roda esquerda
    }
    if(radio.fnc == MOVE_BACK_RL){
      mobil.right_reverse((uint8_t)result_a);  //Primeiro byte corresponde ao pwm para roda direita
      mobil.left_direct((uint8_t)result_b);  //Segundo byte corresponde ao pwm para roda esquerda
    }
    if(radio.fnc == MOVE_RIGHT_RL){
      mobil.right_direct((uint8_t)result_a);  //Primeiro byte corresponde ao pwm para roda direita
      mobil.left_direct((uint8_t)result_b);  //Segundo byte corresponde ao pwm para roda esquerda
    }
    if(radio.fnc == MOVE_LEFT_RL){
      mobil.right_reverse((uint8_t)result_a);  //Primeiro byte corresponde ao pwm para roda direita
      mobil.left_reverse((uint8_t)result_b);  //Segundo byte corresponde ao pwm para roda esquerda
    }
    /*************************************/    
  }
  //verifica a serial//melhoramento previsto
  if(Serial.available()){
    dado = Serial.read();
  }  
  /******************************************/
  if(dado == 'F'){
    Serial.println("Frente");
    mobil.forward_stop(PASSOS,_PWM);
    Serial.println("Fim");
  }
  if(dado == 'B'){
    Serial.println("Ré");
    mobil.back_stop(PASSOS,_PWM);
    Serial.println("Fim");
  }
  if(dado == 'L'){
    Serial.println("Esquerda");
    mobil.left_stop(PASSOS,_PWM);
    Serial.println("Fim");
  }
  if(dado == 'R'){
    Serial.println("Direita");
    mobil.right_stop(PASSOS,_PWM);
    Serial.println("Fim");
  }
  /******************************************/
  dado = 0;
}





