void PrintMonitor(int _potencia, int _waiting, int _maxldr, int _minldr, int _lightLimit, bool _relayStatus) {
  Serial.print(_potencia);
  Serial.print("\t");
  Serial.print(_waiting / 10);
  Serial.print("\t");
  Serial.print(_maxldr);
  Serial.print("\t");
  Serial.print(_minldr);
  Serial.print("\t");
  Serial.print(_lightLimit);
  Serial.print("\t");

  if (_potencia < _lightLimit) {
    Serial.print("dark");
  } else {
    Serial.print("bright");
  }

  Serial.print("\t");

  if (_relayStatus) {
    Serial.print("On");
  } else {
    Serial.print("Off");
  }
  
  Serial.print("\n");
}