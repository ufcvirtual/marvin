/*******************************************************************************************/
/*********************************CLASSE****************************************************/
/*******************************************************************************************/
#define BRAKING_POINT 1
#define COUNT 100
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

  uint16_t analog_read(uint16_t pin,uint16_t nivel);
  void check(uint16_t steps_L,uint16_t steps_R);//não usado
  void speed_smooth(uint16_t steps_L,uint16_t steps_R,uint16_t speed);//não usado
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
  void right_direct();
  void right_reverse();
  void left_direct();
  void left_reverse();

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
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  boolean flag_L = true,flag_R = true;
  right_direct();
  left_direct();
  uint8_t aux_R = 0,aux_L = 0;
  while(encoder_R <= steps ||encoder_L <= steps ){
    uint16_t read_R = analog_read(pin_enc_R,500);
    //verificar o estado do encoder
    if(read_R != status_R){
      encoder_R++;
      status_R = read_R;
      flag_R = stop_R();//parar roda direita 
      //delay(10);
      //Serial.print("encoder_R: ");
      //Serial.println(encoder_R);
    }
    uint16_t read_L = analog_read(pin_enc_L,500);
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      flag_L = stop_L();//parar roda esquerda
      //delay(10); 
      //Serial.print("\t\tencoder_L: ");
      //Serial.println(encoder_L);
    }
    if(encoder_L < encoder_R && flag_R && flag_L){
      //right_direct();
      left_direct();
      flag_L = false;
    }
    if(encoder_R <= encoder_L && flag_R && flag_L){
      right_direct();
      //left_direct();
      flag_R = false;
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
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  boolean flag_L = true,flag_R = true;
  right_reverse();
  left_reverse();
  uint8_t aux_R = 0,aux_L = 0;
  while(encoder_R <= steps ||encoder_L <= steps ){
    uint16_t read_R = analog_read(pin_enc_R,500);
    //verificar o estado do encoder
    if(read_R != status_R){
      encoder_R++;
      status_R = read_R;
      flag_R = stop_R();//parar roda direita
      //delay(10); 
      //Serial.print("encoder_R: ");
      //Serial.println(encoder_R);
    }
    uint16_t read_L = analog_read(pin_enc_L,500);
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      flag_L = stop_L();//parar roda esquerda 
      //delay(10);
      //Serial.print("\t\tencoder_L: ");
      //Serial.println(encoder_L);
    }
    if(encoder_L < encoder_R && flag_R && flag_L){
      //right_reverse();
      left_reverse();
      flag_L = false;
    }
    if(encoder_R <= encoder_L && flag_R && flag_L){
      right_reverse();
      //left_reverse();
      flag_R = false;
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
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  boolean flag_L = true,flag_R = true;

  //left_direct();
  right_reverse();

  uint8_t aux_R = 0,aux_L = 0;
  while(encoder_R <= steps || encoder_L <= steps ){
    uint16_t read_R = analog_read(pin_enc_R,500);
    //verificar o estado do encoder
    if(read_R != status_R){
      encoder_R++;
      status_R = read_R;
      flag_R = stop_R();//parar roda direita 
      //delay(10);
      //Serial.print("encoder_R: ");
      //Serial.println(encoder_R);
    }
    uint16_t read_L = analog_read(pin_enc_L,500);
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      flag_L = stop_L();//parar roda esquerda 
      //delay(10);
      //Serial.print("\t\tencoder_L: ");
      //Serial.println(encoder_L);
    }
    if(encoder_L < encoder_R && flag_R && flag_L){
      left_direct();
      //right_reverse();
      flag_L = false;
    }
    if(encoder_R <= encoder_L && flag_R && flag_L){
      //left_direct();
      right_reverse();
      flag_R = false;
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
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  encoder_L = 0;
  encoder_R = 0;
  uint16_t status_R = analog_read(pin_enc_R,500);
  uint16_t status_L = analog_read(pin_enc_L,500);
  boolean flag_L = true,flag_R = true;
  right_direct();
  //left_reverse();
  uint8_t aux_R = 0,aux_L = 0;
  while(encoder_R <= steps ||encoder_L <= steps ){    
    uint16_t read_R = analog_read(pin_enc_R,500);
    //verificar o estado do encoder
    if(read_R != status_R){
      encoder_R++;
      status_R = read_R;
      flag_R = stop_R();//parar roda direita 
      //delay(10);
      //Serial.print("encoder_R: ");
      //Serial.println(encoder_R);
    }
    uint16_t read_L = analog_read(pin_enc_L,500);
    if(read_L != status_L){
      status_L = read_L;
      encoder_L++;
      flag_L = stop_L();//parar roda esquerda 
      //delay(10);
      //Serial.print("\t\tencoder_L: ");
      //Serial.println(encoder_L);
    }
    if(encoder_L < encoder_R && flag_R && flag_L){
      //right_direct();
      left_reverse();
      flag_L = false;
    }
    if(encoder_R <= encoder_L && flag_R && flag_L){
      right_direct();
      //left_reverse();
      flag_R = false;
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
}
/********************************************************************************************/
//retorna 1 se a leitura analogica esta acima de level
uint16_t mobile::analog_read(uint16_t pin,uint16_t level){
  uint16_t num = analogRead(pin);
  if(num >= level) return 1;
  else return 0;

}
/********************************************************************************************/
void mobile::right_direct(){
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}
/********************************************************************************************/
void mobile::right_reverse(){
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}
/********************************************************************************************/
void mobile::left_direct(){
  digitalWrite(in1,1);
  digitalWrite(in2,0);
}
/********************************************************************************************/
void mobile::left_reverse(){
  digitalWrite(in1,0);
  digitalWrite(in2,1);
}
/********************************************************************************************/
/********************************************************************************************/




















