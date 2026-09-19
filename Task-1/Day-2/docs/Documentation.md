# TASK 1 — DAY 2

## ESP32 Build Environment Setup and Verification

### 1. Introduction

Day 2 focused on setting up and verifying the development environment for the **Nexforz Agritech WiFi Edge Node** project. The ESP32 was configured using Arduino IDE and tested to ensure that the board, software environment, memory, and communication were working correctly.

An environment-check program was developed to retrieve important ESP32 hardware and software information and monitor the available memory during runtime.

---

## 2. Objectives

The main objectives were:

* Configure Arduino IDE for ESP32 development.
* Verify the ESP32 Arduino Core.
* Configure the ESP32 Dev Module.
* Select an OTA-capable partition scheme for future firmware updates.
* Verify the required libraries for upcoming IoT tasks.
* Develop and upload an ESP32 environment-check program.
* Verify hardware and software information.
* Monitor free heap memory during runtime.

---

## 3. Development Environment Setup

The **Arduino IDE** was used for ESP32 programming.

The **ESP32 Arduino Core** was installed and verified through the Arduino IDE Boards Manager.

The following configuration was used:

| Parameter               | Configuration    |
| ----------------------- | ---------------- |
| Board                   | ESP32 Dev Module |
| Development Environment | Arduino IDE      |
| Communication           | USB / Serial     |
| Serial Baud Rate        | 115200           |

The ESP32 was connected to the computer using a USB cable, and the corresponding COM port was selected.

---

## 4. Partition Scheme

An **OTA-capable partition scheme** was selected during the ESP32 configuration.

This provides the required partition arrangement for future **Over-The-Air (OTA) firmware updates**.

OTA will allow firmware to be updated through a network connection without physically connecting the ESP32 to the computer.

---

## 5. Required Libraries

The following libraries were verified for future IoT development:

| Library            | Purpose                          |
| ------------------ | -------------------------------- |
| DHT Sensor Library | Temperature and humidity sensing |
| PubSubClient       | MQTT communication               |
| ArduinoJson        | JSON data handling               |

These libraries will be used in later stages for sensor data collection and cloud/MQTT communication.

---

## 6. Environment Check Program

A basic environment-check program was developed and uploaded to the ESP32.

The program checks:

* ESP32 chip model
* Chip revision
* CPU frequency
* Flash memory size
* Free heap memory
* Arduino ESP32 SDK version

It also continuously monitors the available free heap memory.

### Program

```cpp
#include <Arduino.h>

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("NEXFORZ WIFI EDGE NODE");
  Serial.println("Day 02 - Environment Check");
  Serial.println("==============================");

  Serial.print("ESP32 Chip Model: ");
  Serial.println(ESP.getChipModel());

  Serial.print("Chip Revision: ");
  Serial.println(ESP.getChipRevision());

  Serial.print("CPU Frequency: ");
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");

  Serial.print("Flash Size: ");
  Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
  Serial.println(" MB");

  Serial.print("Free Heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");

  Serial.print("Arduino ESP32 SDK Version: ");
  Serial.println(ESP.getSdkVersion());

  Serial.println();
  Serial.println("Environment check complete.");
}

void loop() {

  delay(5000);

  Serial.print("Free Heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
}
```

---

## 7. Working of the Program

### Serial Initialization

```cpp
Serial.begin(115200);
```

Initializes serial communication at **115200 baud**, allowing the ESP32 to communicate with the Serial Monitor.

### Chip Information

```cpp
ESP.getChipModel()
ESP.getChipRevision()
```

These functions retrieve the ESP32 chip model and hardware revision.

### CPU Frequency

```cpp
ESP.getCpuFreqMHz()
```

Returns the CPU frequency in MHz.

### Flash Size

```cpp
ESP.getFlashChipSize()
```

Returns the flash memory size. The value is converted from bytes to megabytes.

### Free Heap

```cpp
ESP.getFreeHeap()
```

Returns the amount of currently available heap memory in bytes.

### SDK Version

```cpp
ESP.getSdkVersion()
```

Returns the ESP32 SDK version being used.

### Continuous Monitoring

The `loop()` function waits for **5 seconds** and then prints the current free heap. This allows memory usage to be monitored continuously while the ESP32 is running.

---

## 8. Compilation and Upload

The program was compiled using Arduino IDE and successfully uploaded to the ESP32.

Successful compilation and upload confirmed:

* Correct board selection.
* Correct ESP32 development environment.
* Successful USB/serial communication.
* Successful firmware transfer.
* Correct execution of ESP32-specific functions.

---

## 9. Serial Monitor Testing

The Serial Monitor was opened at **115200 baud** after uploading the program.

The ESP32 successfully displayed the environment information and continued monitoring its free heap.

The observed output repeatedly showed:

```text
Free Heap: 331072 bytes
```

The repeated output confirmed that the `loop()` function was executing continuously and that the ESP32 was operating correctly during the test.

---

## 10. Result

The following were successfully verified:

* Arduino IDE ESP32 environment
* ESP32 Dev Module configuration
* ESP32 Arduino Core
* OTA-capable partition configuration
* Required IoT libraries
* ESP32 hardware information
* CPU and flash information
* Free heap monitoring
* SDK version retrieval
* Firmware compilation
* Firmware upload
* Serial communication
* Continuous runtime execution

The observed free heap during testing was approximately **331072 bytes**.

---

## 11. Learning Outcomes

Through Day 2, the following concepts were understood:

* ESP32 development environment setup.
* Board and COM port configuration.
* ESP32 Arduino Core.
* OTA-capable partition schemes.
* ESP32 hardware information APIs.
* Flash and heap memory.
* Serial communication and baud rate.
* Firmware compilation and upload.
* Runtime memory monitoring.

---

## 12. Conclusion

Day 2 successfully established and verified the ESP32 development environment for the Nexforz Agritech WiFi Edge Node project.

The ESP32 was configured, programmed, and tested using an environment-check program. Hardware information and runtime memory were successfully monitored through the Serial Monitor.

The verified environment provides a reliable foundation for the upcoming **Wi-Fi connectivity, sensor interfacing, MQTT communication, and IoT telemetry** tasks.

**Status: Day 2 — Completed ✅**
