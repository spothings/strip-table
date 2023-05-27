void Relay(int _pin, bool _status){
  if(!_status){
    digitalWrite(pin_relay, HIGH);
  } else {
    digitalWrite(pin_relay, LOW);
  }
}

void RelayStatus(int _pin, bool _status, bool _value, int _delay) {
  if (RELAYWAIT < _delay * 10) {
    if (_status != _value){
      RELAYWAIT++;
    }
  } else {
    RELAYWAIT = 0;
    RELAYSTATUS = _value;
    Relay(_pin, _value);
  }
}