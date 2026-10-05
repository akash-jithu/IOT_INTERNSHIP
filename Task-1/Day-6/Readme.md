# Task 1 — Day 6
## OTA Firmware Update

Day 6 focused on implementing **Over-The-Air (OTA) firmware updates** for the ESP32. OTA allows firmware to be updated wirelessly through Wi-Fi without physically connecting the ESP32 using USB.

### Objectives

- Configure OTA firmware updates.
- Connect the ESP32 to Wi-Fi.
- Configure an OTA hostname.
- Enable OTA password protection.
- Monitor OTA progress and errors.
- Use an OTA-compatible partition scheme.

### Work Done

- Configured Wi-Fi connectivity on the ESP32.
- Implemented OTA using `ArduinoOTA`.
- Configured the hostname as `Nexforz-ESP32`.
- Added OTA password protection.
- Implemented OTA start, progress, completion, and error callbacks.
- Selected an OTA-compatible partition scheme.
- Uploaded and tested the firmware through USB.
- Verified that the ESP32 enters the OTA-ready state.
- Attempted firmware upload through the network using the Arduino IDE.

### OTA Working

```text
ESP32
  ↓
Connect to Wi-Fi
  ↓
Initialize OTA
  ↓
OTA Ready
  ↓
Receive Firmware
  ↓
Restart
  ↓
Run Updated Firmware
````

### Verification

The ESP32 successfully connected to Wi-Fi and displayed its IP address. The OTA service was initialized successfully and the device remained ready to receive firmware updates.

```text
WiFi connected!
IP Address: 10.56.231.229
OTA ready!
```

The network OTA upload was attempted, but the complete wireless transfer requires further verification due to a network connection issue.

### Security

Basic OTA password protection was enabled. For future deployment, firmware authentication, integrity verification, and secure network access should also be considered.

### Result

The ESP32 was successfully configured and tested for **OTA firmware updates**, providing the foundation for wireless firmware deployment in the IoT edge node.

**Day 6 — Completed ⚠️**


