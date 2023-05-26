void SerialMonitor(int _potencia, int _waiting, int _maxldr, int _minldr){
  Serial.print(_potencia);
  Serial.print("\t");
  Serial.print(_waiting/10);
  Serial.print("\t");
  Serial.print(_maxldr);
  Serial.print("\t");
  Serial.print(_minldr);
  Serial.print("\n");
}