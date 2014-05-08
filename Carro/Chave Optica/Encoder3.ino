/*******************************************************************************************/
/*********************************CLASSE****************************************************/
/*******************************************************************************************/
class mobile{
private:
  //Pinos de acionamento do drive dos motores
  int in1;
  int in2;
  int in3;
  int in4;
  //int pin_pwm;
  //Variaveis de contagem dos encoderes
  int encoder_L;
  int encoder_R;
  //Pinos dos encoderes
  int pin_enc_L;
  int pin_enc_R;
  //Pinos de pwm
  int pin_pwm_L;
  int pin_pwm_R;
  int analog_read(int pin,int nivel);
  void verifica(int steps,int pwm);
  boolean wheel_stop_1();
  boolean wheel_stop_2();
public:
  //Construtor
  mobile(int pin1,int pin2,int pin3,int pin4,int pwm_L,int pwm_R,int enc_L,int enc_R);//enc_L,enc_R devem ser entradas analógicas
  /***********Funções*************/
  void forward(int steps,int pwm);
  void left(int steps,int pwm);
  void right(int steps,int pwm);
  void back(int steps,int pwm); 
  void check(int steps,int pwm);//só para testes.

};
/********************************************************************************************/
/*Funções*/
/********************************************************************************************/
mobile::mobile(int pin1,int pin2,int pin3,int pin4,int pwm_L,int pwm_R,int enc_L,int enc_R){
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
void mobile::forward(int steps,int pwm){
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  verifica(steps,pwm);
}
/********************************************************************************************/
void mobile::back(int steps,int pwm){
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  verifica(steps,pwm);
}
/********************************************************************************************/
void mobile::left(int steps,int pwm){
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  verifica(steps,pwm);
}
/********************************************************************************************/
void mobile::right(int steps,int pwm){
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
  analogWrite(pin_pwm_L,pwm);
  analogWrite(pin_pwm_R,pwm);
  verifica(steps,pwm);
}
/********************************************************************************************/
boolean mobile::wheel_stop_1(){
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  analogWrite(pin_pwm_L,0);
  return true;
}
/********************************************************************************************/
boolean mobile::wheel_stop_2(){
  digitalWrite(in3,0);
  digitalWrite(in4,0);
  analogWrite(pin_pwm_L,0);
  return true;
}
/********************************************************************************************/
void mobile::verifica(int steps,int pwm){
  encoder_L = 0;
  encoder_R = 0;
  uint8_t status1 = 0, status2 = 0;
  boolean flag1 = false,flag2 = false;
  while(1){
    if(encoder_L >= steps && !flag1){
      flag1 = wheel_stop_1();
    }
    if(encoder_R >= steps && !flag2){
      flag2 = wheel_stop_2();
    }
    //verifica o estado da leitura digital, se for diferente incrementa 
    if(encoder_L <= steps){
      //int aux = digitalRead(pin_enc_L);
      int aux = analog_read(pin_enc_L,100);
      if(status1 != aux)encoder_L++;
      status1 = aux;
    }
    if(encoder_R <= steps){
      //int aux = digitalRead(pin_enc_R);
      int aux = analog_read(pin_enc_R,100);
      if(status2 != aux)encoder_R++;
      status2 = aux;
    }
    if(flag1 && flag2)break;//caso os dois encoders tenham terminado a contagem, sair do laço
  }
  wheel_stop_1();
  wheel_stop_2();
}
/********************************************************************************************/
void mobile::check(int steps,int pwm){
  encoder_L = 0;
  encoder_R = 0;
  uint8_t status1 = 0, status2 = 0;
  boolean flag1 = false,flag2 = false;
  while(1){
    if(encoder_L >= steps && !flag1){
      flag1 = wheel_stop_1();
    }
    if(encoder_R >= steps && !flag2){
      flag2 = wheel_stop_2();
    }
    //verifica o estado da leitura digital, se for diferente incrementa 
    if(encoder_L <= steps){
      //int aux = digitalRead(pin_enc_L);
      int aux = analog_read(pin_enc_L,100);
      if(status1 != aux)encoder_L++;
      status1 = aux;
    }
    if(encoder_R <= steps){
      //int aux = digitalRead(pin_enc_R);
      int aux = analog_read(pin_enc_R,100);
      if(status2 != aux)encoder_R++;
      status2 = aux;
    }
    if(flag1 && flag2)break;//caso os dois encoders tenham terminado a contagem, sair do laço
  }
  wheel_stop_1();
  wheel_stop_2();
}
/********************************************************************************************/
int mobile::analog_read(int pin,int nivel){
  int num = analogRead(pin);
  if(num >= nivel) return 1;
  else return 0;

}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/



