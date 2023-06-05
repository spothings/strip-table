WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Add root certificate for api.telegram.org
X509List cert(TELEGRAM_CERTIFICATE_ROOT);

// Checks for new messages every 1 second.
unsigned long lastTimeBotRan;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages, int _led, int _relay, int* _tdelay, bool* _sleep, int _addrmax, int _addrmin, int _maxldr, int _minldr, int* _medldr) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/status") {
      if (*_sleep) {
        bot.sendMessage(chat_id, "system is sleep", "");
      } else {
        bot.sendMessage(chat_id, "system is wakeup", "");
      }
    }

    if (text == "/sleep") {
      Leds(_led, false);
      Relay(_relay, false);
      *_sleep = true;
      *_tdelay = 0;
      if (*_sleep) {
        bot.sendMessage(chat_id, "system is sleep", "");
      } else {
        bot.sendMessage(chat_id, "system is wakeup", "");
      }
    }

    if (text == "/wakeup") {
      Leds(_led, true);
      Relay(_relay, true);
      *_sleep = false;
      *_tdelay = 10000;
      if (*_sleep) {
        bot.sendMessage(chat_id, "system is sleep", "");
      } else {
        bot.sendMessage(chat_id, "system is wakeup", "");
      }
    }

    if (text == "/generate") {
      Serial.println(_maxldr);
      Serial.println(_minldr);
      StorageWrite(_addrmax, _maxldr);
      StorageWrite(_addrmin, _minldr);
      *_medldr = MedianLDR(_addrmax, _addrmin);
      bot.sendMessage(chat_id, "done generate", "");
    }
  }
}

void TelegramSetup() {
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  client.setTrustAnchors(&cert);     // Add root certificate for api.telegram.org
}

void Telegram(int _led, int _relay, int* _tdelay, bool* _sleep, int _addrmax, int _addrmin, int _maxldr, int _minldr, int* _medldr) {
  if (millis() > lastTimeBotRan + *_tdelay) {
    Serial.println("read telegram message");
    Leds(_led, false);
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages, _led, _relay, _tdelay, _sleep, _addrmax, _addrmin, _maxldr, _minldr, _medldr);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  Leds(_led, true);
}