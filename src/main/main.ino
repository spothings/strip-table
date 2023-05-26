int pin_ldr = A0;
int pin_relay = 16;

int relay_wait = 0;
bool relay_status = false;

bool gelap = false;

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
    if(relay_wait < 10 * 1000){
      relay_wait++;
    } else {
      relay_status = true;
      Relay(pin_relay, false);
      relay_wait = 0;
    }
  } else {
    if(relay_wait < 10 * 1000){
      relay_wait++;
    } else {
      relay_status = false;
      Relay(pin_relay, true);
      relay_wait = 0;
    }
  }

  Leds(LED_BUILTIN, intensitas);
  SerialMonitor(intensitas, relay_wait / 1000);
}
