/*******************************************************************************************/
/*********************************CLASSE****************************************************/
/*******************************************************************************************/
#define BRAKING_POINT 1
class mobile{
private:
  //Pinos de acionamento do drive dos motores
  uint16_t in1;
  uint16_t in2;
  uint16_t in3;
  uint16_t in4;
  //uint16_t pin_pwm;
  //Variaveis de contagem dos encoderes
  uint16_t encoder_L;
  uint16_t encoder_R;
  //Pinos dos encoderes
  uint16_t pin_enc_L;
  uint16_t pin_enc_R;
  //Pinos de pwm
  uint16_t pin_pwm_L;
  uint16_t pin_pwm_R;

  uint8_t overflow_L;
  uint8_t overflow_R;

  uint16_t analog_read(uint16_t pin,uint16_t nivel);
  void check(uint16_t steps_L,uint16_t steps_R);
  void speed_smooth(uint16_t steps_L,uint16_t steps_R,uint16_t speed);
  boolean stop_L();
  boolean stop_R();

public:
  //Construtor
  mobile(uint16_t pin1,uint16_t pin2,uint16_t pin3,uint16_t pin4,uint16_t pwm_L,uint16_t pwm_R,uint16_t enc_L,uint16_t enc_R);//enc_L,enc_R devem ser entradas analógicas
  /***********Funções*************/
  void forward(uint16_t steps,uint16_t pwm);
  void left(uint16_t steps,uint16_t pwm);
  void right(uint16_t steps,uint16_t pwm);
  void back(uint16_t steps,uint16_t pwm); 
  void test(uint16_t steps,uint16_t pwm);//só para testes.

};
/********************************************************************************************/
/*Funções*/
/********************************************************************************************/
mobile::mobile(uint16_t pin1,uint16_t pin2,uint16_t pin3,uint16_t pin4,uint16_t pwm_L,uint16_t pwm_R,uint16_t enc_L,uint16_t enc_R){
  in1 = pin1;
  in2 = pin2;
  in3 = pin3;
  in4 = pin4;
  pin_pwm_L = pwm_L;
  pin_pwm_R = pwm_R;
  pin_enc_L = enc_L;
  pin_enc_R = enc_R;
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
}
/********************************************************************************************/
void mobile::forward(uint16_t steps,uint16_t pwm){
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);//
  digitalWrite(in4,0);
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  //check(steps,steps);
  //speed_smooth((1-BRAKING_POINT)*steps,(1-BRAKING_POINT)*steps,pwm);
    //espera até que se conclua a contagem de passsos
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  boolean flag_L = false,flag_R = true;

  while(encoder_R <= steps ||encoder_L <= steps ){
    uint16_t aux_R = analog_read(pin_enc_R,500);

    if(aux_R != status_R){
      Serial.print("encoder_R: ");
      Serial.println(encoder_R);
    }
    //se houver uma mudança no sinal do encoder direito 
    if(aux_R != status_R && flag_L){
      encoder_R++;
      flag_R = stop_R();//parar roda direita
      status_R = aux_R;
      delay(1);
      digitalWrite(in1,1);//ligar roda esquerda
    }

    uint16_t aux_L = analog_read(pin_enc_L,500);

    if(aux_L != status_L){
      Serial.print("\t\tencoder_L: ");
      Serial.println(encoder_L);
    }
    //se houver uma mudança no sinal do encoder esquerdo
    if(aux_L != status_L && flag_R){
      encoder_L++;
      flag_L = stop_L();//parar roda esquerda
      status_L = aux_L;
      delay(1);
      digitalWrite(in3,1);//ligar roda direita
    }
    if(Serial.available()){
      stop_R();
      stop_L();
      break;
    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
void mobile::back(uint16_t steps,uint16_t pwm){
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,0);//
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  //check(steps,steps);
  //speed_smooth((1-BRAKING_POINT)*steps,(1-BRAKING_POINT)*steps,pwm);
    //espera até que se conclua a contagem de passsos
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  boolean flag_L = false,flag_R = true;

  while(encoder_R <= steps ||encoder_L <= steps ){
    uint16_t aux_R = analog_read(pin_enc_R,500);

    if(aux_R != status_R){
      Serial.print("encoder_R: ");
      Serial.println(encoder_R);
    }
    //se houver uma mudança no sinal do encoder direito 
    if(aux_R != status_R && flag_L){
      encoder_R++;
      flag_R = stop_R();//parar roda direita
      status_R = aux_R;
      delay(1);
      digitalWrite(in2,1);//ligar roda esquerda
    }

    uint16_t aux_L = analog_read(pin_enc_L,500);

    if(aux_L != status_L){
      Serial.print("\t\tencoder_L: ");
      Serial.println(encoder_L);
    }
    //se houver uma mudança no sinal do encoder esquerdo
    if(aux_L != status_L && flag_R){
      encoder_L++;
      flag_L = stop_L();//parar roda esquerda
      status_L = aux_L;
      delay(1);
      digitalWrite(in4,1);//ligar roda direita
    }
    if(Serial.available()){
      stop_R();
      stop_L();
      break;
    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
void mobile::left(uint16_t steps,uint16_t pwm){
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);//
  digitalWrite(in4,0);
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  //espera até que se conclua a contagem de passsos
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  boolean flag_L = false,flag_R = true;

  while(encoder_R <= steps ||encoder_L <= steps){
    uint16_t aux_R = analog_read(pin_enc_R,500);

    if(aux_R != status_R){
      Serial.print("encoder_R: ");
      Serial.println(encoder_R);
    }

    if(aux_R != status_R && flag_L){
      encoder_R++;
      flag_R = stop_R();
      status_R = aux_R;
      delay(1);
      digitalWrite(in2,1);
    }
    uint16_t aux_L = analog_read(pin_enc_L,500);

    if(aux_L != status_L){
      Serial.print("\t\tencoder_L: ");
      Serial.println(encoder_L);
    }

    if(aux_L != status_L && flag_R){
      encoder_L++;
      flag_L = stop_L();
      status_L = aux_L;
      delay(1);
      digitalWrite(in3,1);
    }
    if(Serial.available()){
      stop_R();
      stop_L();
      break;
    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
void mobile::right(uint16_t steps,uint16_t pwm){
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);//
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  //espera até que se conclua a contagem de passsos
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  boolean flag_L = false,flag_R = true;

  while(encoder_R <= steps ||encoder_L <= steps ){
    uint16_t aux_R = analog_read(pin_enc_R,500);

    if(aux_R != status_R){
      Serial.print("encoder_R: ");
      Serial.println(encoder_R);
    }
    //se houver uma mudança no sinal do encoder direito 
    if(aux_R != status_R && flag_L){
      encoder_R++;
      flag_R = stop_R();//parar roda direita
      status_R = aux_R;
      delay(1);
      digitalWrite(in1,1);//ligar roda esquerda
    }

    uint16_t aux_L = analog_read(pin_enc_L,500);

    if(aux_L != status_L){
      Serial.print("\t\tencoder_L: ");
      Serial.println(encoder_L);
    }
    //se houver uma mudança no sinal do encoder esquerdo
    if(aux_L != status_L && flag_R){
      encoder_L++;
      flag_L = stop_L();//parar roda esquerda
      status_L = aux_L;
      delay(1);
      digitalWrite(in4,1);//ligar roda direita
    }
    if(Serial.available()){
      stop_R();
      stop_L();
      break;
    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
boolean mobile::stop_L(){
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  analogWrite(pin_pwm_L,0);
  return true;
}
/********************************************************************************************/
boolean mobile::stop_R(){
  digitalWrite(in3,0);
  digitalWrite(in4,0);
  analogWrite(pin_pwm_R,0);
  return true;
}
/********************************************************************************************/
void mobile::check(uint16_t steps_L,uint16_t steps_R){
  encoder_L = 0;
  encoder_R = 0;

  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  uint8_t pin_status = 0;
  boolean flag_L = false,flag_R = false;

  //guardar o status atual dos pinos de controle da ponte H
  //pin_status = (digitalRead(in1) << 3)|(digitalRead(in2) << 2)|(digitalRead(in3) << 1)|(digitalRead(in4) << 0);

  while(1){
    /*ler o sensor 1 optico,e incrementar se detectada mudança,
     se holver o incremento parar o motor*/
    uint16_t aux_R = analog_read(pin_enc_R,500);
    if(aux_R != status_R){
      encoder_R++;
      flag_R = stop_R();
      status_R = aux_R;
    }
    /* ler o sensor 2 optico,e incrementar se detectada mudança,
     se holver o incremento parar o motor*/
    uint16_t aux_L = analog_read(pin_enc_L,500);
    if(aux_L != status_L){
      encoder_L++;
      flag_L = stop_L();
      status_L = aux_L;
    }
    //Caso as duas rodas estiverem paradas e a contagem de cada uma superou o numero de passos 
    if(flag_L && flag_R){
      break;
    }
    /* se a variavel de controle exceder o valor do numero de passos
     sair do loop*/
    if(Serial.available()){
      stop_R();
      stop_L();
      break;
    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
//retorna 1 se a leitura analogica esta acima de level
uint16_t mobile::analog_read(uint16_t pin,uint16_t level){
  uint16_t num = analogRead(pin);
  if(num >= level) return 1;
  else return 0;

}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/















