#include <Adafruit_NeoPixel.h>
#include "snake.h"
#include "utilities.h"
#include "apple.h"

// RECOMEND CREATING A NEW CLASS TO CONTROL DE SPAWN
void Apple::spawn_random() { // Accounting for snake collision in Snake update
        // random(0, TOTAL_LEDS) -> We make sure that the limit is always within the number of LEDs
        position[0] = random(0, TOTAL_LEDS) % LEDS_PER_STRIP;
        position[1] = random(0, TOTAL_LEDS) % NUM_LED_STRIPS;
         // Look for another position if and only if The apple is in the SNAKE


    // Show the position of the apple
    Serial.print("Apple spawned at (");
    Serial.print(position[0]);
    Serial.print(", ");
    Serial.print(position[1]);
    Serial.print(")\n");
}

// RECOMEND ADDIDNG THIS METHOD TO THE SNAKE
bool Apple::check_collision(Snake snake1) {
    for (int i = 0; i < snake1.length; i++){ // Get the lenght of the snake
        if (snake1.segments_x[i] == position[0] && snake1.segments_y[i] == position[1]) { // Check if the snake position is the same of the apple
            return true;
        }
    }

    // IF there is not any collision is false
    return false;
}

void Apple::show() {
    strip.setPixelColor(position_to_i(position), color);
    strip.show();
}

// I'm  assuming I won't create this function here
// int position_to_i(const int position[2]) {
//     return position[0] + NUM_LED_STRIPS * position[1];
// }