/*******************************************************************************************/
/*********************************CLASSE****************************************************/
/*******************************************************************************************/
#define STOP_WHEEL(A,B) digitalWrite(A,0);digitalWrite(B,0);
#define SPIN_WHEEL(A,B) digitalWrite(A,0);digitalWrite(B,1);
#define ENCODER_READ(A,B) ((A>B)?(1):(0))
#define BRAKING_POINT 1
#define ANALOG_MIN 200
class mobile{
private:
  //Pinos de acionamento do drive dos motores
  uint16_t L1;
  uint16_t L2;
  uint16_t R1;
  uint16_t R2;
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

  uint16_t analog_read(uint16_t pin,uint16_t nivel);
  void speed_smooth(uint16_t steps_L,uint16_t steps_R,uint16_t speed);//não usado
  boolean stop_L();
  boolean stop_R();

public:
  //Construtor
  mobile(uint16_t pL1,uint16_t pL2,uint16_t pR1,uint16_t pR2,uint16_t pwm_L,uint16_t pwm_R,uint16_t enc_L,uint16_t enc_R);//enc_L,enc_R devem ser entradas analógicas
  /***********Funções*************/
  void forward(uint16_t steps,uint16_t pwm);
  void left(uint16_t steps,uint16_t pwm);
  void right(uint16_t steps,uint16_t pwm);
  void back(uint16_t steps,uint16_t pwm); 
  void right_direct(uint8_t speed);
  void right_reverse(uint8_t speed);
  void left_direct(uint8_t speed);
  void left_reverse(uint8_t speed);

};
/********************************************************************************************/
/*Funções*/
/********************************************************************************************/
mobile::mobile(uint16_t pL1,uint16_t pL2,uint16_t pR1,uint16_t pR2,uint16_t pwm_L,uint16_t pwm_R,uint16_t enc_L,uint16_t enc_R){
  L1 = pL1;
  L2 = pL2;
  R1 = pR1;
  R2 = pR2;
  pin_pwm_L = pwm_L;
  pin_pwm_R = pwm_R;
  pin_enc_L = enc_L;
  pin_enc_R = enc_R;
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
}
/********************************************************************************************/
void mobile::forward(uint16_t steps,uint16_t pwm){
  encoder_L = 0;//contagem do encoder esquerdo
  encoder_R = 0;//contagem do encoder direito
  uint16_t status_R = ENCODER_READ(analogRead(pin_enc_R),500);//guarda o estado do sensor direito
  uint16_t status_L = ENCODER_READ(analogRead(pin_enc_L),500);//guarda o estado do sensor esquerdo
  boolean flag_L = true,flag_R = true;
  //right_direct(pwm);
  //left_direct(pwm);
  SPIN_WHEEL(L1,L2);
  SPIN_WHEEL(R1,R2);
  //uint8_t aux_R = 0,aux_L = 0;
  //uint8_t speed = pwm;
  while(encoder_R < steps ||encoder_L < steps ){
    uint16_t read_R = ENCODER_READ(analogRead(pin_enc_R),500);//real
    //uint16_t read_R = digitalRead(pin_enc_R);//para simulações
    //verificar o estado do encoder,caso seja diferente do estado anterior...
    if(read_R != status_R){
      encoder_R++;//incremente a variavel
      status_R = read_R;//guarde a atual leitura
      //flag_R = stop_R();//parar roda direita 
      STOP_WHEEL(R1,R2);
      flag_R = true;
    }
    uint16_t read_L = ENCODER_READ(analogRead(pin_enc_L),500);//real
    //uint16_t read_L = digitalRead(pin_enc_L);//para simulações
    if(read_L != status_L){
      encoder_L++;//incremente a variavel
      status_L = read_L;//guarde a atual leitura
      //flag_L = stop_L();//parar roda esquerda
      STOP_WHEEL(L1,L2);
      flag_L = true;
    }
    //se a roda esquerda andou um pouco menos que a direita e as duas rodas estiverem paradas...
    if(encoder_L < encoder_R && encoder_L < steps && flag_R && flag_L){
      //right_direct();
      //left_direct(speed);//ligue a roda esquerda
      SPIN_WHEEL(L1,L2);
      flag_L = false;
    }
    //se a roda direita andou um pouco menos que a direita e as duas rodas estiverem paradas...
    if(encoder_R <= encoder_L && encoder_R < steps && flag_R && flag_L){
      //right_direct(speed);
      //left_direct();
      SPIN_WHEEL(R1,R2);
      flag_R = false;
    }
//    if(Serial.available()){
//      stop_R();
//      stop_L();
//      break;
//    }
    //velocidade
//    if(speed < 255 && encoder_L < steps-BRAKING_POINT){
//      speed++; 
//      analogWrite(pin_pwm_L,speed);
//      analogWrite(pin_pwm_R,speed); 
//    }
//    if(speed > 0 && encoder_L >= steps-1 && speed >=ANALOG_MIN){
//      speed--;
//      analogWrite(pin_pwm_L,speed);
//      analogWrite(pin_pwm_R,speed);
//    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
void mobile::back(uint16_t steps,uint16_t pwm){
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = ENCODER_READ(analogRead(pin_enc_R),500);//guarda o estado do sensor direito
  uint16_t status_L = ENCODER_READ(analogRead(pin_enc_L),500);//guarda o estado do sensor esquerdo
  boolean flag_L = true,flag_R = true;
  //right_reverse(pwm);
  //left_reverse(pwm);
  SPIN_WHEEL(L2,L1);
  SPIN_WHEEL(R2,R1);
  //uint8_t aux_R = 0,aux_L = 0;
  //uint8_t speed = pwm;
  while(encoder_R < steps ||encoder_L < steps ){
    uint16_t read_R = ENCODER_READ(analogRead(pin_enc_R),500);//real
    //uint16_t read_R = digitalRead(pin_enc_R);//para simulações
    //verificar o estado do encoder
    if(read_R != status_R){
      encoder_R++;
      status_R = read_R;
      //flag_R = stop_R();//parar roda direita
      STOP_WHEEL(R1,R2);
      flag_R = true;
    }
    uint16_t read_L = ENCODER_READ(analogRead(pin_enc_L),500);//real
    //uint16_t read_L = digitalRead(pin_enc_L);//para simulações
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      //flag_L = stop_L();//parar roda esquerda 
      STOP_WHEEL(L1,L2);
      flag_L = true;
    }
    if(encoder_L < encoder_R && encoder_L < steps && flag_R && flag_L){
      //right_reverse();
      //left_reverse(speed);
      SPIN_WHEEL(L2,L1);
      flag_L = false;
      //Serial.println("erro aqui");
    }
    if(encoder_R <= encoder_L && encoder_R < steps && flag_R && flag_L){
      //right_reverse(speed);
      //left_reverse();
      SPIN_WHEEL(R2,R1);
      flag_R = false;
    }
//    if(Serial.available()){
//      stop_R();
//      stop_L();
//      break;
//    }
//    if(speed > 0 && encoder_L >= steps-BRAKING_POINT){
//      speed--;
//      analogWrite(pin_pwm_L,speed);
//      analogWrite(pin_pwm_R,speed);
//    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
void mobile::left(uint16_t steps,uint16_t pwm){
  //Serial.println(pwm);
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = ENCODER_READ(analogRead(pin_enc_R),500);//guarda o estado do sensor direito
  uint16_t status_L = ENCODER_READ(analogRead(pin_enc_L),500);//guarda o estado do sensor esquerdo
  boolean flag_L = true,flag_R = true;
  //left_direct(pwm);
  //right_reverse(pwm);
  SPIN_WHEEL(L1,L2);
  SPIN_WHEEL(R2,R1);
  //uint8_t aux_R = 0,aux_L = 0;
  //uint8_t speed = pwm;
  while(encoder_R < steps || encoder_L < steps ){
    //uint16_t read_R = analog_read(pin_enc_R,500);//real
    //uint16_t read_R = digitalRead(pin_enc_R);//para simulações
    uint16_t read_R = ENCODER_READ(analogRead(pin_enc_R),500);
    //verificar o estado do encoder
    if(read_R != status_R){
      encoder_R++;
      status_R = read_R;
      //flag_R = stop_R();//parar roda direita 
      STOP_WHEEL(R1,R2);
      flag_R = true;
    }
    uint16_t read_L = ENCODER_READ(analogRead(pin_enc_L),500);//real
    //uint16_t read_L = digitalRead(pin_enc_L);//para simulações
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      //flag_L = stop_L();//parar roda esquerda 
      STOP_WHEEL(L1,L2);
      flag_L = true;
    }
    if(encoder_L < encoder_R && encoder_L < steps && flag_R && flag_L){
      //left_direct(speed);
      //right_reverse();
      SPIN_WHEEL(L1,L2);
      flag_L = false;
    }
    if(encoder_R <= encoder_L && encoder_R < steps && flag_R && flag_L){
      //left_direct();
      //right_reverse(speed);
      SPIN_WHEEL(R2,R1);
      flag_R = false;
    }
//    if(Serial.available()){
//      stop_R();
//      stop_L();
//      break;
//    }
//    if(speed > 0 && encoder_R >= steps-BRAKING_POINT){
//      speed--;
//      analogWrite(pin_pwm_L,speed);
//      analogWrite(pin_pwm_R,speed);
//     //Serial.println(speed); 
//    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
void mobile::right(uint16_t steps,uint16_t pwm){
  //Serial.println(pwm);
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = ENCODER_READ(analogRead(pin_enc_R),500);//guarda o estado do sensor direito
  uint16_t status_L = ENCODER_READ(analogRead(pin_enc_L),500);//guarda o estado do sensor esquerdo
  boolean flag_L = true,flag_R = true;
  //right_direct(pwm);
  //left_reverse(pwm);
  SPIN_WHEEL(L2,L1);
  SPIN_WHEEL(R1,R2);
  //uint8_t aux_R = 0,aux_L = 0;
  //uint8_t speed = pwm;
  while(encoder_R < steps ||encoder_L < steps ){    
    uint16_t read_R = ENCODER_READ(analogRead(pin_enc_R),500);//real
    //uint16_t read_R = digitalRead(pin_enc_R);//para simulações
    //verificar o estado do encoder
    if(read_R != status_R){
      status_R = read_R;
      encoder_R++;
      //Serial.print("encoder_R = ");
      //Serial.println(encoder_R);      
      //flag_R = stop_R();//parar roda direita 
      //Serial.println("parando roda direita");
      STOP_WHEEL(R1,R2);
      flag_R = true;
    }
    uint16_t read_L = ENCODER_READ(analogRead(pin_enc_L),500);//real
    //uint16_t read_L = digitalRead(pin_enc_L);//para simulações
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      //Serial.print("encoder_L = ");
      //Serial.println(encoder_L);
      flag_L = stop_L();//parar roda esquerda 
      //Serial.println("parando roda esquerda");
      STOP_WHEEL(L1,L2);
      flag_L = true;
    }
    if(encoder_L < encoder_R && encoder_L < steps && flag_R && flag_L){
      //right_direct();
      //Serial.println("ligando roda esquerda");
      //left_reverse(speed);
      SPIN_WHEEL(L2,L1);
      flag_L = false;
    }
    if(encoder_R <= encoder_L && encoder_R < steps && flag_R && flag_L){
      //Serial.println("ligando roda direita");
      //right_direct(speed);
      //left_reverse();
      SPIN_WHEEL(R1,R2);
      flag_R = false;
    }
//    if(Serial.available()){
//      stop_R();
//      stop_L();
//      break;
//    }
//    if(speed > 0 && encoder_L >= steps-BRAKING_POINT){
//      speed--;
//      analogWrite(pin_pwm_L,speed);
//      analogWrite(pin_pwm_R,speed);
//     //Serial.println(speed); 
//    }
  }
  stop_R();
  stop_L();
}
/********************************************************************************************/
boolean mobile::stop_L(){
  digitalWrite(L1,0);
  digitalWrite(L2,0);
  analogWrite(pin_pwm_L,0);
  return true;
}
/********************************************************************************************/
boolean mobile::stop_R(){
  digitalWrite(R1,0);
  digitalWrite(R2,0);
  analogWrite(pin_pwm_R,0);
  return true;
}
/********************************************************************************************/
/********************************************************************************************/
//retorna 1 se a leitura analogica esta acima de level
uint16_t mobile::analog_read(uint16_t pin,uint16_t level){
  uint16_t num = analogRead(pin);
  if(num >= level) return 1;
  else return 0;

}
/********************************************************************************************/
void mobile::right_direct(uint8_t speed){
  digitalWrite(R1,0);
  digitalWrite(R2,1);
  analogWrite(pin_pwm_R,speed);
}
/********************************************************************************************/
void mobile::right_reverse(uint8_t speed){
  digitalWrite(R1,1);
  digitalWrite(R2,0);
  analogWrite(pin_pwm_R,speed);
}
/********************************************************************************************/
void mobile::left_direct(uint8_t speed){
  digitalWrite(L1,0);
  digitalWrite(L2,1);
  analogWrite(pin_pwm_L,speed);
}
/********************************************************************************************/
void mobile::left_reverse(uint8_t speed){
  digitalWrite(L1,1);
  digitalWrite(L2,0);
  analogWrite(pin_pwm_L,speed);
}
/********************************************************************************************/
/********************************************************************************************/





















