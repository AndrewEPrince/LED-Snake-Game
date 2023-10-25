#ifndef TIMER_H
#define TIMER_H

#include "7segment.h"
//This shows the score from the value passed to it.

// !!! Already in 7segment.h !!!
// class ShowScore {
//   public:
//     void showScore(SevenSegment sSegment, int value);  
// };


//The timer class!

class Timer {

//This section sets up the timer by setting tens to 6 and ones to 0. 
//It also sets the interval to 1000UL or 1 second. 
  private: 
    const int fTens = 6;
    const int fOnes = 0;
    const int fSeconds = 60;
    int tens = 6;
    int ones = 0;
    unsigned long previousMillis = 0;
    unsigned long interval = 1000UL;
    unsigned long seconds = 60;

//Sets isTimeOver to false and restarts the timer. 
  public:
    bool isTimeOver = false;
    void restart();
    void updateTimeByFrame();
    void showTime(SevenSegment sSegment);
    void flashZeroes();
};

#endif

