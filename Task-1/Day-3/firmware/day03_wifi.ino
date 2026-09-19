#include <WiFi.h>
#include "secrets.h"

// -----------------------------
// Wi-Fi Configuration
// -----------------------------

const unsigned long CONNECTION_TIMEOUT = 15000;   // 15 seconds
const unsigned long HEALTH_CHECK_INTERVAL = 5000;

const unsigned long INITIAL_BACKOFF = 1000;       // 1 second
const unsigned long MAX_BACKOFF = 30000;          // 30 seconds

unsigned long lastHealthCheck = 0;
unsigned long currentBackoff = INITIAL_BACKOFF;


// -----------------------------
// Connect to Wi-Fi
// -----------------------------

bool connectToWiFi() {

  Serial.println();
  Serial.println("Connecting to Wi-Fi...");

  Serial.print("SSID: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startTime < CONNECTION_TIMEOUT) {

    delay(250);
    Serial.print(".");
  }

  Serial.println();

  // -----------------------------
  // Connection successful
  // -----------------------------

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("Wi-Fi connected!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    Serial.print("Wi-Fi Channel: ");
    Serial.println(WiFi.channel());

    // Reset backoff after successful connection
    currentBackoff = INITIAL_BACKOFF;

    return true;
  }

  // -----------------------------
  // Connection failed
  // -----------------------------

  Serial.println("Wi-Fi connection failed.");

  Serial.print("Next retry in ");
  Serial.print(currentBackoff);
  Serial.println(" ms.");

  return false;
}


// -----------------------------
// Setup
// -----------------------------

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("NEXFORZ WIFI EDGE NODE");
  Serial.println("Day 03 - Wi-Fi Test");
  Serial.println("==============================");

  Serial.println("Mode: Wi-Fi Station (STA)");

  connectToWiFi();
}


// -----------------------------
// Main Loop
// -----------------------------

void loop() {

  unsigned long currentTime = millis();


  // -----------------------------
  // Connected
  // -----------------------------

  if (WiFi.status() == WL_CONNECTED) {

    if (currentTime - lastHealthCheck >= HEALTH_CHECK_INTERVAL) {

      lastHealthCheck = currentTime;

      Serial.println();
      Serial.println("Wi-Fi Health Check");

      Serial.println("Status: CONNECTED");

      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());

      Serial.print("RSSI: ");
      Serial.print(WiFi.RSSI());
      Serial.println(" dBm");

      Serial.print("Channel: ");
      Serial.println(WiFi.channel());
    }
  }


  // -----------------------------
  // Disconnected
  // -----------------------------

  else {

    Serial.println();
    Serial.println("Wi-Fi status: DISCONNECTED");

    Serial.print("Retrying in ");
    Serial.print(currentBackoff);
    Serial.println(" ms...");

    delay(currentBackoff);

    if (connectToWiFi()) {

      // Connection successful
      currentBackoff = INITIAL_BACKOFF;

    } else {

      // Double the retry delay
      currentBackoff = currentBackoff * 2;

      // Limit to 30 seconds
      if (currentBackoff > MAX_BACKOFF) {
        currentBackoff = MAX_BACKOFF;
      }
    }
  }

  delay(100);
}
