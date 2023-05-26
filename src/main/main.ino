int pin_ldr = A0;
int pin_relay = 16;

void setup() {
  Serial.begin(115200);
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int intensitas = Ldr(A0);

  Relay(pin_relay, intensitas);
  Leds(LED_BUILTIN, intensitas);
  SerialMonitor(intensitas);
}
