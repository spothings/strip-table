void Relay(int _pin, bool _status){
  if(_status){
    digitalWrite(pin_relay, LOW);
  } else {
    digitalWrite(pin_relay, HIGH);
  }
}

void RelayStatus(int _pin, int _intensity, int _lightLimit, bool _relay, bool _bright, int _delay) {
  if (_intensity > _lightLimit) {
    if (RELAYSTATUS) {
      RELAYWAIT = 0;
    }
  } else {
    if (!RELAYSTATUS) {
      RELAYWAIT = 0;
    }
  }

  if (RELAYWAIT < _delay * 10) {
    if (_relay != _bright) {
      RELAYWAIT++;
    }
  } else {
    RELAYWAIT = 0;
    RELAYSTATUS = _bright;
    Relay(_pin, _bright);
  }
}