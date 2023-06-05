void Relay(int _pin, bool _status){
  if(_status){
    digitalWrite(_pin, LOW);
  } else {
    digitalWrite(_pin, HIGH);
  }
}

void RelayStatus(int _pin, int _intensity, int _lightLimit, int _relay_delay, int* _relay_wait, bool* _relay_status, bool _bright) {
  if (_intensity > _lightLimit) {
    if (*_relay_status) {
      *_relay_wait = 0;
    }
  } else {
    if (!*_relay_status) {
      *_relay_wait = 0;
    }
  }

  if (*_relay_wait < _relay_delay * 10) {
    if (*_relay_status != _bright) {
      *_relay_wait += 1;
    }
  } else {
    *_relay_wait = 0;
    *_relay_status = _bright;
    Relay(_pin, _bright);
  }
}