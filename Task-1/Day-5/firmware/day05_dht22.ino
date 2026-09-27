#include <DHT.h>

// ----------------------------------------
// DHT22 Configuration
// ----------------------------------------

#define DHT_PIN 4
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);


// ----------------------------------------
// SensorBundle
// ----------------------------------------

struct SensorBundle {

  float temperature;
  float humidity;

  bool temperatureValid;
  bool humidityValid;
};


// ----------------------------------------
// Median filter storage
// ----------------------------------------

float temperatureSamples[3];
float humiditySamples[3];

int sampleCount = 0;


// ----------------------------------------
// Calculate median of 3 values
// ----------------------------------------

float medianOfThree(float a, float b, float c) {

  if ((a <= b && b <= c) || (c <= b && b <= a)) {
    return b;
  }

  if ((b <= a && a <= c) || (c <= a && a <= b)) {
    return a;
  }

  return c;
}


// ----------------------------------------
// Read DHT22 with retry
// ----------------------------------------

SensorBundle readSensor() {

  SensorBundle sensor;

  sensor.temperature = NAN;
  sensor.humidity = NAN;

  sensor.temperatureValid = false;
  sensor.humidityValid = false;


  // Try up to 3 times
  for (int attempt = 1; attempt <= 3; attempt++) {

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Check for valid readings
    if (!isnan(humidity) && !isnan(temperature)) {

      sensor.temperature = temperature;
      sensor.humidity = humidity;

      sensor.temperatureValid = true;
      sensor.humidityValid = true;

      Serial.print("DHT22 read successful on attempt ");
      Serial.println(attempt);

      return sensor;
    }

    Serial.print("DHT22 read failed - attempt ");
    Serial.print(attempt);
    Serial.println("/3");

    delay(200);
  }


  // All attempts failed
  Serial.println("DHT22 read failed after 3 attempts.");

  return sensor;
}


// ----------------------------------------
// Add valid sample to filter
// ----------------------------------------

void addSample(float temperature, float humidity) {

  if (sampleCount < 3) {

    temperatureSamples[sampleCount] = temperature;
    humiditySamples[sampleCount] = humidity;

    sampleCount++;

  } else {

    // Shift old samples
    temperatureSamples[0] = temperatureSamples[1];
    temperatureSamples[1] = temperatureSamples[2];
    temperatureSamples[2] = temperature;

    humiditySamples[0] = humiditySamples[1];
    humiditySamples[1] = humiditySamples[2];
    humiditySamples[2] = humidity;
  }
}


// ----------------------------------------
// Print filtered values
// ----------------------------------------

void printFilteredValues() {

  Serial.println();
  Serial.println("----- Sensor Reading -----");

  if (sampleCount < 3) {

    Serial.print("Temperature: ");
    Serial.print(temperatureSamples[sampleCount - 1], 2);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humiditySamples[sampleCount - 1], 2);
    Serial.println(" %");

    Serial.println("Median filter: Waiting for 3 samples");

  } else {

    float filteredTemperature = medianOfThree(
      temperatureSamples[0],
      temperatureSamples[1],
      temperatureSamples[2]
    );

    float filteredHumidity = medianOfThree(
      humiditySamples[0],
      humiditySamples[1],
      humiditySamples[2]
    );

    Serial.print("Temperature: ");
    Serial.print(filteredTemperature, 2);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(filteredHumidity, 2);
    Serial.println(" %");

    Serial.println("Median filter: ACTIVE");
  }

  Serial.println("Temperature Valid: YES");
  Serial.println("Humidity Valid: YES");
}


// ----------------------------------------
// Setup
// ----------------------------------------

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("NEXFORZ WIFI EDGE NODE");
  Serial.println("Day 05 - DHT22 Sensor");
  Serial.println("==============================");

  dht.begin();

  Serial.println("DHT22 initialized.");
}


// ----------------------------------------
// Main Loop
// ----------------------------------------

void loop() {

  // DHT22 requires at least 2 seconds
  // between readings
  delay(2000);


  // Read sensor
  SensorBundle sensor = readSensor();


  // Check validity
  if (!sensor.temperatureValid ||
      !sensor.humidityValid) {

    Serial.println("Sensor data invalid.");
    Serial.println("Skipping this sample.");

    return;
  }


  // Add only good readings
  addSample(
    sensor.temperature,
    sensor.humidity
  );


  // Print filtered result
  printFilteredValues();
}
