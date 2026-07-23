#include "bongo_cat.h"

#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>

#include "../assets/bongo_cat_frames.h"

#define BONGO_CAT_STRIKE_MS 100

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);
static uint32_t press_count;

struct bongo_cat_state {
    uint32_t press_count;
};

static struct bongo_cat_state bongo_cat_get_state(const zmk_event_t *event) {
    const struct zmk_position_state_changed *position_event =
        event == NULL ? NULL : as_zmk_position_state_changed(event);

    if (position_event != NULL && position_event->state) {
        press_count++;
    }

    return (struct bongo_cat_state){.press_count = press_count};
}

static void return_to_idle(lv_timer_t *timer) {
    struct zmk_widget_bongo_cat *widget = timer->user_data;

    lv_img_set_src(widget->obj, &nibble_bongo_cat_idle);
    lv_timer_pause(timer);
}

static void bongo_cat_update_cb(struct bongo_cat_state state) {
    struct zmk_widget_bongo_cat *widget;

    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
        if (state.press_count == widget->handled_press_count) {
            continue;
        }

        widget->handled_press_count = state.press_count;
        lv_img_set_src(widget->obj, state.press_count % 2 == 0 ? &nibble_bongo_cat_right
                                                               : &nibble_bongo_cat_left);
        lv_timer_reset(widget->idle_timer);
        lv_timer_resume(widget->idle_timer);
    }
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_bongo_cat, struct bongo_cat_state, bongo_cat_update_cb,
                            bongo_cat_get_state)
ZMK_SUBSCRIPTION(widget_bongo_cat, zmk_position_state_changed);

int zmk_widget_bongo_cat_init(struct zmk_widget_bongo_cat *widget, lv_obj_t *parent) {
    widget->obj = lv_img_create(parent);
    widget->handled_press_count = 0;
    lv_img_set_src(widget->obj, &nibble_bongo_cat_idle);

    widget->idle_timer = lv_timer_create(return_to_idle, BONGO_CAT_STRIKE_MS, widget);
    lv_timer_pause(widget->idle_timer);

    sys_slist_append(&widgets, &widget->node);
    widget_bongo_cat_init();

    return 0;
}

lv_obj_t *zmk_widget_bongo_cat_obj(struct zmk_widget_bongo_cat *widget) { return widget->obj; }
