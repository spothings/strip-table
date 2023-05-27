void Leds(int _pin, int _value){
  if(!_value){
    digitalWrite(_pin, HIGH);
  } else {
    digitalWrite(_pin, LOW);
  }
}