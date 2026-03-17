#include "app_logic.h"
#include "config.h"
#include "ui.h"
#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoOTA.h>

// ---- RGB LED ----
Adafruit_NeoPixel rgb_led(RGB_NUM_LEDS, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

// ---- State ----
int current_page = 0;
uint32_t last_ntp_update = 0;

// Pomodoro State
bool pomo_running = false;
bool pomo_is_work = true;
int pomo_seconds = 25 * 60;
uint32_t last_pomo_tick = 0;

// Button state
bool btn1_prev = false;
bool btn2_prev = false;
bool btn3_prev = false;
uint32_t last_btn_press_time[3] = {0, 0, 0};
const uint32_t DEBOUNCE_DELAY = 250;

// ---- Clock ----
void update_clock() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo, 10)) {
        lv_label_set_text(lbl_hour, "00");
        lv_label_set_text(lbl_min, "00");
        return;
    }
    lv_label_set_text_fmt(lbl_hour, "%02d", timeinfo.tm_hour);
    lv_label_set_text_fmt(lbl_min, "%02d", timeinfo.tm_min);
}

// ---- RGB LED dynamic based on page ----
void update_rgb_led() {
    if (current_page == 0) {
        // Clock page: light purple
        rgb_led.setPixelColor(0, rgb_led.Color(100, 0, 255));
    } else if (current_page == 1) {
        // Horror story page: blood red
        rgb_led.setPixelColor(0, rgb_led.Color(255, 0, 0));
    } else if (current_page == 2) {
        // Pomodoro page: Green for work, Blue for rest
        if (pomo_is_work) {
            rgb_led.setPixelColor(0, rgb_led.Color(0, 255, 0));
        } else {
            rgb_led.setPixelColor(0, rgb_led.Color(0, 0, 255));
        }
    } else if (current_page == 3) {
        // Ghast GIF page: White/Cyan glow
        rgb_led.setPixelColor(0, rgb_led.Color(200, 255, 255));
    }
    rgb_led.show();
}

void update_pomo_ui() {
    char min_str[10];
    char sec_str[10];
    int m = pomo_seconds / 60;
    int s = pomo_seconds % 60;
    snprintf(min_str, sizeof(min_str), "%02d", m);
    snprintf(sec_str, sizeof(sec_str), "%02d", s);
    lv_label_set_text(lbl_pomo_hour, min_str);
    lv_label_set_text(lbl_pomo_min, sec_str);
    
    // Update progress bar
    int max_time = pomo_is_work ? (25 * 60) : (5 * 60);
    lv_bar_set_range(bar_pomo_progress, 0, max_time);
    // As time goes down, bar should go down. Or up? Usually bar shows remaining time.
    lv_bar_set_value(bar_pomo_progress, pomo_seconds, LV_ANIM_ON);
}


// ==========================
void logic_setup() {
    // Dokunmatik tus (TTP223 vb.) aktif HIGH cikis verir, PULLDOWN gerekmez.
    pinMode(BTN1_PIN, INPUT);
    pinMode(BTN2_PIN, INPUT);
    pinMode(BTN3_PIN, INPUT);

    rgb_led.begin();
    rgb_led.setBrightness(255);
    rgb_led.show();

    WiFi.begin(ssid, password);
    
    // OTA definitions
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else { // U_SPIFFS
            type = "filesystem";
        }
        Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
            Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            Serial.println("End Failed");
        }
    });
    ArduinoOTA.begin();
}

bool check_button(int pin, bool &prev_state, uint32_t &last_press, uint32_t now) {
    // Dokunmatik TTP223 modulleri basildiginda HIGH verir 
    // (Eger ESP32'nin kendi dahili dokunmatik pini kullaniliyorsa buranin touchRead(pin) > 30000_
    // veya benzeri bir degere cevrilmesi gerekir. Ancak "dokunmatik tus" genelde harici moduldur)
    bool current_state = digitalRead(pin);
    bool triggered = false;
    
    // Check for LOW to HIGH transition (rising edge)
    if (current_state == HIGH && prev_state == LOW && (now - last_press > DEBOUNCE_DELAY)) {
        triggered = true;
        last_press = now;
    }
    prev_state = current_state;
    return triggered;
}

void logic_tick() {
    uint32_t now = millis();

    if (WiFi.status() == WL_CONNECTED) {
        static bool time_configured = false;
        if (!time_configured) {
            configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", ntpServer); // Europe/Warsaw
            time_configured = true;
        }
        ArduinoOTA.handle(); // OTA listener
    }

    if (now - last_ntp_update > 1000) {
        update_clock();
        last_ntp_update = now;
    }

    // Pomodoro Timer Logic
    if (pomo_running && (now - last_pomo_tick > 1000)) {
        last_pomo_tick = now;
        if (pomo_seconds > 0) {
            pomo_seconds--;
        } else {
            // Switch state
            pomo_is_work = !pomo_is_work;
            pomo_seconds = pomo_is_work ? (25 * 60) : (5 * 60);
        }
        update_pomo_ui();
    }

    update_rgb_led();

    // Button 1: Switch Page
    if (check_button(BTN1_PIN, btn1_prev, last_btn_press_time[0], now)) {
        current_page = (current_page + 1) % 4; // Now loops through 4 pages
        lv_obj_set_tile_id(tv, current_page, 0, LV_ANIM_OFF);
    }
    
    // Button 2: Start / Pause Pomodoro
    if (check_button(BTN2_PIN, btn2_prev, last_btn_press_time[1], now)) {
        if (current_page == 2) {
            pomo_running = !pomo_running;
            last_pomo_tick = now;
        }
    }
    
    // Button 3: Reset Pomodoro
    if (check_button(BTN3_PIN, btn3_prev, last_btn_press_time[2], now)) {
        if (current_page == 2) {
            pomo_running = false;
            pomo_is_work = true;
            pomo_seconds = 25 * 60;
            update_pomo_ui();
        }
    }
}
