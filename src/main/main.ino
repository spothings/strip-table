void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(D0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int intensitas = Ldr(A0);\
  
  if(intensitas < 500){
    Relay(D0, true);
  } else {
    Relay(D0, false);
  }
  
  Leds(LED_BUILTIN, intensitas);
  SerialMonitor(intensitas);
}
