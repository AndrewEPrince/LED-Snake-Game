#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

class SevenSegment {
  private:

  //Create a private class and set up pins
  //Sets up the pins for segments
    int pinA = 11;
    int pinB = 7;
    int pinC = 4;
    int pinD = 2;
    int pinE = 1;
    int pinF = 10;
    int pinG = 5;
    
  //Sets up the pins for digits
    int D1 = 12;
    int D2 = 9;
    int D3 = 8;
    int D4 = 6;

//Sets up all of the segments...
  public:
    void setup();
    void showZero();
    void showOne();
    void showTwo();
    void showThree();
    void showFour();
    void showFive();
    void showSix();
    void showSeven();
    void showEight();
    void showNine();
    void AllturnOffSegments();
    void selectThirdDigit();
    void selectFirstDigit();
    void selectSecondDigit();
    void selectFourthDigit();
    void selectAll4Digits();
    void displayDigit(int value);
    void showScore(int value);
};

//This shows the score from the value passed to it.
class ShowScore {
  public:
    void showScore(SevenSegment sSegment, int value);  
};

#endif
