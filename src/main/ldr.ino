int Ldr(int _pin){
  int potencia = analogRead(_pin);
  return potencia;
}

// is turn off because conflict with telegram
int LdrAverage(int _pin){
  int potencia = 0;
  for(int i=0; i < 1000; i++){
    potencia += Ldr(_pin);
  }
  potencia /= 1000;
  // int potencia = Ldr(_pin);
  return potencia;
}

int MaxLdr(int _new, int _old){
  if (_new > _old){
    MAXLDR = _new;
    return _new;
  } else {
    return _old;
  }
}

int MinLdr(int _new, int _old){
  if (_new < _old){
    MINLDR = _new;
    return _new;
  } else {
    return _old;
  }
}

int IntensityAverage(int _intensity, int _max, int _min){
  int ldrmaxvalue = MaxLdr(_intensity, _max);
  int ldrminvalue = MinLdr(_intensity, _min);
  return (ldrmaxvalue + ldrminvalue)/2;
}