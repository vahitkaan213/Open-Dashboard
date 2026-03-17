#ifndef UI_H
#define UI_H

#include <lvgl.h>

LV_FONT_DECLARE(my_font_280);
LV_FONT_DECLARE(my_font_260);

extern lv_obj_t *tv;
extern lv_obj_t *page1, *page2, *page3;

extern lv_obj_t *lbl_hour;
extern lv_obj_t *lbl_min;
extern lv_obj_t *lbl_pomo_hour;
extern lv_obj_t *lbl_pomo_min;
extern lv_obj_t *bar_pomo_progress;

void build_ui();

#endif // UI_H
