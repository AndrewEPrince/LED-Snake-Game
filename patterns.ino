void raindow_x(const int offset) {
    int x;
    int y;
    strip.clear();
    for (int i = 0; i < TOTAL_LEDS; i++) {
        y = i_to_y(i);
        x = ((i_to_x(i, y) + offset % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
        strip.setPixelColor(i, strip.ColorHSV(x * 65535 / TOTAL_LEDS * LEDS_PER_STRIP, 255, 255));
    }
    strip.show();
}

void raindow_y(const int offset) {
    int x;
    int y;
    strip.clear();
    for (int i = 0; i < TOTAL_LEDS; i++) {
        y = (((i_to_y(i) + offset) % NUM_LED_STRIPS) + NUM_LED_STRIPS) % NUM_LED_STRIPS;
        x = i_to_x(i, y);
        strip.setPixelColor(i, strip.ColorHSV(y * 65535 / TOTAL_LEDS * LEDS_PER_STRIP, 255, 255));
    }
    strip.show();
}

void rainbow_waterfall_x(const int loops, const int wait) {
    for (int i = 0; i < loops; i++) {
        raindow_x(-i);
        delay(wait);
    }
}

void rainbow_waterfall_y(const int loops, const int wait) {
    for (int i = 0; i < loops; i++) {
        raindow_y(-i);
        delay(wait);
    }
}

void random_hsv(const int loops, const int wait) {
  int x;
  int y;
  for (int i = 0; i < loops; i++) {
        strip.clear();
    for (int i = 0; i < TOTAL_LEDS; i++) {
        y = i_to_y(i);
        x = i_to_x(i, y);
        strip.setPixelColor(i, strip.ColorHSV(rand() % 65535, 255, 255));
    }
    strip.show();
        delay(wait);
    }
}
