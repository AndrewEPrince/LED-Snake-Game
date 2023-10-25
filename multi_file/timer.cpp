#include <Arduino.h>
#include "timer.h"


//This restarts the timer 
void Timer::restart() {
  seconds = fSeconds;
  isTimeOver = false;
  ones = fOnes;
  tens = fTens;
}


//Updates time by frame
void Timer::updateTimeByFrame() {
  if (isTimeOver) return;

  if ((millis() - previousMillis) > interval) {
      previousMillis += interval;
      seconds--;

      if (seconds > 0) {
        ones = seconds % 10;
        tens = seconds / 10;
      } else {
        isTimeOver = true;
        ones = 0;
        tens = 0;
      }
  }
}

//Shows the time
void Timer::showTime(SevenSegment sSegment) {
  int dNumber = 2;
  
  sSegment.selectFirstDigit();
  sSegment.displayDigit(tens);

  delay(dNumber);

  sSegment.selectSecondDigit();
  sSegment.displayDigit(ones);

  delay(dNumber);
}