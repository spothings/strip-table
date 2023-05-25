void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int intensitas = Ldr(A0);
  Leds(LED_BUILTIN, intensitas);
  SerialMonitor(intensitas);
}
