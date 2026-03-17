#ifndef DISPLAY_H
#define DISPLAY_H

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lvgl.h>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ILI9488   _panel_instance;
  lgfx::Bus_SPI         _bus_instance;
  lgfx::Light_PWM       _light_instance;

public:
  LGFX(void);
};

extern LGFX tft;

void init_display();

#endif // DISPLAY_H
