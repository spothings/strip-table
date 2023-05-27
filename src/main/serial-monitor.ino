void SerialMonitor(int _potencia, int _waiting, int _maxldr, int _minldr, int _nilaimalam, bool _malam){
  Serial.print(_potencia);
  Serial.print("\t");
  Serial.print(_waiting/10);
  Serial.print("\t");
  Serial.print(_maxldr);
  Serial.print("\t");
  Serial.print(_minldr);
  Serial.print("\t");
  Serial.print(_nilaimalam);
  Serial.print("\t");
  if (_malam){
    Serial.print("gelap");
  } else {
    Serial.print("terang");
  }
  Serial.print("\n");
}