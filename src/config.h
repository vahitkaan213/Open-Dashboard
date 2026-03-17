#ifndef CONFIG_H
#define CONFIG_H

// WiFi config
extern const char* ssid;
extern const char* password;

// NTP properties
extern const char* ntpServer;

// Button IO
#define BTN1_PIN 4
#define BTN2_PIN 5
#define BTN3_PIN 6

// RGB LED (WS2812 onboard)
#define RGB_LED_PIN 48
#define RGB_NUM_LEDS 1

// UI / Screen
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 480

#endif // CONFIG_H
