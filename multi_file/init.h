#ifndef INIT_H
#define INIT_H

constexpr int LED_PIN = 3;
constexpr int LEFT_BUTTON_PIN = 12;
constexpr int UP_BUTTON_PIN = 13;
constexpr int DOWN_BUTTON_PIN = 10;
constexpr int RIGHT_BUTTON_PIN = 11;

constexpr int NUM_LED_STRIPS = 16;
constexpr int LEDS_PER_STRIP = 32;
constexpr int BRIGHTNESS = 255;
constexpr int TOTAL_LEDS = NUM_LED_STRIPS * LEDS_PER_STRIP;

#endif