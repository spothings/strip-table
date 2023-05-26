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

int MaxLdr(int _new, int _old){
  if (_new > _old){
    maxldr = _new;
    return _new;
  } else {
    return _old;
  }
}

int MinLdr(int _new, int _old){
  if (_new < _old){
    minldr = _new;
    return _new;
  } else {
    return _old;
  }
}

int IntensitasAverage(int _intensitas, int _max, int _min){
  int ldfmaxvalue = MaxLdr(_intensitas, _max);
  int ldfminvalue = MinLdr(_intensitas, _min);
  return (ldfmaxvalue + ldfminvalue)/2;
}