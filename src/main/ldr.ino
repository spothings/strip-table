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

void MaxLdr(int _new, int* _max){
  if (_new > *_max){
    *_max = _new;
  }
}

void MinLdr(int _new, int* _min){
  if (_new < *_min){
    *_min = _new;
  }
}

void GenerateLimit(int _intensity, int* _max, int* _min){
  MaxLdr(_intensity, _max);
  MinLdr(_intensity, _min);
}

int MedianLDR(int _max, int _min){
  return (StorageRead(_max) + StorageRead(_min)) / 2;
}