# ESP32 Smart Display - Project Instructions & Chat Log

**Introduction:**
An open-source, ultra-cheap custom smart dashboard powered by ESP32. Features a massive NTP pixel clock, a unique reading display, and a sleek Pomodoro timer with progress tracking. Built with LVGL for stunning visuals on budget TFT screens.

## 1. Project Overview
This project is an ESP32-S3 driven smart display using LVGL and a custom 320x480 TFT screen. The system has four main pages:
1. **Full-Screen Pixel Clock**: A dynamically updated WiFi NTP clock that fills the screen with massive 280-pixel tall characters.
2. **Japanese Horror Story**: A screen dedicated to a wrapped horror story ("Hanako-san") featuring blood-red text formatting.
3. **Pomodoro Timer**: A minimalist study timer (Page 3) incorporating a large 260-pixel stacked countdown indicator and a bottom progress bar to monitor work (25m) and rest (5m) cycles.
4. **Ghast Animation**: A final page displaying a Minecraft Ghast GIF (`my_ghast_gif.h`) utilizing LVGL's native GIF decoder widget.

## 2. Hardware Setup
### Components
*   **Microcontroller:** ESP32-S3 DevKitC-1
*   **Display:** 320x480 TFT LCD (RGB colorspace swapped on the specific ILI9488 panel)
*   **Input:** TTP223 Capacitive Touch Sensors (Active-HIGH setup for navigating pages and toggling Pomodoro)
*   **LED:** Onboard NeoPixel (WS2812) to dynamically change colors based on the active page (Purple for Clock, Red for Horror, Green/Blue for Pomodoro)

### Pinout Configuration
*   **Buttons:** Pins 4, 5, 6
*   **NeoPixel:** Pin 48
*   **Backlight:** Pin 3 (Forced HIGH early in boot)

## 3. Libraries Used
Ensure the following are in `platformio.ini`:
*   `lovyan03/LovyanGFX`
*   `lvgl/lvgl`
*   `adafruit/Adafruit NeoPixel`
*   `WiFi`
*   `ArduinoOTA`

## 4. Timezone Configurations
The system utilizes Network Time Protocol (NTP) to stay perfectly in sync. 
During setup, `configTzTime` is utilized passing the POSIX descriptor to ensure Daylight Saving Time in Warsaw is natively supported:
```cpp
configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", ntpServer);
```

---

## 5. Developer Chat Log

**Date:** March 2026
**Topic:** Pomodoro UI Refactoring

> **USER:** make button high activated
> **AI:** Changed the button inputs from `INPUT_PULLUP` active-low to `INPUT_PULLDOWN` (or standard `INPUT`) active-high logic to correctly capture rising edges for the touch sensors.
> 
> **USER:** upload
> **AI:** Compiled and flashed the firmware. Encountered some Linux dual USB auto-detect issues but utilized correct CLI parameters to resolve.
> 
> **USER:** simdi senden istedigim pomodro kisminin tarzini degistirmen daha buyuk yazilar olsun yani saat dakika alt alta en alltada minik prograss bar olsun *(Now I want you to change the style of the Pomodoro section to have larger text, with hours and minutes stacked, and a small progress bar at the bottom)*
> **AI:** Drafted a redesign plan to incorporate a completely revamped Page 3. Split the single time display into two distinct `lbl_pomo_hour` and `lbl_pomo_min` labels arrayed vertically. Added `lv_bar_create(page3)` attached to `LV_ALIGN_BOTTOM_MID`.
> 
> **USER:** pomodro sayfasindaki saati yesil yap bode work yazisi arkaya geliyor *(Make the time on the Pomodoro page green, also the 'work' text is falling behind)*
> **AI:** Updated color hex codes arrays for `lbl_pomo...` from `0xFFFFFF` to `0x00FF00` (green). Lifted the object layout using `lv_obj_move_foreground(lbl_pomo_status)` so the "WORK/REST" tags rendered cleanly over the massive clock numerals.
> 
> **USER:** work yazini tamamen kaldir ve saat progress bar ile cakisiyor hala bi tik kucult saati work rest yazisi istemiyorum sil direkt *(Remove the 'work' text entirely, the clock still overlaps with the progress bar, shrink the clock a bit. I don't want the work/rest text at all, delete it directly)*
> **AI:** Stripped `lbl_pomo_status` entirely out of the application space. Downgraded the core typography font sizing for the Pomodoro loop from `my_font_280` down to `my_font_200`, aligning center Y shifts.
> 
> **USER:** saati buyut bi tik daha *(Make the clock a bit bigger again)*
> **AI:** Tested and discovered the optimal size between overlap and massive readability was `my_font_260`. Adjusted offset tight packing values (`-112`, `102`) to stack perfectly over the progress bar.
> 
> **USER:** saati warsaw a gore ayarla bide proje instuurctions dosyasi yap sonra icine chat log koy .md olabilir cok detayli ve uzun olsun ingilizce olsun *(Set the clock to Warsaw time and also make a project instructions file, then put the chat log inside, it can be .md, make it very detailed and long, in English)*
> **AI:** Discovered Warsaw timezone attributes, shifting time initialization script from `configTime()` arrays directly to an active `configTzTime()` parser to resolve European Summertime transitions correctly. Executed documentation pipeline to generate this exact Markdown record.
