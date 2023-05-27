#include <Arduino.h>
#include <ESP8266WiFi.h>

const int
  pin_ldr = A0,
  pin_relay = 16,
  pin_led = LED_BUILTIN,
  relay_delay = 60;

int
  RELAYWAIT = 0,
  MAXLDR = 0,
  MINLDR = 1024;

bool
  RELAYSTATUS = false,
  GELAP = false;

void setup() {
  Serial.begin(115200);
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(pin_led, OUTPUT);

  Relay(pin_relay, false);
  WifiSetup();
}

void loop() {
  int intensitas = LdrAverage(pin_ldr);
  int nilaigelap = IntensitasAverage(intensitas, MAXLDR, MINLDR);

  if (intensitas < nilaigelap) {
    if (GELAP == false){
      RELAYWAIT = 0;
      GELAP = true;
    }
  } else {
    if (GELAP == true){
      RELAYWAIT = 0;
      GELAP = false;
    }
  }

  Leds(pin_led, GELAP);
  RelayStatus(pin_relay, RELAYSTATUS, GELAP, relay_delay);
  SerialMonitor(intensitas, RELAYWAIT, MAXLDR, MINLDR, nilaigelap, GELAP);
}
