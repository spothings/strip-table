#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <UniversalTelegramBot.h>

const int
  pin_ldr = A0,           // pin LDR
  pin_relay = 16,         // pin relay
  pin_led = LED_BUILTIN,  // pin LED
  relay_delay = 60;       // relay delay to turn on or off relay, in secon

int
  tdelay = 10000,  // set telegram delay value
  relay_wait = 0,  // increment value to wait condision
  maxldr = 0,      // min value for LDR by default
  minldr = 1024;   // max value for LDR by default

bool
  relay_status,  // relay status (on or off)
  sleep;         // sensor read status (on or off)

int
  *TDELAY = &tdelay,
  *RELAYWAIT = &relay_wait,
  *MAXLDR = &maxldr,
  *MINLDR = &minldr;

bool
  *RELAYSTATUS = &relay_status,
  *SLEEP = &sleep;

void setup() {
  //Init Serial USB
  Serial.begin(115200);

  // set pin mode (input or output)
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(pin_led, OUTPUT);

  WifiSetup();      // setup WiFi
  NTPSetup();       // setup NTP time
  TelegramSetup();  // setup Telegram bot

  // set setup value
  Leds(pin_led, true);
  Relay(pin_relay, false);
  *RELAYSTATUS = false;
  *SLEEP = false;
}

void loop() {
  if (!*SLEEP) {
    // get time (day or night)
    bool night = true;  //GetTime();

    // LDR sensor set only works at night
    if (night) {
      *TDELAY = 10000;

      int
        // get LDR value with average
        intensity = LdrAverage(pin_ldr),

        // set value for lightLimit with auto sampling
        lightLimit = IntensityAverage(intensity, *MAXLDR, *MINLDR);

      bool
        // get bright value
        bright = Bright(intensity, lightLimit);

      // turn on or off relay
      RelayStatus(pin_relay, intensity, lightLimit, *RELAYSTATUS, bright, relay_delay);

      // print to serial monitor
      PrintMonitor(intensity, *RELAYWAIT, *MAXLDR, *MINLDR, lightLimit, *RELAYSTATUS);
    }

    // if day, it's time to rest 😴
    else {
      *TDELAY = 0;
      Relay(pin_relay, false);
    }
  }
  // check message from telegram
  Telegram();
}