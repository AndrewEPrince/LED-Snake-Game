#include "Adafruit_NeoPixel.h"
#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "init.h"

int position_to_i(const int position[2]);
int i_to_x(const int i, const int y);
int i_to_y(const int i);
int xy_to_i(const int x, const int y);
void screen_clear(Adafruit_NeoPixel &strip);

#endif