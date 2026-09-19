# Task 1 — Day 2: ESP32 Build Environment Setup and Verification

## Objective

Verify and configure the ESP32 development environment for the Nexforz Agritech WiFi Edge Node project.

## Work Completed

- Verified Arduino IDE setup for ESP32 development.
- Configured the ESP32 Dev Module.
- Verified ESP32 Arduino Core.
- Selected an OTA-capable partition scheme.
- Verified the required libraries for future IoT development.
- Created and tested an ESP32 environment-check program.
- Verified ESP32 chip information.
- Verified CPU frequency and flash memory information.
- Monitored free heap memory.
- Verified the Arduino ESP32 SDK version.
- Successfully compiled and uploaded the program.
- Verified runtime output using the Serial Monitor.

## Environment Check

The ESP32 environment-check program retrieves:

- ESP32 chip model
- Chip revision
- CPU frequency
- Flash size
- Free heap memory
- Arduino ESP32 SDK version

The program also monitors free heap memory continuously during runtime.

## Runtime Result

The Serial Monitor successfully displayed the environment information and repeatedly reported the available free heap memory.

Observed free heap:

```text
331072 bytes
