#include "init.h"

void check_inputs(Snake &snake1) {
    left_button_state = digitalRead(LEFT_BUTTON_PIN);
    up_button_state = digitalRead(UP_BUTTON_PIN);
    down_button_state = digitalRead(DOWN_BUTTON_PIN);
    right_button_state = digitalRead(RIGHT_BUTTON_PIN);

    if (left_button_state == HIGH) {
        snake1.change_direction(Direction::LEFT);
    }
    if (up_button_state == HIGH) {
        snake1.change_direction(Direction::UP);
    }
    if (down_button_state == HIGH) {
        snake1.change_direction(Direction::DOWN);
    }
    if (right_button_state == HIGH) {
        snake1.change_direction(Direction::RIGHT);
    }
}

int position_to_i(const int position[2]) {
    return position[0] + NUM_LED_STRIPS * position[1];
}

int i_to_x(const int i, const int y) {
  if (y % 2 != 0 ){
    return LEDS_PER_STRIP - 1 - ((i % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
  }
  else {
    return ((i % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
  }
}

int i_to_y(const int i) {
	return i / LEDS_PER_STRIP % NUM_LED_STRIPS;
}

int xy_to_i(const int x, const int y) {
    return x + NUM_LED_STRIPS * y;
}