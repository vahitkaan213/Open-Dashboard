# 🚀 Open-Dashboard: The Ultimate ESP32-S3 Smart Controller

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-Compatible-orange.svg)](https://platformio.org/)
[![Hardware](https://img.shields.io/badge/MCU-ESP32--S3-red.svg)](https://www.espressif.com/en/products/socs/esp32-s3)
[![Framework](https://img.shields.io/badge/Framework-Arduino-green.svg)](https://www.arduino.cc/)

A professional-grade, high-performance smart dashboard system built on the **ESP32-S3** platform. This project showcases the power of the S3's **Octal SPI (OPI) PSRAM** coupled with a vibrant **4-inch 320x480 TFT display** to create a fluid, multi-page user interface using **LVGL 8.3**.

---

## 📺 Project Demonstration

Check out the dashboard in action:

[Click here to watch the demo video!](https://www.youtube.com/shorts/q00bwqRD0so)

*(Note: Add your YouTube or Google Drive link here since the video file is too large for GitHub)*

---

## 💡 Core Features

### 1. 🕒 High-Visibility Pixel Clock
- **NTP Synchronization**: Updates over WiFi to maintain atomic-level accuracy.
- **Timezone Awareness**: Native support for **Warsaw (Europe/Central)** time, including automatic Daylight Saving Time (DST) transitions using POSIX timezone strings.
- **Typography**: Uses massive, custom-built fonts (up to 280px height) designed for maximum readability from across a room.

### 2. 📖 Atmospheric Horror Story Reader
- **Immersive UI**: Features a dedicated reading mode for "Hanako-san", formatted with blood-red color palettes and high-contrast typography.
- **Auto-Wrapping**: Leverages LVGL's text engine to handle long-form storytelling on a vertical screen.

### 3. ⏳ Advanced Pomodoro Timer
- **Productivity Engine**: Optimized for the 25/5 technique (25 min work / 5 min rest).
- **Visual Feedback**: A stacked digital layout with a high-resolution progress bar at the bottom.
- **State Logic**: Fully controlled via external hardware touch sensors for Start/Pause/Reset functionality.

### 4. 👻 Animated Ghast (Minecraft) Interface
- **Raw Performance**: Displays an uncompressed Minecraft Ghast GIF using the LVGL native GIF decoder.
- **Memory Optimization**: Utilizes the ESP32-S3's **8MB OPI PSRAM** to buffer and render high-quality animation frames without exhausting the internal heap.

### 5. 🌈 Ambient LED Integration
- **Contextual Lighting**: An onboard NeoPixel (WS2812B) provides peripheral feedback by changing colors based on the current page:
  - **Clock Mode**: Deep Purple
  - **Story Mode**: Blood Red
  - **Work Mode**: Vivid Green
  - **Rest Mode**: Calm Blue
  - **Ghast Mode**: Icy White/Cyan

---

## 🔧 Technical Hardware Specifications

### 📱 Display Module
- **Size**: 4.0-inch TFT LCD
- **Resolution**: 320x480 pixels
- **Integration**: Driven by the high-speed **Lovyan03/LovyanGFX** library for near-60fps UI performance.
- **Backlight Control**: GPIO 3 (Hard-wired for high-brightness output).

### 🧠 Microcontroller & Memory
- **SoC**: ESP32-S3 (Dual-core 240MHz)
- **Flash**: 8MB QIO
- **PSRAM**: **8MB Octal SPI (OPI)**. 
  - *Crucial for GIF decoding and large LVGL frame buffers.*
  - *Configured in `platformio.ini` via `board_build.arduino.memory_type = qio_opi`.*

### 🔘 Capacitive Touch Input
The dashboard is controlled by **TTP223** capacitive touch sensors. These are configured for **Active-HIGH** logic, providing a more robust and responsive navigation experience compared to traditional physical buttons.

| Sensor | Function | Pin |
| :--- | :--- | :--- |
| **Touch 1** | Page Transition / Home | GPIO 4 |
| **Touch 2** | Start / Pause Pomodoro | GPIO 5 |
| **Touch 3** | Reset Pomodoro Timer | GPIO 6 |

---

## 🛠️ Software Architecture

### Dependencies
- **LVGL v8.3.11**: Industrial-grade graphics library.
- **LovyanGFX**: Low-level display driver.
- **Adafruit NeoPixel**: Logic-level LED control.
- **ArduinoOTA**: Supports over-the-air firmware updates via WiFi.

### Build Instructions
This project is configured for **PlatformIO**. Simply clone the repo and run:
```bash
# Compile and Upload
pio run -t upload

# Open Serial Monitor
pio device monitor -b 115200
```

---

## 📜 License
Available under the **MIT License**. Check the `LICENSE` file for details.

---
*Created with passion for the ESP32 community. If you like this project, give it a ⭐!*
