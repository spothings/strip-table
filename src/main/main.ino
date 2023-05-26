#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif

int pin_ldr         = A0,
    pin_relay       = 16
;

bool  relay_status  = false, 
      gelap         = false
;

int relay_wait = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  WifiSetup();
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
