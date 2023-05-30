#include <NTPClient.h>
#include <WiFiUdp.h>

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setupNTP() {
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
  if (ntpTime > 18 and ntpTime < 7) {
    return true;
  } else {
    return false;
  }
}