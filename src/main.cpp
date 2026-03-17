#include <Arduino.h>
#include "display.h"
#include "ui.h"
#include "app_logic.h"

void setup() {
  Serial.begin(115200);
  delay(1000); 
  Serial.println("\n--- ESP32 Smart Display Booting ---");
  
  // Power up backlight pin 3 early (Active-HIGH)
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  Serial.println("Backlight pin 3 forced HIGH.");
  
  // Initialize hardware and drivers
  Serial.println("Initializing display hardware...");
  init_display();
  Serial.println("Display initialized.");
  
  // Build LVGL interface
  Serial.println("Building UI components...");
  build_ui();
  Serial.println("UI components built.");
  
  // Setup logic and inputs (WiFi, buttons)
  Serial.println("Initializing application logic...");
  logic_setup();

  Serial.printf("PSRAM Size: %d bytes\n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
  Serial.printf("Free Internal Heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("Setup Complete! Free Heap: %d, Free PSRAM: %d\n", ESP.getFreeHeap(), ESP.getFreePsram());
  Serial.println("Setup Finished.");
  
  Serial.println("System Ready.");
}

void loop() {
  static uint32_t last_loop_msg = 0;
  if (millis() - last_loop_msg > 5000) {
    Serial.println("Main loop running...");
    last_loop_msg = millis();
  }

  // LVGL timer handler
  lv_timer_handler();
  
  // Application logic processing (timer, clock, buttons)
  logic_tick();
  
  delay(5);
}
