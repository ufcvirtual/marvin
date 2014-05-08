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
    return distancia;
}
