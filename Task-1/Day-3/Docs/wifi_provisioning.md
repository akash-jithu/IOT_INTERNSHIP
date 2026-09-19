# Wi-Fi Provisioning

Wi-Fi provisioning is the process of providing Wi-Fi network credentials to an ESP32 so that it can connect to a wireless network.

The project currently uses pre-configured Wi-Fi credentials for development and testing. For future deployment, wireless provisioning methods can be used.

## 1. SmartConfig

SmartConfig allows Wi-Fi credentials to be sent wirelessly to the ESP32 from a compatible mobile application or provisioning tool.

### Working

```text
Mobile Device
     ↓
Wi-Fi Credentials
     ↓
SmartConfig
     ↓
ESP32
     ↓
Connects to Wi-Fi
````

### Advantages

* No USB connection required
* Credentials can be configured wirelessly
* Useful for initial device setup

### Limitations

* Requires a compatible provisioning application or tool
* Provisioning can depend on the Wi-Fi network environment

---

## 2. Captive Portal

A Captive Portal allows the ESP32 to temporarily create its own Wi-Fi access point.

The user connects to this network and enters the required Wi-Fi credentials through a web page.

### Working

```text
ESP32 Access Point
       ↓
User Connects
       ↓
Configuration Web Page
       ↓
Enter Wi-Fi Credentials
       ↓
ESP32 Connects to Wi-Fi
```

### Advantages

* No USB connection required
* Configuration through a normal web browser
* Easy for users to configure
* Suitable for field deployment

### Limitations

* Requires additional web-server and portal code
* Requires proper handling of credential storage

---

## 3. Comparison

| Feature          | SmartConfig       | Captive Portal |
| ---------------- | ----------------- | -------------- |
| Configuration    | Wireless          | Web browser    |
| USB Required     | No                | No             |
| Mobile App       | Usually required  | Not required   |
| User Interface   | Application-based | Web-based      |
| Setup            | Simple            | User-friendly  |
| Field Deployment | Suitable          | Suitable       |
| Additional Code  | Moderate          | Moderate       |

## 4. Current and Future Approach

The current project uses **pre-configured Wi-Fi credentials** during development and testing because it provides a simple way to establish the connection.

For future deployment of the WiFi Edge Node, **SmartConfig or Captive Portal** can be implemented to allow users to configure Wi-Fi without modifying and re-uploading the firmware.

### Conclusion

SmartConfig provides a wireless provisioning method, while a Captive Portal provides a browser-based configuration method. Both can eliminate the need for USB-based Wi-Fi configuration during field deployment.
