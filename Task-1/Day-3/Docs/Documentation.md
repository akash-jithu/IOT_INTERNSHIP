# TASK 1 — DAY 3
## Wi-Fi Station Mode & Connection Manager

### 1. Introduction

Day 3 focused on configuring the ESP32 as a **Wi-Fi Station (STA)** and implementing a reliable Wi-Fi connection manager for the Nexforz Agritech WiFi Edge Node.

The ESP32 was configured to connect to an existing Wi-Fi network, monitor the connection status, report network information, detect disconnections, and automatically recover the connection using retry and exponential backoff mechanisms.

---

### 2. Objectives

The main objectives of Day 3 were:

- Configure the ESP32 in Wi-Fi Station Mode.
- Connect the ESP32 to an existing Wi-Fi network.
- Keep Wi-Fi credentials separate from the main program.
- Implement a Wi-Fi connection timeout.
- Display the assigned IP address.
- Monitor Wi-Fi signal strength using RSSI.
- Display the connected Wi-Fi channel.
- Perform periodic Wi-Fi health checks.
- Detect Wi-Fi disconnection.
- Implement automatic reconnection.
- Implement exponential backoff.
- Test Wi-Fi connection recovery.

---

### 3. Development Environment

| Parameter | Configuration |
|---|---|
| Microcontroller | ESP32 |
| Development Board | ESP32 Dev Module |
| Development Environment | Arduino IDE |
| Wi-Fi Mode | Station (STA) |
| Serial Baud Rate | 115200 |
| Wi-Fi Library | WiFi.h |

The ESP32 was connected to the computer through USB and programmed using Arduino IDE.

---

### 4. Wi-Fi Station Mode

The ESP32 was configured to operate in **Station Mode**.

In Station Mode, the ESP32 connects to an existing Wi-Fi network instead of creating its own network.

The Wi-Fi mode is configured using:

```cpp
WiFi.mode(WIFI_STA);
````

The Wi-Fi connection is started using:

```cpp
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
```

The Wi-Fi credentials are kept separate from the main program to prevent sensitive network information from being directly included in the firmware logic.

The actual Wi-Fi credentials are not uploaded to the GitHub repository.

---

### 5. Wi-Fi Connection

A dedicated connection process was implemented to establish the Wi-Fi connection.

The connection process works as follows:

1. Configure the ESP32 in Station Mode.
2. Start the Wi-Fi connection.
3. Wait for the ESP32 to connect.
4. Check the Wi-Fi connection status.
5. Continue waiting until the connection succeeds or the timeout is reached.
6. Display the connection result.

The connection timeout is configured as:

```cpp
const unsigned long CONNECTION_TIMEOUT = 15000;
```

This allows a maximum of **15 seconds** for each connection attempt.

If the connection is successful, the ESP32 displays the network information.

If the connection fails, the ESP32 prepares for another connection attempt.

---

### 6. Connection Information

After successfully connecting to Wi-Fi, the ESP32 retrieves and displays important network information.

The following information is reported:

* IP address
* RSSI
* Wi-Fi channel

Example output:

```text
Wi-Fi connected!

IP Address: 10.56.231.229
RSSI: -24 dBm
Wi-Fi Channel: 1
```

#### RSSI

RSSI stands for **Received Signal Strength Indicator**.

It is reported in dBm and provides information about the strength of the received Wi-Fi signal.

During testing, RSSI values were observed approximately between:

```text
-14 dBm to -25 dBm
```

---

### 7. Wi-Fi Health Monitoring

The ESP32 performs periodic health checks to monitor the Wi-Fi connection during operation.

The health check interval is configured as:

```cpp
const unsigned long HEALTH_CHECK_INTERVAL = 5000;
```

Therefore, the connection is monitored every **5 seconds**.

Example output:

```text
Wi-Fi Health Check

Status: CONNECTED
IP Address: 10.56.231.229
RSSI: -14 dBm
Channel: 1
```

The health check provides continuous information about the current Wi-Fi connection.

---

### 8. Connection Status Detection

The Wi-Fi connection status is monitored using:

```cpp
WiFi.status()
```

When the status is:

```cpp
WL_CONNECTED
```

the ESP32 continues normal operation and performs periodic health checks.

If the status changes and the ESP32 is no longer connected, the program detects the disconnection and starts the reconnection process.

---

### 9. Automatic Reconnection

An automatic reconnection mechanism was implemented to allow the ESP32 to recover when the Wi-Fi connection is lost.

When a disconnection is detected, the ESP32 waits for a specified retry interval before attempting to connect again.

The initial retry delay is:

```cpp
const unsigned long INITIAL_BACKOFF = 1000;
```

The maximum retry delay is:

```cpp
const unsigned long MAX_BACKOFF = 30000;
```

This creates an exponential backoff sequence.

---

### 10. Exponential Backoff

After every unsuccessful connection attempt, the retry delay is doubled.

The delay is updated using:

```cpp
currentBackoff = currentBackoff * 2;
```

The retry delay is limited to a maximum of 30 seconds.

The retry sequence is:

```text
1 second
   ↓
2 seconds
   ↓
4 seconds
   ↓
8 seconds
   ↓
16 seconds
   ↓
30 seconds maximum
```

Exponential backoff prevents the ESP32 from repeatedly attempting to connect at very short intervals when the network is unavailable.

---

### 11. Backoff Reset

When the ESP32 successfully reconnects to the Wi-Fi network, the retry delay is reset to the initial value.

```cpp
currentBackoff = INITIAL_BACKOFF;
```

Therefore, after recovery, a future disconnection starts the retry process again from a 1-second delay.

---

### 12. Wi-Fi Disconnection and Recovery Test

The connection manager was tested by disabling the Wi-Fi hotspot while the ESP32 was connected.

The ESP32 detected that the Wi-Fi connection had been lost.

The system then entered the reconnection process and waited according to the configured backoff interval.

Example:

```text
Wi-Fi status: DISCONNECTED

Retrying in 2000 ms...
```

The ESP32 continued attempting to reconnect.

When the Wi-Fi hotspot became available again, the ESP32 successfully restored the connection.

Example:

```text
Wi-Fi connected!

IP Address: 10.56.231.229
RSSI: -24 dBm
Wi-Fi Channel: 1
```

This confirmed that the automatic Wi-Fi recovery mechanism was functioning correctly.

---

### 13. Program Working

The overall working of the Wi-Fi connection manager can be summarized as:

```text
Start
  ↓
Initialize Serial Communication
  ↓
Configure Wi-Fi Station Mode
  ↓
Attempt Wi-Fi Connection
  ↓
Connection Successful?
  ├── Yes
  │    ↓
  │  Display IP, RSSI and Channel
  │    ↓
  │  Perform Health Check
  │    ↓
  │  Monitor Wi-Fi Status
  │
  └── No
       ↓
     Wait for Backoff Delay
       ↓
     Retry Connection
       ↓
     Increase Backoff Delay
```

When a connection is lost:

```text
Wi-Fi Connected
      ↓
Connection Lost
      ↓
Detect Disconnected Status
      ↓
Wait for Retry Delay
      ↓
Attempt Reconnection
      ↓
Connection Successful?
   ├── Yes → Reset Backoff → Continue Monitoring
   │
   └── No → Increase Backoff → Retry Again
```

---

### 14. Important Configuration

| Parameter             |      Value | Purpose                                 |
| --------------------- | ---------: | --------------------------------------- |
| Connection Timeout    | 15 seconds | Maximum time for one connection attempt |
| Health Check Interval |  5 seconds | Periodic Wi-Fi monitoring               |
| Initial Backoff       |   1 second | First retry delay                       |
| Maximum Backoff       | 30 seconds | Maximum retry delay                     |
| Serial Baud Rate      |     115200 | Serial communication                    |

---

### 15. Testing and Observations

The following functions were successfully tested:

| Test                    | Result     |
| ----------------------- | ---------- |
| ESP32 Station Mode      | Successful |
| Wi-Fi Connection        | Successful |
| IP Address Reporting    | Successful |
| RSSI Reporting          | Successful |
| Wi-Fi Channel Reporting | Successful |
| Periodic Health Check   | Successful |
| Disconnection Detection | Successful |
| Automatic Retry         | Successful |
| Exponential Backoff     | Successful |
| Wi-Fi Recovery          | Successful |

Observed network information included:

```text
IP Address: 10.56.231.229
RSSI: Approximately -14 to -25 dBm
Wi-Fi Channel: 1
```

---

### 16. Learning Outcomes

Through Day 3, the following concepts were learned and implemented:

* ESP32 Wi-Fi Station Mode
* Wi-Fi connection management
* Wi-Fi status monitoring
* IP address retrieval
* RSSI monitoring
* Wi-Fi channel detection
* Connection timeout handling
* Automatic reconnection
* Exponential backoff
* Network recovery
* Periodic health monitoring
* Separation of Wi-Fi credentials

---

### 17. Result

The ESP32 was successfully configured as a Wi-Fi Station and connected to the configured wireless network.

The connection manager successfully:

* Established the Wi-Fi connection.
* Reported the IP address.
* Reported Wi-Fi signal strength.
* Reported the Wi-Fi channel.
* Performed periodic health checks.
* Detected Wi-Fi disconnections.
* Retried failed connections automatically.
* Used exponential backoff during retries.
* Recovered the Wi-Fi connection when the network became available.

---

### 18. Conclusion

Day 3 successfully established a reliable Wi-Fi connectivity layer for the Nexforz Agritech WiFi Edge Node.

The ESP32 can now connect to a Wi-Fi network, monitor its connection status, detect network failures, retry using exponential backoff, and automatically recover from Wi-Fi disconnections.

**Day 3 — Wi-Fi Station Mode & Connection Manager: Completed ✅**

