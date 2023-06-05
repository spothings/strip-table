void Relay(int _pin, bool _status){
  if(_status){
    digitalWrite(pin_relay, LOW);
  } else {
    digitalWrite(pin_relay, HIGH);
  }
}

void RelayStatus(int _pin, int _intensity, int _lightLimit, int _relay_delay, bool* _relay_status, bool _bright) {
  if (_intensity > _lightLimit) {
    if (*_relay_status) {
      *RELAYWAIT = 0;
    }
  } else {
    if (!*_relay_status) {
      *RELAYWAIT = 0;
    }
  }

  if (*RELAYWAIT < _relay_delay * 10) {
    if (*_relay_status != _bright) {
      *RELAYWAIT += 1;
    }
  } else {
    *RELAYWAIT = 0;
    *_relay_status = _bright;
    Relay(_pin, _bright);
  }
}