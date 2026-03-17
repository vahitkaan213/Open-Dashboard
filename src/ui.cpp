#include <Arduino.h>
#include "my_photo.h"
#include "my_ghast_gif.h"
#include "ui.h"

// Globals
lv_obj_t *tv;
lv_obj_t *page1, *page2, *page3, *page4;
lv_obj_t *lbl_hour;
lv_obj_t *lbl_min;
lv_obj_t *lbl_pomo_hour;
lv_obj_t *lbl_pomo_min;
lv_obj_t *lbl_pomo_status;
lv_obj_t *bar_pomo_progress;

#define CP_BG     0x000000
#define CP_PURPLE 0xFF309B  // R/B swapped for ILI9488: actual purple (155,48,255)

void build_ui() {
    Serial.println("  - Building Full-Screen Pixel Clock...");
    tv = lv_tileview_create(lv_scr_act());
    lv_obj_set_scrollbar_mode(tv, LV_SCROLLBAR_MODE_OFF);

    page1 = lv_tileview_add_tile(tv, 0, 0, LV_DIR_NONE);
    page2 = lv_tileview_add_tile(tv, 1, 0, LV_DIR_NONE);
    page3 = lv_tileview_add_tile(tv, 2, 0, LV_DIR_NONE);
    page4 = lv_tileview_add_tile(tv, 3, 0, LV_DIR_NONE);

    // Page 1: Clock (Cyberpunk)
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(CP_BG), 0);
    lv_obj_set_style_bg_color(tv, lv_color_hex(CP_BG), 0);
    lv_obj_set_style_bg_color(page1, lv_color_hex(CP_BG), 0);

    // Hours — 270px, top
    lbl_hour = lv_label_create(page1);
    lv_label_set_text(lbl_hour, "00");
    lv_obj_set_style_text_color(lbl_hour, lv_color_hex(CP_PURPLE), 0);
    lv_obj_set_style_text_font(lbl_hour, &my_font_280, 0);
    lv_obj_set_style_text_letter_space(lbl_hour, 2, 0);
    lv_obj_align(lbl_hour, LV_ALIGN_CENTER, 0, -105);

    // Minutes — 200px, bottom
    lbl_min = lv_label_create(page1);
    lv_label_set_text(lbl_min, "00");
    lv_obj_set_style_text_color(lbl_min, lv_color_hex(CP_PURPLE), 0);
    lv_obj_set_style_text_font(lbl_min, &my_font_280, 0);
    lv_obj_set_style_text_letter_space(lbl_min, 2, 0);
    lv_obj_align(lbl_min, LV_ALIGN_CENTER, 0, 105);

    // Page 2: Horror Story
    lv_obj_set_style_bg_color(page2, lv_color_hex(CP_BG), 0);
    // Remove default padding from the tileview page, then we can control margins perfectly.
    lv_obj_set_style_pad_all(page2, 0, 0);
    
    lv_obj_t *story_label = lv_label_create(page2);
    lv_label_set_long_mode(story_label, LV_LABEL_LONG_WRAP);
    // Ekran 320px, sifir bosluk
    lv_obj_set_width(story_label, 320); 
    
    // Metin yeterince uzun olmadigi ve font kucuk kaldigi icin alt/ustionerde bosluk kaldi.
    // Ekranin dikey donanimi 480px, yatay 320px. 
    // Yazi fontu (20 -> 24) buyutuldu ve metin uzatildi ki asagi dogru da duvar gibi tassin.
    const char* horror_story = 
        "Hanako-san, are you there? According to Japanese urban legends, the spirit of a young girl "
        "named Hanako-san haunts the last stall of the girls' bathroom on the third floor. "
        "During World War II, while hiding from air raids, she tragically suffocated to death "
        "in that dark, cold space. If you gather the courage to knock on her stall door three times "
        "and ask, 'Hanako-san, are you there?', you will hear a chilling, ethereal voice whisper from "
        "within, 'Yes, I am here...'. When you slowly open the door, you will see a little girl in a "
        "blood-red skirt, staring right at you... She is always there, watching you... "
        "Those who try to run are dragged into the toilet, descending to an endless hell. "
        "Do not look behind you now. Can you feel her cold breath on your neck? "
        "Her lifeless eyes are fixed on you... forever... and ever... waiting in the dark... "
        "You are not alone in this room.";

    lv_label_set_text(story_label, horror_story);
    lv_obj_set_style_text_align(story_label, LV_TEXT_ALIGN_LEFT, 0); 

    
    // R/B swapped for ILI9488: to get Red (255,0,0), we send Blue (0x0000FF)
    #define CP_RED 0x0000FF 
    
    lv_obj_set_style_text_color(story_label, lv_color_hex(CP_RED), 0);
    lv_obj_set_style_text_font(story_label, &lv_font_montserrat_18, 0); 
    lv_obj_align(story_label, LV_ALIGN_CENTER, 0, 0);

    // Page 3: Pomodoro Timer
    lv_obj_set_style_bg_color(page3, lv_color_hex(CP_BG), 0);
    
    // Minutes on top - 260px font
    lbl_pomo_hour = lv_label_create(page3);
    lv_label_set_text(lbl_pomo_hour, "25");
    lv_obj_set_style_text_color(lbl_pomo_hour, lv_color_hex(0x00FF00), 0); // Requested Green
    lv_obj_set_style_text_font(lbl_pomo_hour, &my_font_260, 0);
    lv_obj_set_style_text_letter_space(lbl_pomo_hour, 2, 0);
    lv_obj_align(lbl_pomo_hour, LV_ALIGN_CENTER, 0, -112); // Tightly packed for 260px font
    
    // Seconds on bottom - 260px font
    lbl_pomo_min = lv_label_create(page3);
    lv_label_set_text(lbl_pomo_min, "00");
    lv_obj_set_style_text_color(lbl_pomo_min, lv_color_hex(0x00FF00), 0); // Requested Green
    lv_obj_set_style_text_font(lbl_pomo_min, &my_font_260, 0);
    lv_obj_set_style_text_letter_space(lbl_pomo_min, 2, 0);
    lv_obj_align(lbl_pomo_min, LV_ALIGN_CENTER, 0, 102); // Tightly packed for 260px font
    
    // Progress bar at the very bottom
    bar_pomo_progress = lv_bar_create(page3);
    lv_obj_set_size(bar_pomo_progress, 280, 10);
    lv_obj_align(bar_pomo_progress, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_bar_set_range(bar_pomo_progress, 0, 25 * 60);
    lv_bar_set_value(bar_pomo_progress, 25 * 60, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(bar_pomo_progress, lv_color_hex(0x333333), LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar_pomo_progress, lv_color_hex(0x00FF00), LV_PART_INDICATOR); // Green indicator

    // Page 4: Ghast GIF
    lv_obj_set_style_bg_color(page4, lv_color_hex(CP_BG), 0);
    
    // Wrap the raw GIF data in an LVGL image descriptor so the decoder doesn't crash
    static lv_img_dsc_t ghast_gif_dsc = {
        .header = {
            .cf = LV_IMG_CF_RAW,
            .always_zero = 0,
            .reserved = 0,
            .w = 0,
            .h = 0,
        },
        .data_size = raw_gif_data_len,
        .data = raw_gif_data,
    };

    // Create the GIF
    lv_obj_t *ghast_gif = lv_gif_create(page4);
    lv_gif_set_src(ghast_gif, &ghast_gif_dsc);
    lv_obj_align(ghast_gif, LV_ALIGN_CENTER, 0, 0);
}
