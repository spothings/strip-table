#include <ESP8266WiFi.h>           // for connect to WiFi
#include <WiFiUdp.h>               // for use UDP protocol NTP client
#include <NTPClient.h>             // for use NTP Client
#include <UniversalTelegramBot.h>  // for use Telegram bot
#include <ArduinoJson.h>           // Telegram bot requeretment
#include <EEPROM.h>                // for use EEPROM storage

const int
  // declarate pin
  PINLDR = A0,           // pin LDR sensor
  PINRELAY = 16,         // pin relay / lamp
  PINLED = LED_BUILTIN,  // pin LED (built in led)

  // set EEPROM address
  ADDRMAX = 0,  // address for max LDR
  ADDRMIN = 4,  // address for min LDR

  // relay delay to turn on or off relay, in secon
  RELAYDELAY = 5;


int
  tdelay,  // set telegram delay value
  rwait,   // increment value to wait condision
  maxldr,  // save new min value for LDR
  minldr,  // save new max value for LDR
  medldr;  // set value for light limit to read night or day

bool
  sleep,    // sensor read status (sleep or scan)
  night,    // variable for night status (night or day)
  rstatus;  // relay status (on or off)

void setup() {
  Serial.begin(115200);

  // set pin mode (input or output)
  pinMode(PINLDR, INPUT);     // pin LDR
  pinMode(PINLED, OUTPUT);    // pin LED
  pinMode(PINRELAY, OUTPUT);  // pin Relay /lamp

  WifiSetup();      // setup WiFi
  NTPSetup();       // setup NTP time
  EEPROMSetup();    // setup Storage
  TelegramSetup();  // setup Telegram bot

  // set setup value
  Leds(PINLED, true);                    // turn on led
  Relay(PINRELAY, false);                // turn off relay
  sleep = false;                         // set as not sleep
  rstatus = false;                       // set relay status off
  night = true;                          // set day as night
  tdelay = 10000;                        // set telegram read message as 10 second
  rwait = 0;                             // resset increment relay wait
  maxldr = 0;                            // set min value for maxldr
  minldr = 1024;                         // set max value for minldr
  medldr = MedianLDR(ADDRMAX, ADDRMIN);  // set bright or dark
}

void loop() {
  if (!sleep) {
    if (night != GetTime()) { Daily(); }  // get time (day or night), is reset every day. If morning, it's time to rest 😴
    if (night) { Night(); }               // LDR sensor set only works at night
  }
  Telegram(PINLED, PINRELAY, &tdelay, &sleep, ADDRMAX, ADDRMIN, maxldr, minldr, &medldr);  // check message from telegram
}

void Daily() {

  // get night value
  night = GetTime();

  if (night) {
    // set telegram delay to oftimize sensor scan
    tdelay = 10000;

    // turn on relay for feadback
    Relay(PINRELAY, true);

    // update max and min value in EEPROM
    StorageWrite(ADDRMAX, maxldr);
    StorageWrite(ADDRMIN, minldr);

    // reset max and min temporary value
    maxldr = 0;
    minldr = 1024;

    // get median value for parameter bright or dark
    medldr = MedianLDR(ADDRMAX, ADDRMIN);

  } else {
    // remove telegram delay for speed up bot response
    tdelay = 0;

    // turn off relay for feadback
    Relay(PINRELAY, false);
  }
}

void Night() {

  // get LDR value with average
  int intensity = LdrAverage(PINLDR);

  // get bright value (bright or dark)
  bool bright = Bright(intensity, medldr);

  // generate lightLimit with auto sampling
  GenerateLimit(intensity, &maxldr, &minldr);

  // turn on or off relay
  RelayStatus(PINRELAY, intensity, medldr, RELAYDELAY, &rwait, &rstatus, bright);

  // print to serial monitor
  PrintMonitor(intensity, rwait, StorageRead(ADDRMAX), StorageRead(ADDRMIN), medldr, rstatus);
}