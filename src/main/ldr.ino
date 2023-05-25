int Ldr(int _pin){
  int potencia = analogRead(_pin);
  potencia = 1024 - potencia;
  return potencia;
}