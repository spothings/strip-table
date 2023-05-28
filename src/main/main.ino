#include <Arduino.h>
#include <ESP8266WiFi.h>

const int
  pin_ldr = A0,           // pin LDR
  pin_relay = 16,         // pin relay
  pin_led = LED_BUILTIN,  // pin LED
  relay_delay = 60;       // relay delay to turn on or off relay

int
  RELAYWAIT = 0,  // increment value to wait condision
  MAXLDR = 0,     // min value for LDR by default
  MINLDR = 1024;  // max value for LDR by default

bool
  RELAYSTATUS = true,  // relay status on or off
  GELAP = true,        // light status (gelap or terang)
  MALAM = true;

void setup() {
  Serial.begin(115200);
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(pin_led, OUTPUT);

  // Relay(pin_relay, false);  // by default turn off relay
  WifiSetup();

  //Setup time ntp
  setupNTP();
}

void loop() {
  // get LDR value
  int intensitas = LdrAverage(pin_ldr);

  // set max and min LDR value with average
  int nilaigelap = IntensitasAverage(intensitas, MAXLDR, MINLDR);

  // set light status (gelap or terang)
  if (MALAM) {
    if (intensitas < nilaigelap) {
      if (GELAP == false) {
        RELAYWAIT = 0;
        GELAP = true;
      }
    } else {
      if (GELAP == true) {
        RELAYWAIT = 0;
        GELAP = false;
      }
    }
  } else {
    GELAP = false;
    RELAYSTATUS = false;
  }

  // CODE FOR NTP CLIENT
  // amen peteng, set variabel -> MALAM = true | amen tengai, set variablel -> MALAM = false
  int ntpTime = getTimeNTP();
  if(ntpTime > 18 and ntpTime < 7){
    MALAM = true;
  }else{
    MALAM = false;
  }

  // turn on built in led by light status
  Leds(pin_led, GELAP);

  // turn on or off relay
  RelayStatus(pin_relay, RELAYSTATUS, GELAP, relay_delay);

  // print to serial monitor
  SerialMonitor(intensitas, RELAYWAIT, MAXLDR, MINLDR, nilaigelap, GELAP);
}
