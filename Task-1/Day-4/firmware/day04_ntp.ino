#include <WiFi.h>
#include <time.h>

// WiFi details
const char* ssid = "Ghost S24 FE";
const char* password = "Akash123";

// India Standard Time: UTC +5:30
const long GMT_OFFSET_SEC = 19800;
const int DAYLIGHT_OFFSET_SEC = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  // Start NTP synchronization
  Serial.println("Starting NTP time synchronization...");

  configTime(
    GMT_OFFSET_SEC,
    DAYLIGHT_OFFSET_SEC,
    "pool.ntp.org",
    "time.nist.gov"
  );

  struct tm timeinfo;

  if (getLocalTime(&timeinfo)) {
    Serial.println();
    Serial.println("NTP synchronization successful!");
  } else {
    Serial.println();
    Serial.println("NTP synchronization failed!");
  }
}

void loop() {

  struct tm timeinfo;

  if (getLocalTime(&timeinfo)) {

    // Normal local time
    char localTime[25];

    strftime(
      localTime,
      sizeof(localTime),
      "%Y-%m-%d %H:%M:%S",
      &timeinfo
    );

    Serial.println();
    Serial.println("Current Local Time:");
    Serial.println(localTime);

    // ISO-8601 timestamp
    char isoTimestamp[32];

    snprintf(
      isoTimestamp,
      sizeof(isoTimestamp),
      "%04d-%02d-%02dT%02d:%02d:%02d+05:30",
      timeinfo.tm_year + 1900,
      timeinfo.tm_mon + 1,
      timeinfo.tm_mday,
      timeinfo.tm_hour,
      timeinfo.tm_min,
      timeinfo.tm_sec
    );

    Serial.println("ISO-8601 Timestamp:");
    Serial.println(isoTimestamp);

  } else {
    Serial.println("Failed to obtain time");
  }

  delay(5000);
}
