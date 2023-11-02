#ifndef INIT_H
#define INIT_H
#include <Arduino.h>

constexpr int LED_PIN = 3;
constexpr int LEFT_BUTTON_PIN = A6;
constexpr int UP_BUTTON_PIN = A0;
constexpr int DOWN_BUTTON_PIN = A4;
constexpr int RIGHT_BUTTON_PIN = A2;

constexpr int NUM_LED_STRIPS = 16;
constexpr int LEDS_PER_STRIP = 32;
constexpr int BRIGHTNESS = 255;
constexpr int TOTAL_LEDS = NUM_LED_STRIPS * LEDS_PER_STRIP;

constexpr int START_X = 2;
constexpr int START_Y = 2;

#endif