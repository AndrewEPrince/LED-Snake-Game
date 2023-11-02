#include <Arduino.h>
#include "init.h"
#include "utilities.h"

int position_to_i(const int position[2]) {
  return xy_to_i(position[0], position[1]);
}

int i_to_y(const int i, const int y) {
  if (y % 2 != 0) {
    return LEDS_PER_STRIP - 1 - ((i % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
  } else {
    return ((i % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
  }
}

int i_to_x(const int i) {
  return i / LEDS_PER_STRIP % NUM_LED_STRIPS;
}

// int xy_to_i(const int x, const int y) {
//   return x + NUM_LED_STRIPS * y;
// }

int xy_to_i(const int x, const int y) {
  int i = 0;
  bool col_is_odd = (x % 2 != 0) ? true : false;

  i += x * LEDS_PER_STRIP; // Go to current Col
  if (col_is_odd) {
    i += LEDS_PER_STRIP - 1 - y;
  } else {
    i += y;
  }

  return i;
}

void screen_clear(Adafruit_NeoPixel &strip) {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
}