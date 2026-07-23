#include <lvgl.h>

#include <zmk/display/status_screen.h>
#include <zmk/display/widgets/battery_status.h>
#include <zmk/display/widgets/layer_status.h>
#include <zmk/display/widgets/output_status.h>
#include <zmk/display/widgets/wpm_status.h>

#include "widgets/bongo_cat.h"

static struct zmk_widget_bongo_cat bongo_cat_widget;
static struct zmk_widget_battery_status battery_status_widget;
static struct zmk_widget_output_status output_status_widget;
static struct zmk_widget_layer_status layer_status_widget;
static struct zmk_widget_wpm_status wpm_status_widget;

static void configure_label(lv_obj_t *label, lv_coord_t width, lv_text_align_t text_align) {
	lv_obj_set_width(label, width);
	lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_font(label, &lv_font_montserrat_8, LV_PART_MAIN);
	lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
	lv_obj_set_style_text_align(label, text_align, LV_PART_MAIN);
}

lv_obj_t *zmk_display_status_screen(void) {
	lv_obj_t *screen = lv_obj_create(NULL);

	lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);

	zmk_widget_bongo_cat_init(&bongo_cat_widget, screen);
	lv_obj_align(zmk_widget_bongo_cat_obj(&bongo_cat_widget), LV_ALIGN_TOP_LEFT, 0, 0);

	zmk_widget_output_status_init(&output_status_widget, screen);
	configure_label(zmk_widget_output_status_obj(&output_status_widget), 36, LV_TEXT_ALIGN_LEFT);
	lv_obj_align(zmk_widget_output_status_obj(&output_status_widget), LV_ALIGN_TOP_LEFT, 64, 0);

	zmk_widget_battery_status_init(&battery_status_widget, screen);
	configure_label(zmk_widget_battery_status_obj(&battery_status_widget), 24, LV_TEXT_ALIGN_RIGHT);
	lv_obj_align(zmk_widget_battery_status_obj(&battery_status_widget), LV_ALIGN_TOP_RIGHT, 0, 0);

	zmk_widget_layer_status_init(&layer_status_widget, screen);
	configure_label(zmk_widget_layer_status_obj(&layer_status_widget), 48, LV_TEXT_ALIGN_LEFT);
	lv_obj_align(zmk_widget_layer_status_obj(&layer_status_widget), LV_ALIGN_BOTTOM_LEFT, 64, 0);

	zmk_widget_wpm_status_init(&wpm_status_widget, screen);
	configure_label(zmk_widget_wpm_status_obj(&wpm_status_widget), 16, LV_TEXT_ALIGN_RIGHT);
	lv_obj_align(zmk_widget_wpm_status_obj(&wpm_status_widget), LV_ALIGN_BOTTOM_RIGHT, 0, 0);

	return screen;
}
