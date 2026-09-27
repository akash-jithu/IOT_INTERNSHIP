#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "NAME";
const char* password = "PASSWORD";

const char* otaPassword = "NexforzOTA2026";

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("Starting ESP32 OTA...");

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ArduinoOTA.setHostname("Nexforz-ESP32");

  ArduinoOTA.setPassword(otaPassword);

  ArduinoOTA
    .onStart([]() {
      Serial.println("OTA update started...");
    })
    .onEnd([]() {
      Serial.println("\nOTA update finished!");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf(
        "OTA Progress: %u%%\r",
        (progress * 100) / total
      );
    })
    .onError([](ota_error_t error) {

      Serial.printf(
        "\nOTA Error[%u]: ",
        error
      );

      if (error == OTA_AUTH_ERROR)
        Serial.println("Authentication Failed");

      else if (error == OTA_BEGIN_ERROR)
        Serial.println("Begin Failed");

      else if (error == OTA_CONNECT_ERROR)
        Serial.println("Connection Failed");

      else if (error == OTA_RECEIVE_ERROR)
        Serial.println("Receive Failed");

      else if (error == OTA_END_ERROR)
        Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("OTA ready!");
}

void loop() {

  ArduinoOTA.handle();

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint >= 5000) {

    lastPrint = millis();

    Serial.println();
    Serial.println("Firmware running- OTA version 2");
  }
}
