// External Libraries
#include <Adafruit_NeoPixel.h>
#include <vector>

// Internal Libraries
#include <apple.h>
#include <init.h>
#include <snake.h>

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
    snake1.position[0] = 2;
    snake1.position[1] = 2;
    snake1.velocity[0] = 1;
    snake1.velocity[1] = 0;
    snake1.current_direction = Direction::RIGHT;
}


void loop() {

  if(snake1.is_alive) {
    snake1.update();
    Serial.print("px = ");
    Serial.print(snake1.position[0]);
    Serial.print(", py = ");
    Serial.print(snake1.position[1]);
    Serial.print(", vx = ");
    Serial.print(snake1.velocity[0]);
    Serial.print(", vy = ");
    Serial.println(snake1.velocity[1]);
  // Yousif's 60FPS hack :D
    for (int i = 0; i < 30; i++) {
  	check_inputs(snake1);
    delay(16);
    }
  }
  else { // When you die
      //call end_screen
    Serial.println("ENDGAME STATE");
    strip.clear(); // Not working bc of TinkerCad(?)
    return;
  }
    //delay(wait);
}