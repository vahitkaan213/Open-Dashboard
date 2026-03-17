#include <Arduino.h>
#include "display.h"
#include "config.h"

LGFX tft;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf; // Allocate dynamically

LGFX::LGFX(void) {
  {
    auto cfg = _bus_instance.config();
    cfg.spi_host = SPI2_HOST;
    cfg.spi_mode = 0;
    cfg.freq_write = 20000000;
    cfg.freq_read  = 16000000;
    cfg.spi_3wire  = false;
    cfg.use_lock   = true;
    cfg.dma_channel = SPI_DMA_CH_AUTO;
    cfg.pin_sclk = 12;
    cfg.pin_mosi = 11;
    cfg.pin_miso = 13;
    cfg.pin_dc   = 9;
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);
  }
  {
    auto cfg = _panel_instance.config();
    cfg.pin_cs           = 10;
    cfg.pin_rst          = 46;
    cfg.pin_busy         = -1;
    cfg.panel_width      = SCREEN_WIDTH;
    cfg.panel_height     = SCREEN_HEIGHT;
    cfg.offset_x         = 0;
    cfg.offset_y         = 0;
    cfg.offset_rotation  = 0;
    cfg.dummy_read_pixel = 8;
    cfg.dummy_read_bits  = 1;
    cfg.readable         = true;
    cfg.invert           = false;
    cfg.rgb_order        = true;
    cfg.dlen_16bit       = false;
    cfg.bus_shared       = false;
    _panel_instance.config(cfg);
  }
  {
    auto cfg = _light_instance.config();
    cfg.pin_bl = 3;
    cfg.invert = false;
    cfg.freq   = 44100;
    cfg.pwm_channel = 7;
    _light_instance.config(cfg);
    _panel_instance.setLight(&_light_instance);
  }
  setPanel(&_panel_instance);
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  tft.startWrite();
  tft.pushImage(area->x1, area->y1, w, h, (uint16_t *)&color_p->full);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

void init_display() {
  Serial.println("  - LovyanGFX begin()...");
  tft.begin();
  tft.setRotation(0);
  tft.setBrightness(255);
  Serial.println("  - LVGL lv_init()...");
  lv_init();
  
  // Allocate LVGL draw buffer explicitly to Internal SRAM (DMA requirements)
  Serial.println("  - Allocating DMA buffer (1/4 screen)...");
  buf = (lv_color_t *)heap_caps_malloc(SCREEN_WIDTH * SCREEN_HEIGHT / 4 * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
  if (buf == NULL) {
    Serial.println("CRITICAL: Failed to allocate LVGL draw buffer!");
    while(1) delay(100);
  }
  
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, SCREEN_WIDTH * SCREEN_HEIGHT / 4);

  Serial.println("  - Registering display driver...");
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = SCREEN_WIDTH;
  disp_drv.ver_res = SCREEN_HEIGHT;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
  Serial.println("  - init_display finished.");
}
