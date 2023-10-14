#include <SevSeg.h>

//Declares Variables
int pinA = 11; //
int pinB = 7; //
int pinC = 4; //
int pinD = 2; //
int pinE = 1; //
int pinF = 10; //
int pinG = 5; //
int pinDP = 3; //
int D1 = 12; //
int D2 = 9; //
int D3 = 8; //
int D4 = 6; //

int tens;
int ones;
int i;

unsigned long previousMillis = 0;
unsigned long interval = 1000UL;
unsigned long seconds = 10;

int dt = 1000;

class Timer {

  private: 


    int tens;
    int ones;

  public:
    void restart();
    


};

//void zero(void), one(void), two(void), three(void), four(void), five(void), six(void), seven(void), eight(void), nine(void);

//void (*segmentDisplay[]) = {zero, one, two, three, four, five, six, seven, eight, nine};

void setup() {//set all segments & digits as outputs

pinMode(pinA, OUTPUT);
pinMode(pinB, OUTPUT);
pinMode(pinC, OUTPUT);
pinMode(pinD, OUTPUT);
pinMode(pinE, OUTPUT);
pinMode(pinF, OUTPUT);
pinMode(pinG, OUTPUT);
pinMode(pinDP, OUTPUT);
pinMode(D1, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(D4, OUTPUT);

}

void loop() {
  
  if ((millis() - previousMillis) > interval) {
      previousMillis += interval;
      seconds--;
      

  if (seconds <= 0) {
    ones = 0;
    tens = 0;

  } else {
  ones = seconds % 10;
  tens = seconds / 10;

  }

  }

  

  firstDigit();
  CounterWithDisplay(tens);

  delay(5);

  secondDigit();
  CounterWithDisplay(ones);

  delay(5);

}

void CounterWithDisplay(int value) {
  if (value == 0) {
    zero();
  } else if (value == 1) {
    one();
  } else if (value == 2) {
    two();
  } else if (value == 3) {
    three();
  } else if (value == 4) {
    four();
  } else if (value == 5) {
    five();
  } else if (value == 6) {
    six();
  } else if (value == 7) {
    seven();
  } else if (value == 8) {
    eight();
  } else if (value == 9) {
    nine();
  } else {
  }
}

void Timer::restart() {

  seconds = 99;

}

//functions representing numbers 0-9
void zero() {
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, LOW);
  
  }

  void one(){
digitalWrite(pinA, LOW);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
}

void two(){
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, LOW);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, LOW);
digitalWrite(pinG, HIGH);
  }
  
  void three(){
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, LOW);
digitalWrite(pinF, LOW);
digitalWrite(pinG, HIGH);
    }
    
  void four(){
digitalWrite(pinA, LOW);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
    }
    
  void five(){
digitalWrite(pinA, HIGH);
digitalWrite(pinB, LOW);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, LOW);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
    }
    
  void six(){
digitalWrite(pinA, LOW);
digitalWrite(pinA, HIGH);
digitalWrite(pinB, LOW);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
    }
    
  void seven(){
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
    }
    
  void eight(){
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
    }
    
  void nine(){
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, LOW);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
    }


  void turnOffAllSegments(){
digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
          }

//functions to select individual digits on the display

  void thirdDigit(){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
}
      
  void firstDigit(){
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
      }
      
  void secondDigit(){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
      }
      
  void fourthDigit(){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
      }

  void all4Digits(){
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
        }