void Leds(int _pin, bool _value){
  if(_value){
    digitalWrite(_pin, HIGH);
  } else {
    digitalWrite(_pin, LOW);
  }
}