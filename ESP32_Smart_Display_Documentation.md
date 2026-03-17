# ESP32-S3 Minimal Smart Display

A lightweight, highly optimized ESP32-S3 smart display project that utilizes PSRAM and DMA for robust graphics rendering. The system features a 3-page user interface: a hardware-synced NTP Clock, a Pomodoro Timer, and a smooth GIF player.

## 1. Hardware Overview

To run this project, you will need the following components:

- **Microcontroller:** ESP32-S3 DevKitC-1 (Using a module with 8MB Flash and PSRAM is highly recommended).
- **Display:** 3.5" TFT LCD Display with **ILI9488** driver (SPI Interface).vertical display 3/4 oriantion 320x840 resolation
- **Controls:** 3 Physical Push Buttons (Configured as Active-LOW).

### 1.1 Wiring Diagram

The display uses a high-speed SPI bus, while the buttons are simple GPIOs that connect to ground when pressed, relying on the ESP32's internal Pull-Up resistors.

| Component   | Pin Name | ESP32-S3 Pin | Note                             |
| :---------- | :------- | :----------- | :------------------------------- |
| **Display** | VCC      | 5V / 3.3V    | Power                            |
| (ILI9488)   | GND      | GND          | Ground                           |
|             | CS       | 10           | Chip Select                      |
|             | RESET    | 46           | Reset                            |
|             | DC       | 9            | Data/Command                     |
|             | MOSI     | 11           | SDI (Serial Data In)             |
|             | SCK      | 12           | Clock                            |
|             | MISO     | 13           | SDO (Serial Data Out)            |
|             | LED      | 3            | Backlight (Always HIGH in code)  |
| **Objects** | Button 1 | 4            | **Page Navigation** (Cycle 1-3)  |
|             | Button 2 | 5            | **Action A** (Start/Pause)       |
|             | Button 3 | 6            | **Action B** (Mode/Reset)        |

***Note:** Connect one leg of each button to its respective GPIO pin (4, 5, or 6) and the other leg directly to `GND`. Built-in `INPUT_PULLUP` is used in the code.*

---

## 2. User Interface (UI) Pages

The system utilizes the LVGL (Light and Versatile Graphics Library) framework split into isolated rendering containers to avoid screen flickering and overlap. You can cycle through the pages sequentially by pressing **Button 1**.

### Page 1: Evil Lums GIF Player (Default Startup)
- **Description:** Instantly boots into a smooth looping GIF ("evil_evil_lums_gif"). 
- **Features:** This page is the default screen at startup to bypass any network delay or black screens while the system connects to the internet in the background.

### Page 2: NTP Clock
- **Description:** A digital clock styled with a retro 5x7 dot-matrix pixel aesthetic.
- **Features:** 
  - Automatically fetches accurate real-world time over the internet via `pool.ntp.org`.
  - **Offline Fallback:** If the WiFi connection fails or drops, the clock will display a robust gray `00:00` placeholder, waiting until the internet is restored where it instantly switches back to the vibrant green live time.

### Page 3: Pomodoro Timer
- **Description:** A productivity timer also using the retro 5x7 dot-matrix style (rendered in red).
- **Features:**
  - **Start/Pause:** Press **Button 2** to start the countdown. Press it again to pause.
  - **Mode Toggle/Reset:** Press **Button 3** to reset the timer. It toggles the duration between the standard **25-minute** Work mode and the **5-minute** break mode.

---

## 3. Software Requirements & Setup

### 3.1 Dependencies
This project is built using the PlatformIO environment. Ensure you have the following installed matching your `platformio.ini` specifications:
- **Framework:** Arduino core for ESP32
- **Graphics Libraries:** 
  - `LovyanGFX` (Hardware display driver optimized for ILI9488)
  - `lvgl` (UI System)

### 3.2 WiFi Configuration
The system requires an active 2.4GHz WiFi connection to fetch the NTP time for the clock. Before uploading, you must configure your network credentials at the top of `src/main.cpp`:

```cpp
const char *ssid = "Orange_Swiatlowod_3F40";
const char *password = "YJdhPP2H7wppoXHzXM";
```
*Note: The project currently assigns a static IP to `192.168.1.155`. If your router's gateway does not match `192.168.1.1` or you prefer DHCP, comment out the `WiFi.config(local_IP, gateway, subnet);` line.*

### 3.3 Flashing the Firmware (USB)
The first time you upload the project, you must use direct USB flushing for the ESP32-S3. Ensure your port is correct.

To upload the firmware via USB from a Linux (e.g., CachyOS) or macOS terminal using PlatformIO, run:

```bash
pio run --target upload -e esp32-s3-devkitc-1 --upload-port /dev/ttyACM0
```
*(Ensure `/dev/ttyACM0` matches the actual USB port your ESP32-S3 is plugged into.)*

### 3.4 Flashing the Firmware Over-The-Air (WiFi / OTA)
Once the device is flashed initially via USB and connects to your WiFi, you no longer need the USB cable for data! You can upload new code completely wirelessly.

To upload the firmware over WiFi (OTA), run:

```bash
pio run --target upload -e esp32-s3-devkitc-1 --upload-port 192.168.1.155 --upload-protocol espota
```
*(Ensure the device and your computer are on the same WiFi network.)*
