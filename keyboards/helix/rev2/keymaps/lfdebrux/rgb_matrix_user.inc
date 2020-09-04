RGB_MATRIX_EFFECT(bi_flag)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool bi_flag(effect_params_t* params) {
  /* The stripe colors and widths, from top to bottom, are pink (40%), purple
   * (20%), and blue (40%). The exact colors given by the designer are: PMS
   * 226, 258, and 286. Their approximate HTML values are #D60270, #9B4F96,
   * #0038A8; their approximate RGB values are (214,2,112), (155,79,150), and
   * (0,56,168), respectively. -- https://en.wikipedia.org/wiki/Bisexual_pride_flag
   */
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    uint8_t y = g_led_config.point[i].y;
    if (y < 25) {
      rgb_matrix_set_color(i, RGB_PINK);
    } else if (y < 38) {
      rgb_matrix_set_color(i, RGB_PURPLE);
    } else {
      rgb_matrix_set_color(i, RGB_BLUE);
    }
  }
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
