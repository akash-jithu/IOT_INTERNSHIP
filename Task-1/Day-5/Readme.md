# Task 1 — Day 5
## DHT22 Sensor Integration

Day 5 focused on connecting the **DHT22 temperature and humidity sensor** to the ESP32 and implementing reliable sensor reading, error handling, and median filtering.

### Objectives

- Connect the DHT22 sensor to the ESP32
- Read temperature and humidity
- Detect invalid sensor readings
- Implement a retry mechanism
- Reject invalid sensor samples
- Store the last 3 valid readings
- Apply median filtering
- Test sensor failure handling

### Hardware Used

- ESP32 Dev Module
- DHT22 3-pin sensor module
- Jumper wires

### Wiring

| DHT22 Pin | ESP32 |
|---|---|
| `-` | GND |
| `OUT` | GPIO 4 |
| `+` | 3.3V |

The DHT22 module already has the required pull-up resistor, so an additional resistor was not required for this setup.

### Software Implementation

The firmware includes:

- DHT22 initialization using the **Adafruit DHT library**
- Temperature reading
- Humidity reading
- `NaN`/invalid-value detection
- Up to **3 reading attempts**
- `SensorBundle` structure for sensor data
- Temperature and humidity validity flags
- Storage of the last 3 valid readings
- 3-sample median filtering
- Invalid sample rejection

### Successful Reading

Example:

```text
DHT22 read successful on attempt 1

----- Sensor Reading -----
Temperature: 30.00 °C
Humidity: 79.60 %
Median filter: Waiting for 3 samples
Temperature Valid: YES
Humidity Valid: YES
````

After three valid samples:

```text
----- Sensor Reading -----
Temperature: 30.50 °C
Humidity: 77.90 %
Median filter: ACTIVE
Temperature Valid: YES
Humidity Valid: YES
```

### Sensor Failure Test

The DATA connection was disconnected to test the error-handling mechanism.

The ESP32 correctly detected the failure and attempted three readings:

```text
DHT22 read failed - attempt 1/3
DHT22 read failed - attempt 2/3
DHT22 read failed - attempt 3/3
DHT22 read failed after 3 attempts.
Sensor data invalid.
Skipping this sample.
```

The ESP32 continued running without crashing or resetting.

### Median Filtering

The firmware stores the latest **3 valid temperature and humidity readings**.

The median value is calculated to reduce the effect of sudden measurement spikes.

```text
Sample 1
Sample 2
Sample 3
    ↓
Median Filter
    ↓
Filtered Temperature & Humidity
```

### Testing

The following were successfully verified:

* DHT22 initialization
* Temperature reading
* Humidity reading
* Sensor validity checking
* Retry mechanism
* Invalid reading detection
* Invalid sample rejection
* Storage of valid samples
* Median filtering
* Sensor failure handling

### Result

The ESP32 successfully reads temperature and humidity from the DHT22 sensor. The firmware can detect failed readings, retry up to three times, reject invalid data, and apply a 3-sample median filter to valid measurements.

**Day 5 — Completed ✅**
