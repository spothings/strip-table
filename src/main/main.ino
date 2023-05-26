int pin_ldr = A0;
int pin_relay = 16;

int relay_wait = 0;
bool relay_status = false, gelap = false;

void setup() {
  Serial.begin(115200);
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int intensitas = Ldr(A0);

  if(intensitas < 1024){
    gelap = true;
  } else {
    gelap = false;
  }

  if(gelap){
    RelayStatus(true);
  } else {
    RelayStatus(false);
  }

  Leds(LED_BUILTIN, intensitas);
  SerialMonitor(intensitas, relay_wait / 1000);
}
