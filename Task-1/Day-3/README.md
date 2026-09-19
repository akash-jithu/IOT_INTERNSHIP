# Task 1 — Day 3
## Wi-Fi Station Mode & Connection Manager

Day 3 focused on configuring the ESP32 as a Wi-Fi Station and implementing a reliable Wi-Fi connection manager.

### Objectives

- Configure ESP32 in Wi-Fi Station Mode
- Connect to a Wi-Fi network
- Monitor Wi-Fi connection status
- Display IP address, RSSI, and channel
- Perform periodic health checks
- Detect disconnection
- Implement automatic reconnection
- Implement exponential backoff
- Test Wi-Fi recovery

### Key Configuration

| Parameter | Value |
|---|---:|
| Board | ESP32 Dev Module |
| Wi-Fi Mode | Station (STA) |
| Connection Timeout | 15 seconds |
| Health Check Interval | 5 seconds |
| Initial Backoff | 1 second |
| Maximum Backoff | 30 seconds |
| Serial Baud Rate | 115200 |

### Wi-Fi Monitoring

After connecting, the ESP32 reports:

- IP address
- RSSI
- Wi-Fi channel
- Connection status

Example:

```text
Wi-Fi connected!

IP Address: 10.56.231.229
RSSI: -24 dBm
Wi-Fi Channel: 1
Connection Recovery

When Wi-Fi is disconnected, the ESP32 automatically attempts to reconnect.

The retry delay uses exponential backoff:

1s → 2s → 4s → 8s → 16s → 30s maximum

After successful reconnection, the backoff delay is reset to 1 second.

Testing

The following were successfully tested:

Wi-Fi Station Mode
Wi-Fi connection
IP address reporting
RSSI reporting
Channel reporting
Periodic health checks
Disconnection detection
Automatic retry
Exponential backoff
Wi-Fi recovery
Result

The ESP32 successfully connects to Wi-Fi, monitors connection health, detects network loss, retries using exponential backoff, and automatically recovers when the network becomes available.
