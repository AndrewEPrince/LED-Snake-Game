#include <Arduino.h>
#include "init.h"
#include "utilities.h"

int position_to_i(const int position[2]) {
  return position[0] + NUM_LED_STRIPS * position[1];
}

int i_to_x(const int i, const int y) {
  if (y % 2 != 0) {
    return LEDS_PER_STRIP - 1 - ((i % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
  } else {
    return ((i % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
  }
}

int i_to_y(const int i) {
  return i / LEDS_PER_STRIP % NUM_LED_STRIPS;
}

int xy_to_i(const int x, const int y) {
  return x + NUM_LED_STRIPS * y;
}