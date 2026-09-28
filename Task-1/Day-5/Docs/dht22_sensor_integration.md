# Day 5 — DHT22 Sensor Integration

## 1. Introduction

Day 5 focused on connecting a **DHT22 temperature and humidity sensor** to the ESP32 and developing a reliable sensor-reading system.

The implementation includes sensor initialization, temperature and humidity measurement, invalid-data detection, retry handling, and median filtering.

---

## 2. Objectives

The main objectives of Day 5 are:

* Connect the DHT22 sensor to the ESP32.
* Read temperature and humidity.
* Detect invalid sensor readings.
* Implement a retry mechanism.
* Reject invalid sensor samples.
* Store the latest three valid readings.
* Apply median filtering.
* Test sensor failure handling.

---

## 3. Hardware Used

* ESP32 Dev Module
* DHT22 3-pin sensor module
* Jumper wires
* USB cable

---

## 4. DHT22 Wiring

The DHT22 sensor was connected as follows:

| DHT22 Pin | ESP32  |
| --------- | ------ |
| `-`       | GND    |
| `OUT`     | GPIO 4 |
| `+`       | 3.3V   |

The DHT22 module used for this task already includes the required pull-up resistor.

---

## 5. Software Configuration

The DHT22 is configured using:

```cpp
#define DHT_PIN 4
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);
```

The **Adafruit DHT library** is used for communication with the sensor.

The sensor is initialized using:

```cpp
dht.begin();
```

---

## 6. Sensor Data Structure

A `SensorBundle` structure is used to organize the sensor readings and their validity status.

```cpp
struct SensorBundle {

  float temperature;
  float humidity;

  bool temperatureValid;
  bool humidityValid;
};
```

The structure stores:

* Temperature value
* Humidity value
* Temperature validity
* Humidity validity

This makes it easier to process sensor data safely.

---

## 7. Reading Temperature and Humidity

The DHT22 readings are obtained using:

```cpp
float humidity = dht.readHumidity();
float temperature = dht.readTemperature();
```

The firmware checks whether the returned values are valid.

The `isnan()` function is used to detect invalid readings:

```cpp
if (!isnan(humidity) && !isnan(temperature))
```

If both values are valid, they are stored in the `SensorBundle`.

---

## 8. Retry Mechanism

DHT22 readings can occasionally fail. To handle this, the firmware attempts to read the sensor up to **three times**.

```text
Attempt 1
   ↓
Failed?
   ↓
Attempt 2
   ↓
Failed?
   ↓
Attempt 3
   ↓
Failed?
   ↓
Mark sensor data invalid
```

A short delay is provided between failed attempts.

Example output:

```text
DHT22 read failed - attempt 1/3
DHT22 read failed - attempt 2/3
DHT22 read failed - attempt 3/3
DHT22 read failed after 3 attempts.
```

If any attempt succeeds, the valid reading is returned immediately.

---

## 9. Invalid Data Handling

If all three attempts fail, the sensor data remains invalid.

The firmware reports:

```text
Sensor data invalid.
Skipping this sample.
```

Invalid readings are not added to the filtering system.

This prevents incorrect sensor values from being processed or transmitted later.

---

## 10. Sensor Reading Interval

The DHT22 requires sufficient time between consecutive readings.

The firmware uses:

```cpp
delay(2000);
```

This provides a **2-second interval** between sensor-reading cycles.

The sequence is:

```text
Wait 2 seconds
     ↓
Read DHT22
     ↓
Validate data
     ↓
Process valid data
     ↓
Wait 2 seconds
     ↓
Repeat
```

---

## 11. Valid Sample Storage

The firmware stores the latest three valid temperature and humidity readings:

```cpp
float temperatureSamples[3];
float humiditySamples[3];
```

Only valid readings are added to these arrays.

When three samples are available, the oldest sample is removed and the newest sample is added.

Example:

```text
Sample 1 → Sample 2 → Sample 3
                    ↓
              New sample
                    ↓
Sample 2 → Sample 3 → New sample
```

---

## 12. Median Filtering

A median filter is used to reduce the effect of sudden measurement spikes.

The firmware calculates the median of three values using:

```cpp
float medianOfThree(float a, float b, float c)
```

For example:

```text
Temperature samples:

30.2
31.5
30.4

Sorted:

30.2
30.4
31.5

Median = 30.4 °C
```

The same process is applied to humidity readings.

Before three valid samples are available, the firmware displays:

```text
Median filter: Waiting for 3 samples
```

After three samples are available:

```text
Median filter: ACTIVE
```

---

## 13. Program Working

The complete process is:

```text
Start
  ↓
Initialize Serial Communication
  ↓
Initialize DHT22
  ↓
Wait 2 Seconds
  ↓
Read Temperature & Humidity
  ↓
Check Data Validity
  ↓
 ┌───────────────┐
 │ Valid Reading │
 └───────┬───────┘
         ↓
   Store Sample
         ↓
  Median Filtering
         ↓
 Display Result

If Reading Fails
         ↓
 Retry up to 3 Times
         ↓
 If All Fail
         ↓
 Reject Sample
         ↓
 Continue Running
```

---

## 14. Successful Reading Test

The sensor was tested with a working DATA connection.

Example output:

```text
DHT22 read successful on attempt 1

----- Sensor Reading -----
Temperature: 30.00 °C
Humidity: 79.60 %
Median filter: Waiting for 3 samples
Temperature Valid: YES
Humidity Valid: YES
```

After enough valid readings were collected, the median filter became active.

Example:

```text
----- Sensor Reading -----
Temperature: 30.50 °C
Humidity: 77.90 %
Median filter: ACTIVE
Temperature Valid: YES
Humidity Valid: YES
```

---

## 15. Sensor Failure Test

The DATA connection was disconnected to test the error-handling mechanism.

The ESP32 produced:

```text
DHT22 read failed - attempt 1/3
DHT22 read failed - attempt 2/3
DHT22 read failed - attempt 3/3
DHT22 read failed after 3 attempts.
Sensor data invalid.
Skipping this sample.
```

After the sensor connection was restored, valid readings were successfully obtained again.

The ESP32 continued operating without crashing or resetting.

---

## 16. Observations

The following were successfully verified:

* DHT22 initialization.
* Temperature measurement.
* Humidity measurement.
* Invalid-value detection.
* Three-attempt retry mechanism.
* Invalid sample rejection.
* Storage of valid readings.
* Three-sample median filtering.
* Sensor failure detection.
* Continued operation after sensor failure.

---

## 17. Result

The ESP32 successfully reads temperature and humidity from the DHT22 sensor.

The firmware can:

* Detect invalid readings.
* Retry failed readings up to three times.
* Reject invalid sensor data.
* Store valid readings.
* Apply a three-sample median filter.
* Continue operating when the sensor temporarily fails.

---

## 18. Learning Outcomes

The following concepts were learned:

* DHT22 sensor interfacing.
* Temperature and humidity measurement.
* Sensor data validation.
* `NaN` detection.
* Retry mechanisms.
* Structured sensor data using `struct`.
* Invalid-data handling.
* Sample storage.
* Median filtering.
* Basic sensor fault handling.

---

## 19. Conclusion

Day 5 successfully implemented a reliable **DHT22 sensor layer** for the ESP32.

The system can obtain temperature and humidity readings, detect sensor failures, retry unsuccessful readings, reject invalid data, and reduce measurement spikes using a three-sample median filter.

This provides the sensor foundation required for the upcoming **MQTT and cloud telemetry stages** of the Wi-Fi Edge Node project.

**Day 5 — Completed ✅**
