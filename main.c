#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <stdio.h>

static void button_event_cb(lv_event_t * e)
{
    lv_obj_t * label = lv_event_get_user_data(e);

    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        const char * text = lv_label_get_text(label);

        if(text[4] == 'O' && text[5] == 'F') {
            lv_label_set_text(label, "LED 1 ON");
            printf("LED 1 ON\n");
        } else {
            lv_label_set_text(label, "LED 1 OFF");
            printf("LED 1 OFF\n");
        }
    }
}

int main(void)
{
    lv_init();

    fbdev_init();
    evdev_init();

    static lv_color_t buf[800 * 100];
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, 800 * 100);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res = 800;
    disp_drv.ver_res = 480;

    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);

    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;

    lv_indev_drv_register(&indev_drv);

    lv_obj_t * button = lv_btn_create(lv_scr_act());
    lv_obj_set_size(button, 220, 100);
    lv_obj_center(button);

    lv_obj_t * label = lv_label_create(button);
    lv_label_set_text(label, "LED 1 OFF");
    lv_obj_center(label);

    lv_obj_add_event_cb(button, button_event_cb, LV_EVENT_CLICKED, label);

    while(1) {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}
