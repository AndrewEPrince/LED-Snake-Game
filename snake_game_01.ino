#include <Adafruit_NeoPixel.h>

constexpr int LED_PIN = 2;
constexpr int LEFT_BUTTON_PIN = 10;
constexpr int UP_BUTTON_PIN = 11;
constexpr int DOWN_BUTTON_PIN = 12;
constexpr int RIGHT_BUTTON_PIN = 13;

constexpr int NUM_LED_STRIPS = 8;
constexpr int LEDS_PER_STRIP = 8;
constexpr int BRIGHTNESS = 255;

Adafruit_NeoPixel strip(NUM_LED_STRIPS * LEDS_PER_STRIP, LED_PIN, NEO_GRB + NEO_KHZ800);

int TOTAL_LEDS = NUM_LED_STRIPS * LEDS_PER_STRIP;
int frame = 0;
int wait = 500;

int left_button_state = 0;
int up_button_state = 0;
int down_button_state = 0;
int right_button_state = 0;

int i = 0;
int prev_position[2];

enum class Direction {
    LEFT,
    UP,
    DOWN,
    RIGHT
};

class Apple;

class Snake {
public:
    int position[2];
    int velocity[2];
    Direction current_direction;
    uint32_t color;
    bool is_switched = false;
    bool row_is_odd = false;

    void update(Apple apple1);
    void change_direction(Direction new_direction);
    void show();
};

class Apple {
public:
    int position[2];
    uint32_t color = strip.Color(0, 255, 0);

    void spawn_random();
    void spawn_at(const int newPosition[2]);
    void show();
};

int position_to_i(const int position[2]);

Snake snake1;
Apple apple1;

void check_inputs(Snake &snake1);

void setup() {
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
    pinMode(LEFT_BUTTON_PIN, INPUT);
    pinMode(UP_BUTTON_PIN, INPUT);
    pinMode(DOWN_BUTTON_PIN, INPUT);
    pinMode(RIGHT_BUTTON_PIN, INPUT);

    strip.setBrightness(BRIGHTNESS);

    apple1.spawn_random();
    apple1.show();

    snake1.color = strip.Color(255, 0, 0);
    snake1.position[0] = 0;
    snake1.position[1] = 0;
    snake1.velocity[0] = 1;
    snake1.velocity[1] = 0;
    snake1.current_direction = Direction::RIGHT;
}


void loop() {
    Serial.print("px = ");
    Serial.print(snake1.position[0]);
    Serial.print(", py = ");
    Serial.print(snake1.position[1]);
    Serial.print(", vx = ");
    Serial.print(snake1.velocity[0]);
    Serial.print(", vy = ");
    Serial.println(snake1.velocity[1]);
    check_inputs(snake1);
    snake1.update(apple1);
    snake1.show();
    frame += 1;
    delay(wait);
}

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

void Snake::update(Apple apple1) {
    change_direction(current_direction);
    prev_position[1] = position[1];
    prev_position[0] = position[0];
    position[1] = ((((position[1] + velocity[1]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP) % NUM_LED_STRIPS;

    row_is_odd = (position[1] % 2 != 0) ? true : false;

    if (!row_is_odd && !is_switched) {
        position[0] = (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
    }
    else if (row_is_odd and !is_switched) {
        position[0] = LEDS_PER_STRIP - 1 - (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
        is_switched = true;
    }
    else if (!row_is_odd and is_switched) {
        position[0] = LEDS_PER_STRIP - 1 - (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
        is_switched = false;
    }
    else if (is_switched) {
        position[0] = (((position[0] - velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
    }

    if (position[0] == apple1.position[0] and position[1] == apple1.position[1]) {
        apple1.spawn_random();
      	apple1.show();
    }
}

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

void Snake::show() {
    strip.setPixelColor(position_to_i(position), color);
    strip.setPixelColor(position_to_i(prev_position), strip.Color(0, 0, 0));
    strip.show();
}

void Apple::spawn_random() {
    position[0] = rand() % LEDS_PER_STRIP;
    position[1] = rand() % NUM_LED_STRIPS;
}

void Apple::show() {
    strip.setPixelColor(position_to_i(position), color);
    strip.show();
}

int position_to_i(const int position[2]) {
    return position[0] + NUM_LED_STRIPS * position[1];
}
