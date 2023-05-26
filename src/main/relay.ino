void Relay(int _pin, bool _status){
  if(_status){
    digitalWrite(pin_relay, HIGH);
  } else {
    digitalWrite(pin_relay, LOW);
  }
}

void RelayStatus(int _pin, bool _value, int _delay) {
  if (relay_wait < _delay * 10) {
    relay_wait++;
  } else {
    relay_status = _value;
    Relay(_pin, !_value);
    relay_wait = 0;
  }
}