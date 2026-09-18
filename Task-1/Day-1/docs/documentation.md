# TASK 1 — DAY 1

## ESP32 Development Environment Setup and Basic Testing

### 1. Introduction

The first day of the IoT internship focused on setting up the development environment for ESP32-based IoT development.

The ESP32 development board was connected to a computer and configured using the Arduino IDE. The required ESP32 board support was installed, and a basic LED blinking program was uploaded to verify the operation of the board.

The LED test was performed using **GPIO 2** as the output pin. This helped verify the basic programming and GPIO functionality of the ESP32.

---

### 2. Objectives

The main objectives of Day 1 were:

* Set up the Arduino IDE for ESP32 development.
* Install the required ESP32 board support.
* Connect the ESP32 development board to the computer.
* Configure the ESP32 board in Arduino IDE.
* Select the appropriate communication port.
* Upload a basic firmware program.
* Test GPIO functionality using an LED.
* Verify the successful execution of the program on the ESP32.
* Understand the basic workflow for ESP32 development.

---

### 3. Hardware Used

The following hardware components were used:

* ESP32 development board
* USB cable
* Computer/Laptop
* LED for testing GPIO output
* Resistor, when using an external LED

---

### 4. Software Used

The following software tools were used:

* Arduino IDE
* ESP32 board support package
* USB-to-Serial driver
* Arduino IDE Serial Monitor

---

### 5. Arduino IDE Setup

Arduino IDE was used as the development environment for programming the ESP32.

The ESP32 board support was installed through the Arduino IDE Boards Manager. This provides the necessary board definitions, compiler tools, libraries, and upload support required for ESP32 development.

After installing the board support, the ESP32 was connected to the computer through a USB cable.

The appropriate ESP32 board and communication port were then selected in Arduino IDE.

---

### 6. ESP32 Board Configuration

After connecting the ESP32, the board was detected by the computer through the USB connection.

The required ESP32 board was selected in Arduino IDE, and the corresponding COM port was selected.

The configuration allowed Arduino IDE to:

1. Compile the ESP32 program.
2. Establish communication with the ESP32.
3. Upload the firmware.
4. Run the program on the ESP32.

---

### 7. GPIO 2 LED Blink Test

A basic LED blinking program was used to test the ESP32.

For the test, **GPIO 2** was configured as the output pin.

The LED was programmed to turn ON for one second and OFF for one second continuously.

The program used for the test was:

```cpp
#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
```

---

### 8. Working of the Program

The program consists of two main functions: `setup()` and `loop()`.

#### Pin Definition

```cpp
#define LED_PIN 2
```

GPIO 2 is assigned to the constant `LED_PIN`. This pin is used to control the LED.

#### Setup Function

```cpp
void setup() {
  pinMode(LED_PIN, OUTPUT);
}
```

The `setup()` function runs once when the ESP32 starts.

The `pinMode()` function configures GPIO 2 as an output pin.

#### Loop Function

```cpp
void loop() {
```

The `loop()` function runs continuously after the setup function.

#### Turning the LED ON

```cpp
digitalWrite(LED_PIN, HIGH);
```

The GPIO 2 output is set to HIGH, which turns the LED ON.

#### Delay

```cpp
delay(1000);
```

The program waits for 1000 milliseconds, or one second.

#### Turning the LED OFF

```cpp
digitalWrite(LED_PIN, LOW);
```

The GPIO 2 output is set to LOW, which turns the LED OFF.

Another one-second delay is applied before the process repeats.

Therefore, the LED continuously follows this sequence:

**ON → 1 second → OFF → 1 second → Repeat**

---

### 9. Firmware Upload

After configuring the board and communication port, the program was compiled using Arduino IDE.

The compiled program was then uploaded to the ESP32 through the USB connection.

The successful upload verified that the ESP32 was communicating correctly with the computer and was capable of receiving and executing the firmware.

---

### 10. LED Test

After the firmware was uploaded, the LED connected to GPIO 2 was observed.

The expected operation was:

| LED State             | Duration |
| --------------------- | -------: |
| ON                    | 1 second |
| OFF                   | 1 second |
| ON                    | 1 second |
| OFF                   | 1 second |
| Continuous repetition |        — |

The LED blinked continuously according to the programmed timing.

This confirmed that GPIO 2 was successfully configured and controlled by the ESP32.

---

### 11. Observations

The following observations were made during the test:

* The ESP32 was successfully connected to the computer.
* The board was recognized by Arduino IDE.
* The required ESP32 board configuration was completed.
* The program compiled successfully.
* The firmware was uploaded successfully.
* GPIO 2 operated as an output.
* The LED responded correctly to the programmed HIGH and LOW signals.
* The ESP32 continuously executed the uploaded program.

---

### 12. Troubleshooting

Some common issues that can occur during ESP32 setup were considered during the process.

| Issue                  | Solution                                               |
| ---------------------- | ------------------------------------------------------ |
| ESP32 not detected     | Check the USB connection and driver                    |
| COM port not available | Reconnect the board and check the USB-to-Serial driver |
| Upload failure         | Verify the selected board and COM port                 |
| LED not blinking       | Check GPIO 2 and the LED connection                    |
| Compilation error      | Verify ESP32 board support and program syntax          |

---

### 13. Learning Outcomes

Through this task, the following concepts were learned:

* Basic ESP32 architecture and development workflow.
* Arduino IDE configuration for ESP32.
* Installation and use of ESP32 board support.
* USB and serial communication with the ESP32.
* GPIO pin configuration.
* Digital output control.
* Firmware compilation and uploading.
* Basic LED interfacing.
* Use of Arduino C/C++ syntax for ESP32 programming.

---

### 14. Result

The ESP32 development environment was successfully configured.

The ESP32 was connected to the computer, configured in Arduino IDE, and programmed using a basic LED Blink application.

The LED connected to **GPIO 2** successfully turned ON and OFF at one-second intervals, confirming the basic functionality of the ESP32 and its GPIO output.

---

### 15. Conclusion

Day 1 successfully established the basic development environment for ESP32-based IoT applications.

The successful programming and GPIO test confirmed that the ESP32 was ready for further development. The knowledge gained from this task provides the foundation for upcoming activities involving sensors, Wi-Fi connectivity, data collection, and cloud-based IoT applications.

**Day 1 Status: Completed**
