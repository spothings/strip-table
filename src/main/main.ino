#include <ESP8266WiFi.h>           // for connect to WiFi
#include <WiFiUdp.h>               // for use UDP protocol NTP client
#include <NTPClient.h>             // for use NTP Client
#include <UniversalTelegramBot.h>  // for use Telegram bot
#include <ArduinoJson.h>           // Telegram bot requeretment
#include <EEPROM.h>                // for use EEPROM storage

const int
  PINLDR = A0,           // pin LDR sensor
  PINRELAY = 16,         // pin relay / lamp
  PINLED = LED_BUILTIN,  // pin LED (built in led)
  RELAYDELAY = 60;       // relay delay to turn on or off relay, in secon

int
  tdelay = 10000,  // set telegram delay value
  relay_wait = 0,  // increment value to wait condision
  maxldr = 0,      // min value for LDR by default
  minldr = 1024;   // max value for LDR by default

bool
  relay_status,  // relay status (on or off)
  night,         // variable for night status
  sleep;         // sensor read status (on or off)

void setup() {
  //Init Serial USB
  Serial.begin(115200);

  // set pin mode (input or output)
  pinMode(PINLDR, INPUT);
  pinMode(PINRELAY, OUTPUT);
  pinMode(PINLED, OUTPUT);

  WifiSetup();      // setup WiFi
  NTPSetup();       // setup NTP time
  TelegramSetup();  // setup Telegram bot

  // set setup value
  Leds(PINLED, true);
  Relay(PINRELAY, false);
  relay_status = false;
  night = true;
  sleep = false;
}

void loop() {
  if (!sleep) {
    // get time (day or night)
    // if day, it's time to rest 😴
    if (night != GetTime()) {
      if (night) {
        tdelay = 10000;
      } else {
        tdelay = 0;
        Relay(PINRELAY, false);
      }
      night = GetTime();
    }

    // LDR sensor set only works at night
    if (night) {
      int
        // get LDR value with average
        intensity = LdrAverage(PINLDR),

        // set value for lightLimit with auto sampling
        lightLimit = IntensityAverage(intensity, &maxldr, &minldr);

      bool
        // get bright value
        bright = Bright(intensity, lightLimit);

      // turn on or off relay
      RelayStatus(PINRELAY, intensity, lightLimit, RELAYDELAY, &relay_wait, &relay_status, bright);

      // print to serial monitor
      PrintMonitor(intensity, relay_wait, maxldr, minldr, lightLimit, relay_status);
    }
  }
  // check message from telegram
  Telegram(PINLED, PINRELAY, &tdelay, &sleep);
}