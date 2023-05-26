#include <Arduino.h>
#include <ESP8266WiFi.h>

int pin_ldr = A0,
    pin_relay = 16,
    pin_led = LED_BUILTIN;

int relay_wait = 0,
    relay_delay = 10;
bool relay_status = false,
     malam = false;

void setup() {
  Serial.begin(115200);
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(pin_led, OUTPUT);

  WifiSetup();
}

void loop() {
  int intensitas = LdrAverage(A0);

  if (intensitas < 1024) {
    malam = true;
  } else {
    malam = false;
  }

  if (malam) {
    RelayStatus(pin_relay, true, relay_delay);
  } else {
    RelayStatus(pin_relay, false, relay_delay);
  }

  Leds(pin_led, intensitas);
  SerialMonitor(intensitas, relay_wait);
}
