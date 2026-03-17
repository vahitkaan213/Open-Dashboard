# Open Dashboard 🕒👻🍅

An open-source, ultra-cheap custom smart dashboard powered by the ESP32-S3 microcontroller. This project leverages the powerful LVGL graphics library to deliver a stunning and smooth user interface on budget TFT LCD screens.

## 🌟 Features & Pages
The dashboard interface is built using an `lv_tileview` that cycles smoothly through 4 dedicated pages, operated by a physical capacitive touch button. The rear NeoPixel LED dynamically changes colors to match the mood of the active page!

1. **Full-Screen Pixel Clock (Page 1)**
   * **Visuals**: A massive, screen-filling retro pixel clock (280-pixel tall characters).
   * **Logic**: Synchronizes perfectly with global timeservers via WiFi Network Time Protocol (NTP). Features active European/Warsaw timezone support (DST compliant).
   * **LED**: Glows soft Cyberpunk Purple.

2. **Japanese Horror Story (Page 2)**
   * **Visuals**: An atmospheric reading display dedicated to the creepy legend of "Hanako-san".
   * **Logic**: Employs deep red, blood-like formatting on a pitch-black background.
   * **LED**: Glows blood Red.

3. **Pomodoro Study Timer (Page 3)**
   * **Visuals**: A sleek, minimalist study timer utilizing a massive 260px stacked font layout for remaining minutes and seconds.
   * **Logic**: Features a dynamic bottom progress bar mapping your 25-minute WORK and 5-minute REST intervals. Controlled by dedicated physical touch buttons to play, pause, or reset.
   * **LED**: Glows vibrant Green during work sessions, and cool Blue during rest periods.

4. **Ghast Animation (Page 4)**
   * **Visuals**: A full-screen animation of the Minecraft Ghast.
   * **Logic**: Powered by LVGL's native GIF decoder utilizing directly mapped uncompressed byte arrays in the ESP32-S3's 8MB PSRAM to ensure flawless framerates without CPU bottlenecks.
   * **LED**: Glows an icy White/Cyan.

---

## 🛠️ Hardware & Components

To build this project, you will need the following budget-friendly components:

| Component | Description |
| :--- | :--- |
| **Microcontroller** | ESP32-S3 DevKitC-1 (Ensure model has 8MB PSRAM for the GIF decoder) |
| **Display Panel** | 3.5" or 4.0" TFT LCD screen (320x480 resolution) typically utilizing the ILI9488 or ST7796S driver. |
| **Inputs** | 3x TTP223 Capacitive Touch Sensor Modules (Active-HIGH configuration). |
| **Feedback LED** | 1x WS2812B NeoPixel RGB LED. |

### Wiring & Pinout
The components should be wired to the ESP32-S3 as follows:

*   **Display Backlight (`TFT_BL`)**: Pin `3` (Hardcoded HIGH during boot).
*   **Touch Button 1 (Page Cycle)**: Pin `4`
*   **Touch Button 2 (Pomodoro Play/Pause)**: Pin `5`
*   **Touch Button 3 (Pomodoro Reset)**: Pin `6`
*   **NeoPixel LED Data Pin**: Pin `48`

---

## 🚀 Installation & Setup

This project uses **PlatformIO** for package management and compilation.

1. **Clone the repository:**
   ```bash
   git clone https://github.com/vahitkaan213/Open-Dashboard.git
   ```
2. **Configure your WiFi:**
   Open `src/config.h` and enter your local WiFi credentials:
   ```cpp
   extern const char* ssid = "YOUR_WIFI_SSID";
   extern const char* password = "YOUR_WIFI_PASSWORD";
   ```
3. **Build and Upload:**
   Ensure your ESP32-S3 is plugged in and recognized, then compile and upload the filesystem using PlatformIO:
   ```bash
   pio run -t upload
   ```

## 📚 Libraries Used
The internal `platformio.ini` environment will automatically fetch these required dependencies:
*   [LovyanGFX](https://github.com/lovyan03/LovyanGFX) - Display Driver
*   [LVGL](https://github.com/lvgl/lvgl) - GUI Framework
*   [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) - LED Control
