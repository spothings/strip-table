void Relay(int _pin, bool _status){
  if(_status){
    digitalWrite(pin_relay, HIGH);
  } else {
    digitalWrite(pin_relay, LOW);
  }
}

void RelayStatus(bool _value){
  if(relay_wait < 10 * 1000){
    relay_wait++;
  } else {
    relay_status = _value;
    Relay(pin_relay, !_value);
    relay_wait = 0;
  }
}