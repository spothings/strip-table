void Relay(int _pin, int _value){
  if(_value < 1024){
    digitalWrite(pin_relay, LOW);
  } else {
    digitalWrite(pin_relay, HIGH);
  }
}