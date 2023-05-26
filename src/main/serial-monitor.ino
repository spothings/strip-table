void SerialMonitor(int _potencia, int _value){
  Serial.print(_potencia);
  Serial.print("\t");
  Serial.print(_value/10);
  Serial.print("\n");
}