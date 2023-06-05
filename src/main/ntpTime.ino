// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void NTPSetup() {
  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(28800);  // add 3600 each 1 GMT (8*3600 = 28800)
}

int getTimeNTP() {
  timeClient.update();
  int currentHour = timeClient.getHours();  // get current hours ntp time (24 hour)
  return currentHour;
}

bool GetTime() {
  int ntpTime = getTimeNTP();
  if (ntpTime >= 0 && ntpTime < 7) {
    return true;
  } else if (ntpTime >= 7 && ntpTime < 18) {
    return false;
  } else if (ntpTime >= 18 && ntpTime <= 24) {
    return true;
  } else {
    return false;
  }
}

bool Bright(int _intensity, int _lightLimit) {
  if (_intensity > _lightLimit) {
    return true;
  } else {
    return false;
  }
}