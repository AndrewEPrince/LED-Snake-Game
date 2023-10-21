#include <snake.h>
#include <utilities.h>

void Snake::change_direction(Direction direction) {
    switch (direction) {
        case Direction::LEFT:
            if (current_direction != Direction::RIGHT) {
                velocity[0] = -1;
                velocity[1] = 0;
                current_direction = Direction::LEFT;
            }
            break;
        case Direction::UP:
            if (current_direction != Direction::DOWN) {
                velocity[0] = 0;
                velocity[1] = -1;
                current_direction = Direction::UP;
            }
            break;
        case Direction::DOWN:
            if (current_direction != Direction::UP) {
                velocity[0] = 0;
                velocity[1] = 1;
                current_direction = Direction::DOWN;
            }
            break;
        case Direction::RIGHT:
            if (current_direction != Direction::LEFT) {
                velocity[0] = 1;
                velocity[1] = 0;
                current_direction = Direction::RIGHT;
            }
            break;
    }
}

void Snake::check_death() {
  for (int i = 1; i < length; i++) {
    if (head_on_position(segments_x[i], segments_y[i])) {
      is_alive = false;
    }
  }
}

bool Snake::head_on_position(int xPos, int yPos) {
  return (segments_x[0] == xPos && segments_y[0] == yPos);
}

void Snake::show() {
  for (int i = 0; i < length; i++) {
    strip.setPixelColor(xy_to_i(segments_x[i], segments_y[i]), color);
    strip.show();
  }
  
  /*
  strip.setPixelColor(position_to_i(position), color);
    strip.setPixelColor(position_to_i(prev_position), strip.Color(0, 0, 0));
    strip.show();
  */
}

void Snake::update() {
    change_direction(current_direction);
    prev_position[1] = position[1];
    prev_position[0] = position[0];
    position[1] = ((((position[1] + velocity[1]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP) % NUM_LED_STRIPS;

    row_is_odd = (position[1] % 2 != 0) ? true : false;

    if (!row_is_odd && !is_switched) {
        position[0] = (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
    }
    else if (row_is_odd && !is_switched) {
        position[0] = LEDS_PER_STRIP - 1 - (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
        is_switched = true;
    }
    else if (!row_is_odd && is_switched) {
        position[0] = LEDS_PER_STRIP - 1 - (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
        is_switched = false;
    }
    else if (is_switched) {
        position[0] = (((position[0] - velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
    }
	
  	segments_x.push_back(position[0]);
  	segments_y.push_back(position[1]);
  
    if (position[0] == apple1.position[0] && position[1] == apple1.position[1]) {
        length++;
        score++;
      	Serial.print("Length: "); // once you eat the second apple, length does not print to serialmonitor
        Serial.println(length);
        apple1.spawn_random();
      	apple1.show();
    }
    else if (length < segments_x.get_size()) {
        strip.setPixelColor(xy_to_i(segments_x[0], segments_y[0]), strip.Color(0,0,0));
		segments_x.pop_back();
      	segments_y.pop_back();
        Serial.println("POPPED");
    }
  if (snake1.is_alive) {
  	snake1.check_death();
  }
  if (!snake1.is_alive) {
    Serial.println("YOU'RE DEAD");
    strip.clear();
  } else {
    snake1.show();
  }
  
}