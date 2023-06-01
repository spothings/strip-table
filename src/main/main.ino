#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Add root certificate for api.telegram.org
X509List cert(TELEGRAM_CERTIFICATE_ROOT);

const int
  pin_ldr = A0,           // pin LDR
  pin_relay = 16,         // pin relay
  pin_led = LED_BUILTIN,  // pin LED
  relay_delay = 60;       // relay delay to turn on or off relay, in secon

int
  TDELAY = 10000,
  RELAYWAIT = 0,  // increment value to wait condision
  MAXLDR = 0,     // min value for LDR by default
  MINLDR = 1024;  // max value for LDR by default

bool
  RELAYSTATUS,  // relay status (on or off)
  SLEEP;        // sensor read status (on or off)

void setup() {
  Serial.begin(115200);
  pinMode(pin_ldr, INPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(pin_led, OUTPUT);

  // setup Wifi
  WifiSetup();

  // setup time ntp
  setupNTP();

  // setup telegram bot
  TelegramSetup();

  Leds(pin_led, true);
  Relay(pin_relay, false);
  RELAYSTATUS = false;
  SLEEP = false;
}

void loop() {
  if (!SLEEP) {
    // get time (morning or night)
    bool night = GetTime();

    // LDR sensor set only works at night
    if (night) {
      int
        // get LDR value with average
        intensity = LdrAverage(pin_ldr),

        // set value for lightLimit with auto sampling
        lightLimit = IntensityAverage(intensity, MAXLDR, MINLDR);

      bool
        // get bright value
        bright = Bright(intensity, lightLimit);

      // turn on or off relay
      RelayStatus(pin_relay, intensity, lightLimit, RELAYSTATUS, bright, relay_delay);

      // print to serial monitor
      PrintMonitor(intensity, RELAYWAIT, MAXLDR, MINLDR, lightLimit, RELAYSTATUS);
    }

    // if morning, it's time to rest 😴
    else {
      TDELAY = 0;
      Relay(pin_relay, false);
    }
  }
  // check message from telegram
  Telegram();
}