/*******************************************************************************************/
/*********************************CLASSE****************************************************/
/*******************************************************************************************/
#define STOP_WHEEL(A,B) digitalWrite(A,0);digitalWrite(B,0);
#define SPIN_WHEEL(A,B) digitalWrite(A,0);digitalWrite(B,1);
#define ENCODER_READ(A,B) ((A>B)?(1):(0))
#define BRAKING_POINT 1
#define ANALOG_MIN 200

/*================================================================================*/
enum direction{
  front,
  back,
  left,
  right,
  stop
};
/*================================================================================*/
class mobile{
private:
  //Pinos de acionamento do drive dos motores
  int pin_a;
  int pin_b;
  int pwm_a;
  int pwm_b;
  //uint16_t pin_pwm;
  //Variaveis de contagem dos encoderes
  uint16_t encoder_L;
  uint16_t encoder_R;
  //Pinos dos encoderes
  uint16_t pin_enc_L;
  uint16_t pin_enc_R;

  uint16_t analog_read(uint16_t pin,uint16_t nivel);
//  void speed_smooth(uint16_t steps_L,uint16_t steps_R,uint16_t speed);//não usado
  boolean stop_L();
  boolean stop_R();

public:
  //Construtor
  mobile(uint8_t a,uint8_t b,uint8_t pa,uint8_t pb,uint16_t enc_L,uint16_t enc_R);//enc_L,enc_R devem ser entradas analógicas
  /***********Funções*************/
  void forward_stop(uint16_t steps,uint16_t pwm);
  void left_stop(uint16_t steps,uint16_t pwm);
  void right_stop(uint16_t steps,uint16_t pwm);
  void back_stop(uint16_t steps,uint16_t pwm); 
  void right_direct(uint8_t speed);
  void right_reverse(uint8_t speed);
  void left_direct(uint8_t speed);
  void left_reverse(uint8_t speed);

};
/********************************************************************************************/
/*Funções*/
/********************************************************************************************/
mobile::mobile(uint8_t a,uint8_t b,uint8_t pa,uint8_t pb,uint16_t enc_L,uint16_t enc_R){  
  pin_a=a;
  pin_b=b;
  pwm_a=pa;
  pwm_b=pb;
  pinMode(pin_a,OUTPUT);
  pinMode(pin_b,OUTPUT);
  pin_enc_L = enc_L;
  pin_enc_R = enc_R;
}
/********************************************************************************************/
void mobile::forward_stop(uint16_t steps,uint16_t pwm){
  static uint8_t first=0;//Variavel para determinar qual rodo se movera primeiro.
  encoder_L = 0;//contagem do encoder esquerdo
  encoder_R = 0;//contagem do encoder direito
  uint16_t status_R = ENCODER_READ(analogRead(pin_enc_R),500);//guarda o estado do sensor direito
  uint16_t status_L = ENCODER_READ(analogRead(pin_enc_L),500);//guarda o estado do sensor esquerdo
  boolean flag_L = true,flag_R = true;
  //right_direct(pwm);
  //left_direct(pwm);
  if(first %2 == 0){
  SPIN_WHEEL(pin_b,pwm_b);
  SPIN_WHEEL(pin_a,pwm_a);
  Serial.println("Ordem normal");
  }
  else{
  SPIN_WHEEL(pin_b,pwm_b);
  SPIN_WHEEL(pin_a,pwm_a);
  Serial.println("Ordem inversa");
  }
  first++;
  /*******************************************************************
            Loop enquanto encoders não atingem a contagem
  ********************************************************************/
  while(encoder_R < steps || encoder_L < steps ){
    
    
    //Faz a verificação do estado do encoder
    uint16_t read_R = ENCODER_READ(analogRead(pin_enc_R),500);
    
    //verificar o estado do encoder, caso seja diferente do estado anterior...
    if(read_R != status_R ){
      encoder_R++;//incremente a variavel
      status_R = read_R;//guarde a atual leitura
      //flag_R = stop_R();//parar roda direita 
      STOP_WHEEL(pin_a,pwm_a);
      flag_R = true;
    }
    uint16_t read_L = ENCODER_READ(analogRead(pin_enc_L),500);//real
    //uint16_t read_L = digitalRead(pin_enc_L);//para simulações
    if(read_L != status_L){
      encoder_L++;//incremente a variavel
      status_L = read_L;//guarde a atual leitura
      //flag_L = stop_L();//parar roda esquerda
      STOP_WHEEL(pin_b,pwm_b);
      flag_L = true;
    }
    //se a roda esquerda andou um pouco menos que a direita e as duas rodas estiverem paradas...
    if(encoder_L < encoder_R && encoder_L < steps && flag_R && flag_L){
      //right_direct();
      //left_direct(speed);//ligue a roda esquerda
      SPIN_WHEEL(pin_b,pwm_b);
      flag_L = false;
    }
    //se a roda direita andou um pouco menos que a direita e as duas rodas estiverem paradas...
    if(encoder_R <= encoder_L && encoder_R < steps && flag_R && flag_L){
      //right_direct(speed);
      //left_direct();
      SPIN_WHEEL(pin_a,pwm_a);
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
void mobile::back_stop(uint16_t steps,uint16_t pwm){
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = ENCODER_READ(analogRead(pin_enc_R),500);//guarda o estado do sensor direito
  uint16_t status_L = ENCODER_READ(analogRead(pin_enc_L),500);//guarda o estado do sensor esquerdo
  boolean flag_L = true,flag_R = true;
  //right_reverse(pwm);
  //left_reverse(pwm);
  SPIN_WHEEL(pwm_b,pin_b);
  SPIN_WHEEL(pwm_a,pin_a);
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
      STOP_WHEEL(pin_a,pwm_a);
      flag_R = true;
    }
    uint16_t read_L = ENCODER_READ(analogRead(pin_enc_L),500);//real
    //uint16_t read_L = digitalRead(pin_enc_L);//para simulações
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      //flag_L = stop_L();//parar roda esquerda 
      STOP_WHEEL(pin_b,pwm_b);
      flag_L = true;
    }
    if(encoder_L < encoder_R && encoder_L < steps && flag_R && flag_L){
      //right_reverse();
      //left_reverse(speed);
      SPIN_WHEEL(pwm_b,pin_b);
      flag_L = false;
      //Serial.println("erro aqui");
    }
    if(encoder_R <= encoder_L && encoder_R < steps && flag_R && flag_L){
      //right_reverse(speed);
      //left_reverse();
      SPIN_WHEEL(pwm_a,pin_a);
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
void mobile::left_stop(uint16_t steps,uint16_t pwm){
  //Serial.println(pwm);
  analogWrite(pwm_b,pwm);
  analogWrite(pwm_a,pwm);
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = ENCODER_READ(analogRead(pin_enc_R),500);//guarda o estado do sensor direito
  uint16_t status_L = ENCODER_READ(analogRead(pin_enc_L),500);//guarda o estado do sensor esquerdo
  boolean flag_L = true,flag_R = true;
  //left_direct(pwm);
  //right_reverse(pwm);
  SPIN_WHEEL(pin_b,pwm_b);
  SPIN_WHEEL(pwm_a,pin_a);
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
      STOP_WHEEL(pin_a,pwm_a);
      flag_R = true;
    }
    uint16_t read_L = ENCODER_READ(analogRead(pin_enc_L),500);//real
    //uint16_t read_L = digitalRead(pin_enc_L);//para simulações
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      //flag_L = stop_L();//parar roda esquerda 
      STOP_WHEEL(pin_b,pwm_b);
      flag_L = true;
    }
    if(encoder_L < encoder_R && encoder_L < steps && flag_R && flag_L){
      //left_direct(speed);
      //right_reverse();
      SPIN_WHEEL(pin_b,pwm_b);
      flag_L = false;
    }
    if(encoder_R <= encoder_L && encoder_R < steps && flag_R && flag_L){
      //left_direct();
      //right_reverse(speed);
      SPIN_WHEEL(pwm_a,pin_a);
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
void mobile::right_stop(uint16_t steps,uint16_t pwm){
  //Serial.println(pwm);
  analogWrite(pwm_b,pwm);
  analogWrite(pwm_a,pwm);
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = ENCODER_READ(analogRead(pin_enc_R),500);//guarda o estado do sensor direito
  uint16_t status_L = ENCODER_READ(analogRead(pin_enc_L),500);//guarda o estado do sensor esquerdo
  boolean flag_L = true,flag_R = true;
  //right_direct(pwm);
  //left_reverse(pwm);
  SPIN_WHEEL(pwm_b,pin_b);
  SPIN_WHEEL(pin_a,pwm_a);
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
      STOP_WHEEL(pin_a,pwm_a);
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
      STOP_WHEEL(pin_b,pwm_b);
      flag_L = true;
    }
    if(encoder_L < encoder_R && encoder_L < steps && flag_R && flag_L){
      //right_direct();
      //Serial.println("ligando roda esquerda");
      //left_reverse(speed);
      SPIN_WHEEL(pwm_b,pin_b);
      flag_L = false;
    }
    if(encoder_R <= encoder_L && encoder_R < steps && flag_R && flag_L){
      //Serial.println("ligando roda direita");
      //right_direct(speed);
      //left_reverse();
      SPIN_WHEEL(pin_a,pwm_a);
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
  digitalWrite(pin_b,0);
  digitalWrite(pwm_b,0);
  return true;
}
/********************************************************************************************/
boolean mobile::stop_R(){
  digitalWrite(pin_a,0);
  digitalWrite(pwm_a,0);
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
    digitalWrite(pin_a,1);
    analogWrite(pwm_a,255-speed);  
}
/********************************************************************************************/
void mobile::right_reverse(uint8_t speed){
    digitalWrite(pin_a,0);
    analogWrite(pwm_a,speed); 
}
/********************************************************************************************/
void mobile::left_direct(uint8_t speed){
    digitalWrite(pin_b,0);
    analogWrite(pwm_b,speed);
}
/********************************************************************************************/
void mobile::left_reverse(uint8_t speed){
    digitalWrite(pin_b,1);
    analogWrite(pwm_b,255-speed); 
}
/********************************************************************************************/
/********************************************************************************************/





















