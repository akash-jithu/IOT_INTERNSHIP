# Day 6 — OTA Firmware Update Documentation

## 1. Introduction

Day 6 focused on implementing **Over-The-Air (OTA) firmware updates** for the ESP32. OTA allows firmware to be uploaded to the ESP32 through a Wi-Fi network without requiring a physical USB connection for every update.

This is useful for IoT devices that may be deployed in locations where physically accessing the device is difficult.

---

## 2. Objectives

The main objectives of Day 6 were:

* Configure OTA firmware updates on the ESP32.
* Connect the ESP32 to Wi-Fi.
* Configure an OTA device hostname.
* Enable OTA password protection.
* Implement OTA event callbacks.
* Monitor OTA progress through the Serial Monitor.
* Handle OTA errors.
* Use an OTA-compatible partition scheme.
* Understand basic OTA security requirements.

---

## 3. Development Environment

| Component         | Configuration           |
| ----------------- | ----------------------- |
| Development Board | ESP32 Dev Module        |
| IDE               | Arduino IDE 2.3.10      |
| Framework         | Arduino ESP32 Core      |
| Wi-Fi Library     | `WiFi.h`                |
| OTA Library       | `ArduinoOTA.h`          |
| Partition Scheme  | Minimal SPIFFS with OTA |
| Serial Baud Rate  | 115200                  |

---

## 4. OTA Concept

Normally, firmware is uploaded to an ESP32 using a USB cable.

With OTA, the process becomes:

```text
Computer
   ↓
Wi-Fi Network
   ↓
ESP32
   ↓
Receive Firmware
   ↓
Restart
   ↓
Run New Firmware
```

This eliminates the need to connect the USB cable every time a firmware update is required.

---

## 5. Wi-Fi Connection

Before starting OTA, the ESP32 must establish a Wi-Fi connection.

The firmware waits until the ESP32 successfully connects to the configured network.

After connection, the IP address is displayed through the Serial Monitor.

Example:

```text
WiFi connected!
IP Address: 10.56.231.229
```

The IP address is required for network communication between the development computer and the ESP32.

---

## 6. OTA Configuration

The OTA service was configured with a unique hostname:

```text
Nexforz-ESP32
```

This allows the ESP32 to be identified as a network device during OTA operation.

Password protection was also enabled to prevent unauthorized firmware updates.

The OTA configuration includes:

* Hostname
* Password
* Start callback
* Progress callback
* End callback
* Error callback

---

## 7. OTA Event Callbacks

Callbacks are used to monitor the OTA update process.

### OTA Start

Triggered when an OTA update begins.

```text
OTA update started...
```

### OTA Progress

Displays the percentage of firmware transferred.

```text
OTA Progress: 25%
OTA Progress: 50%
OTA Progress: 75%
```

### OTA End

Triggered after the firmware transfer is completed.

```text
OTA update finished!
```

### OTA Error

Reports errors that occur during the update process.

The implemented error handling covers:

* Authentication failure
* OTA begin failure
* Connection failure
* Firmware receive failure
* OTA completion failure

---

## 8. OTA-Compatible Partition Scheme

An OTA-compatible partition scheme was selected for the ESP32:

```text
Minimal SPIFFS
1.9 MB APP with OTA
128 KB SPIFFS
```

The OTA partition configuration provides the required application space for firmware updates.

---

## 9. Program Working

The firmware follows this sequence:

```text
Start ESP32
    ↓
Initialize Serial Monitor
    ↓
Connect to Wi-Fi
    ↓
Display IP Address
    ↓
Configure OTA Hostname
    ↓
Configure OTA Password
    ↓
Register OTA Callbacks
    ↓
Start ArduinoOTA
    ↓
OTA Ready
    ↓
Wait for Firmware Update
    ↓
Handle OTA Requests
```

The OTA service is continuously handled during normal program execution.

---

## 10. OTA-Ready Verification

After the firmware was uploaded through USB, the ESP32 successfully connected to Wi-Fi and initialized the OTA service.

Observed output:

```text
Starting ESP32 OTA...
WiFi connected!
IP Address: 10.56.231.229
OTA ready!

Firmware running- OTA version 2
```

The repeated firmware message confirmed that the ESP32 continued running normally while waiting for an OTA update.

---

## 11. OTA Upload Test

The Arduino IDE detected the ESP32 as a network device and an OTA upload was attempted.

The OTA-ready firmware itself was successfully verified.

However, the complete wireless firmware transfer was not successfully completed because the network connection to the detected device could not be established.

Therefore, the final OTA transfer remains **pending verification**.

---

## 12. OTA Security

OTA introduces a network-based firmware update mechanism, so security is important.

Password protection was enabled for the development test.

For production deployment, additional security measures should be considered:

* Strong OTA authentication
* Firmware integrity verification
* Signed firmware
* Secure credential storage
* Network access control
* Restricted access to the OTA service

---

## 13. Deep Sleep Consideration

Deep sleep was discussed as a future power-saving feature.

OTA requires the ESP32 to remain awake and connected to the network during the update window.

A possible future workflow is:

```text
Wake Up
   ↓
Connect to Wi-Fi
   ↓
Check for OTA Update
   ↓
Read Sensors
   ↓
Send Data
   ↓
Enter Deep Sleep
   ↓
Wake Again
```

Deep sleep was not included in the current OTA test.

---
## 15. Learning Outcomes

By completing Day 6, the following concepts were learned:

* Working principle of OTA firmware updates.
* ESP32 OTA configuration using `ArduinoOTA`.
* Wi-Fi-based firmware deployment.
* OTA hostname configuration.
* OTA password protection.
* OTA event callbacks.
* OTA progress monitoring.
* OTA error handling.
* OTA-compatible partition configuration.
* Basic OTA security considerations.
* Relationship between OTA and future low-power operation.

---

## 16. Result

The ESP32 was successfully configured to support **Over-The-Air firmware updates**. Wi-Fi connectivity, OTA initialization, hostname configuration, password protection, callbacks, error handling, and the OTA-compatible partition scheme were successfully implemented and verified.

The ESP32 successfully entered the **OTA-ready state**. The complete wireless firmware transfer could not be verified because of the network connection issue during the OTA upload attempt.

---

## 17. Conclusion

Day 6 demonstrated the basic implementation of OTA firmware updating for the ESP32. The device can connect to Wi-Fi and remain ready to receive firmware updates without requiring a physical USB connection.

The OTA framework is now prepared for future integration with the Wi-Fi Edge Node system, while successful end-to-end wireless firmware transfer remains the next verification step.
