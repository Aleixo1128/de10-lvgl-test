# de10-lvgl-test


static void button_event_cb(lv_event_t * e)
{
    static int led_on = 0;

    lv_obj_t * label = lv_event_get_user_data(e);

    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        led_on = !led_on;

        if(led_on) {
            lv_label_set_text(label, "LED 1 ON");
            printf("LED 1 ON\n");
        } else {
            lv_label_set_text(label, "LED 1 OFF");
            printf("LED 1 OFF\n");
        }
    }
}


while(1) {
    lv_tick_inc(5);
    lv_timer_handler();
    usleep(5000);
}