int Ldr(int _pin){
  int potencia = analogRead(_pin);
  return potencia;
}

int LdrAverage(int _pin){
  int potencia = 0;
  for(int i=0; i < 1000; i++){
    potencia += Ldr(_pin);
  }
  potencia /= 1000;
  return potencia;
}