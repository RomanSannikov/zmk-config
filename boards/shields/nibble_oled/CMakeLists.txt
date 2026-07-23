if(CONFIG_ZMK_DISPLAY AND CONFIG_SHIELD_NIBBLE_OLED)
  target_sources(app PRIVATE
    custom_status_screen.c
    assets/bongo_cat_frames.c
    widgets/bongo_cat.c
  )
endif()
