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

int MaxLdr(int _new, int* _max){
  if (_new > *_max){
    *_max = _new;
    return _new;
  } else {
    return *_max;
  }
}

int MinLdr(int _new, int* _min){
  if (_new < *_min){
    *_min = _new;
    return _new;
  } else {
    return *_min;
  }
}

int IntensityAverage(int _intensity, int* _max, int* _min){
  int ldrmaxvalue = MaxLdr(_intensity, _max);
  int ldrminvalue = MinLdr(_intensity, _min);
  return (ldrmaxvalue + ldrminvalue)/2;
}