// #include <Adafruit_NeoPixel.h>
// #include "snake.h"
// constexpr int LED_PIN = 2;
// constexpr int LEFT_BUTTON_PIN = 10;
// constexpr int UP_BUTTON_PIN = 11;
// constexpr int DOWN_BUTTON_PIN = 12;
// constexpr int RIGHT_BUTTON_PIN = 13;

// constexpr int NUM_LED_STRIPS = 8;
// constexpr int LEDS_PER_STRIP = 8;
// constexpr int BRIGHTNESS = 255;
// constexpr int TOTAL_LEDS = NUM_LED_STRIPS * LEDS_PER_STRIP;

// Adafruit_NeoPixel strip(NUM_LED_STRIPS * LEDS_PER_STRIP, LED_PIN, NEO_GRB + NEO_KHZ800);

// int wait = 500; // was 500
// int score = 0;

// int left_button_state = 0;
// int up_button_state = 0;
// int down_button_state = 0;
// int right_button_state = 0;

// int i = 0;
// int prev_position[2];

// enum class Direction {
//     LEFT,
//     UP,
//     DOWN,
//     RIGHT
// };

// class Apple;

// class Array {
// private:
//     int data[TOTAL_LEDS];
//     int size;

// public:
//     Array() : size(0) {}

//     void push_back(int value);
//     void pop_back();
//     int get_size() const;
//     int operator[](int index) const;
// };

// class Snake {
// public:
//     int position[2];
//     int velocity[2];
//   	int length = 3;
//     Array segments_x;
//   	Array segments_y;
//     Direction current_direction;
//     uint32_t color;
//     bool is_switched = false;
//     bool row_is_odd = false;
//     bool is_alive = true;

//     void update();
//     void change_direction(Direction new_direction);
//     void show();
//  	bool head_on_position(int x, int y);
//     void check_death(); 
// };

// class Apple {
// public:
//     int position[2];
//     uint32_t color = strip.Color(0, 255, 0);

//     void spawn_random();
//     void spawn_at(const int newPosition[2]);
//     void show();
//     bool check_collision(Snake);
// };

// int position_to_i(const int position[2]);
// int xy_to_i(const int x, const int y);

// Snake snake1;
// Apple apple1;

// void check_inputs(Snake &snake1);

// void setup() {
//     Serial.begin(9600);

//     pinMode(LED_PIN, OUTPUT);
//     pinMode(LEFT_BUTTON_PIN, INPUT);
//     pinMode(UP_BUTTON_PIN, INPUT);
//     pinMode(DOWN_BUTTON_PIN, INPUT);
//     pinMode(RIGHT_BUTTON_PIN, INPUT);

//     strip.setBrightness(BRIGHTNESS);

//     apple1.spawn_random();
//     apple1.show();

//     snake1.color = strip.Color(255, 0, 0);
//     snake1.position[0] = 2;
//     snake1.position[1] = 2;
//     snake1.velocity[0] = 1;
//     snake1.velocity[1] = 0;
//     snake1.current_direction = Direction::RIGHT;
// }


// void loop() {

//   if(snake1.is_alive) {
//     snake1.update();
//     Serial.print("px = ");
//     Serial.print(snake1.position[0]);
//     Serial.print(", py = ");
//     Serial.print(snake1.position[1]);
//     Serial.print(", vx = ");
//     Serial.print(snake1.velocity[0]);
//     Serial.print(", vy = ");
//     Serial.println(snake1.velocity[1]);
//   // Yousif's 60FPS hack :D
//     for (int i = 0; i < 30; i++) {
//   	check_inputs(snake1);
//     delay(16);
//     }
//   }
//   else { // When you die
//       //call end_screen
//     Serial.println("ENDGAME STATE");
//     strip.clear(); // Not working bc of TinkerCad(?)
//     return;
//   }
//     //delay(wait);
// }

// void check_inputs(Snake &snake1) {
//     left_button_state = digitalRead(LEFT_BUTTON_PIN);
//     up_button_state = digitalRead(UP_BUTTON_PIN);
//     down_button_state = digitalRead(DOWN_BUTTON_PIN);
//     right_button_state = digitalRead(RIGHT_BUTTON_PIN);

//     if (left_button_state == HIGH) {
//         snake1.change_direction(Direction::LEFT);
//     }
//     if (up_button_state == HIGH) {
//         snake1.change_direction(Direction::UP);
//     }
//     if (down_button_state == HIGH) {
//         snake1.change_direction(Direction::DOWN);
//     }
//     if (right_button_state == HIGH) {
//         snake1.change_direction(Direction::RIGHT);
//     }
// }

// void Array::push_back(int value) {
//         if (size < TOTAL_LEDS) {
//             data[size++] = value;
//         } else {
//             Serial.println("Array is full. Cannot push more elements.");
//         }
//     }

// void Array::pop_back() {
//     if (size > 0) {
//         // Shift all elements down by one position
//         for (int i = 0; i < size - 1; i++) {
//             data[i] = data[i + 1];
//         }
//         // Clear the last element
//         data[--size] = 0;
//     } else {
//         Serial.println("Array is empty. Cannot pop elements.");
//     }
// }
// int Array::get_size() const {
//   return size;
// }

// int Array::operator[](int index) const {
//   if (index >= 0 && index < size) {
//     return data[index];
//   } else {
//     Serial.println("Index out of bounds");
//     //Serial.println(index);
//   }
// }

// void Snake::update() {
//     change_direction(current_direction);
//     prev_position[1] = position[1];
//     prev_position[0] = position[0];
//     position[1] = ((((position[1] + velocity[1]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP) % NUM_LED_STRIPS;

//     row_is_odd = (position[1] % 2 != 0) ? true : false;

//     if (!row_is_odd && !is_switched) {
//         position[0] = (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
//     }
//     else if (row_is_odd && !is_switched) {
//         position[0] = LEDS_PER_STRIP - 1 - (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
//         is_switched = true;
//     }
//     else if (!row_is_odd && is_switched) {
//         position[0] = LEDS_PER_STRIP - 1 - (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
//         is_switched = false;
//     }
//     else if (is_switched) {
//         position[0] = (((position[0] - velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
//     }
	
//   	segments_x.push_back(position[0]);
//   	segments_y.push_back(position[1]);
  
//     if (position[0] == apple1.position[0] && position[1] == apple1.position[1]) {
//         length++;
//         score++;
//       	Serial.print("Length: "); // once you eat the second apple, length does not print to serialmonitor
//         Serial.println(length);
//         apple1.spawn_random();
//       	apple1.show();
//     }
//     else if (length < segments_x.get_size()) {
//         strip.setPixelColor(xy_to_i(segments_x[0], segments_y[0]), strip.Color(0,0,0));
// 		segments_x.pop_back();
//       	segments_y.pop_back();
//         Serial.println("POPPED");
//     }
//   if (snake1.is_alive) {
//   	snake1.check_death();
//   }
//   if (!snake1.is_alive) {
//     Serial.println("YOU'RE DEAD");
//     strip.clear();
//   } else {
//     snake1.show();
//   }
  
// }

// void Snake::change_direction(Direction direction) {
//     switch (direction) {
//         case Direction::LEFT:
//             if (current_direction != Direction::RIGHT) {
//                 velocity[0] = -1;
//                 velocity[1] = 0;
//                 current_direction = Direction::LEFT;
//             }
//             break;
//         case Direction::UP:
//             if (current_direction != Direction::DOWN) {
//                 velocity[0] = 0;
//                 velocity[1] = -1;
//                 current_direction = Direction::UP;
//             }
//             break;
//         case Direction::DOWN:
//             if (current_direction != Direction::UP) {
//                 velocity[0] = 0;
//                 velocity[1] = 1;
//                 current_direction = Direction::DOWN;
//             }
//             break;
//         case Direction::RIGHT:
//             if (current_direction != Direction::LEFT) {
//                 velocity[0] = 1;
//                 velocity[1] = 0;
//                 current_direction = Direction::RIGHT;
//             }
//             break;
//     }
// }

// void Snake::show() {
//   for (int i = 0; i < length; i++) {
//     strip.setPixelColor(xy_to_i(segments_x[i], segments_y[i]), color);
//     strip.show();
//   }
  
//   /*
//   strip.setPixelColor(position_to_i(position), color);
//     strip.setPixelColor(position_to_i(prev_position), strip.Color(0, 0, 0));
//     strip.show();
//   */
// }

// bool Snake::head_on_position(int xPos, int yPos) {
//   return (segments_x[0] == xPos && segments_y[0] == yPos);
// }

// void Snake::check_death() {
//   for (int i = 1; i < length; i++) {
//     if (head_on_position(segments_x[i], segments_y[i])) {
//       is_alive = false;
//     }
//   }
// }

// void Apple::spawn_random() {
//     do {
//         position[0] = rand() % LEDS_PER_STRIP;
//         position[1] = rand() % NUM_LED_STRIPS;
//     } while (check_collision(snake1));
//   Serial.print("Apple spawned at (");
//   Serial.print(position[0]);
//   Serial.print(", ");
//   Serial.print(position[1]);
//   Serial.print(")\n");
// }

// // True if apple is inside snake : false otherwise
// bool Apple::check_collision(Snake snake1) {
//   for (int i = 0; i < snake1.length; i++){
//     if (snake1.segments_x[i] == position[0] && snake1.segments_y[i] == position[1]){
//       return true;
//     }
//   }
//   return false;
// }

// void Apple::show() {
//     strip.setPixelColor(position_to_i(position), color);
//     strip.show();
// }

// int position_to_i(const int position[2]) {
//     return position[0] + NUM_LED_STRIPS * position[1];
// }

// int xy_to_i(const int x, const int y) {
//     return x + NUM_LED_STRIPS * y;
// }