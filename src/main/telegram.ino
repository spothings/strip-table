WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Add root certificate for api.telegram.org
X509List cert(TELEGRAM_CERTIFICATE_ROOT);

// Checks for new messages every 1 second.
unsigned long lastTimeBotRan;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
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
      if (SLEEP) {
        bot.sendMessage(chat_id, "system is sleep", "");
      } else {
        bot.sendMessage(chat_id, "system is wakeup", "");
      }
    }

    if (text == "/sleep") {
      Leds(pin_led, false);
      Relay(pin_relay, false);
      SLEEP = true;
      *TDELAY = 0;
      if (SLEEP) {
        bot.sendMessage(chat_id, "system is sleep", "");
      } else {
        bot.sendMessage(chat_id, "system is wakeup", "");
      }
    }

    if (text == "/wakeup") {
      Leds(pin_led, true);
      Relay(pin_relay, true);
      SLEEP = false;
      *TDELAY = 10000;
      if (SLEEP) {
        bot.sendMessage(chat_id, "system is sleep", "");
      } else {
        bot.sendMessage(chat_id, "system is wakeup", "");
      }
    }
  }
}

void TelegramSetup() {
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  client.setTrustAnchors(&cert);     // Add root certificate for api.telegram.org
}

void Telegram() {
  if (millis() > lastTimeBotRan + *TDELAY) {
    Serial.println("read telegram message");
    Leds(pin_led, false);
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  Leds(pin_led, true);
}