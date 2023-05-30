#include <Arduino.h>
#include <ESP8266WiFi.h>

const int
  pin_ldr = A0,           // pin LDR
  pin_relay = 16,         // pin relay
  pin_led = LED_BUILTIN,  // pin LED
  relay_delay = 600;      // relay delay to turn on or off relay, 600 = 60 second or 1 minute

int
  RELAYWAIT = 0,  // increment value to wait condision
  MAXLDR = 0,     // min value for LDR by default
  MINLDR = 1024;  // max value for LDR by default

bool
  RELAYSTATUS;  // relay status (on or off)

void setup() {
  Serial.begin(115200);
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(pin_led, OUTPUT);

  // setup Wifi
  WifiSetup();

  // setup time ntp
  setupNTP();
}

void loop() {
  // get time (morning or night)
  bool night = GetTime();

  // LDR sensor set only works at night
  if (night) {
    // get LDR value with average
    int intensity = LdrAverage(pin_ldr);

    // set value for lightLimit with auto sampling
    int lightLimit = IntensityAverage(intensity, MAXLDR, MINLDR);

    // turn on built in led by light status
    Leds(pin_led, !RELAYSTATUS);

    // turn on or off relay
    RelayStatus(pin_relay, intensity, lightLimit, RELAYSTATUS, !RELAYSTATUS, relay_delay);

    // print to serial monitor
    PrintMonitor(intensity, RELAYWAIT, MAXLDR, MINLDR, lightLimit, RELAYSTATUS);
  }

  // if morning, it's time to rest 😴
  else {
    Relay(pin_relay, false);
  }
}