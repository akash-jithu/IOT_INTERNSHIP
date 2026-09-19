# Task 1 — Day 4
## NTP Time Synchronization

Day 4 focused on synchronizing the ESP32 time using **NTP (Network Time Protocol)** after connecting to Wi-Fi.

Accurate timestamps are required for sensor data, MQTT messages, and cloud dashboards.

### Objectives

- Connect the ESP32 to Wi-Fi
- Synchronize time using NTP
- Configure Indian Standard Time (IST)
- Verify successful time synchronization
- Display the current local time
- Generate ISO-8601 timestamps
- Prepare accurate timestamps for future IoT data

### Key Configuration

| Parameter | Value |
|---|---|
| Board | ESP32 Dev Module |
| Time Source | NTP |
| NTP Servers | pool.ntp.org, time.nist.gov |
| Time Zone | IST |
| UTC Offset | +05:30 |
| GMT Offset | 19800 seconds |
| Serial Baud Rate | 115200 |

### NTP Synchronization

The ESP32 connects to Wi-Fi and then starts NTP synchronization using:

```cpp
configTime()
