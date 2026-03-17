# Open-Dashboard 🚀
### Custom ESP32-S3 Smart Dashboard with LVGL

![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Compatible-orange.svg)
![ESP32-S3](https://img.shields.io/badge/Hardware-ESP32--S3-red.svg)

A high-performance, aesthetically pleasing, and open-source smart dashboard powered by the **ESP32-S3**. This project features a multi-page UI built with **LVGL 8.3**, leveraging **8MB of OPI PSRAM** for smooth animations and high-resolution assets.

---

## ✨ Features

- 🕒 **Full-Screen Pixel Clock**: Synchronized via WiFi NTP with native support for Warsaw Time (CET/CEST). Uses massive custom fonts for visibility.
- 📖 **Horror Story Reader**: A dedicated page for atmospheric reading, currently featuring "Hanako-san" with custom blood-red styling.
- 🍅 **Pomodoro Timer**: A productivity-focused timer with 25-minute work and 5-minute rest cycles. Horizontal progress bar and color-coded status.
- 👻 **Ghast Animation**: A pristine Minecraft Ghast GIF rendered natively using LVGL's GIF decoder, utilizing PSRAM for hardware-accelerated playback.
- 🌈 **Dynamic RGB Logic**: Onboard NeoPixel transitions colors based on the active page to provide ambient feedback.

---

## 🛠️ Hardware Connectivity

The project is designed for the **ESP32-S3 DevKitC-1** and a **320x480 TFT LCD**.

### 📌 Pinout Map

| Component | Pin | Notes |
| :--- | :--- | :--- |
| **Backlight** | GPIO 3 | Forced HIGH at boot |
| **Touch Button 1** | GPIO 4 | **Page Toggle** (Active-HIGH) |
| **Touch Button 2** | GPIO 5 | **Pomo Start/Pause** (Active-HIGH) |
| **Touch Button 3** | GPIO 6 | **Pomo Reset** (Active-HIGH) |
| **NeoPixel LED** | GPIO 48 | WS2812 Onboard |
| **Display** | Standard SPI | Uses LovyanGFX for high-speed ILI9488/ST7796 drivers |

---

## 🚀 Getting Started

### 1. Prerequisites
- [PlatformIO USB IDE](https://platformio.org/)
- ESP32-S3 DevKit (8MB Flash / 8MB PSRAM OPI version)

### 2. Configuration
Edit `src/config.cpp` (or `src/main.cpp` if defined there) to include your credentials:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

### 3. Build & Flash
```bash
pio run -t upload
```

---

## 📦 Libraries
- **LVGL 8.3.11**: Core UI framework
- **LovyanGFX**: High-performance display driver
- **Adafruit NeoPixel**: LED control
- **ArduinoOTA**: Wireless firmware updates

---

## 📄 License
This project is open-source under the **MIT License**. Feel free to fork and customize!

---
*Developed with ❤️ for the open-source community.*
