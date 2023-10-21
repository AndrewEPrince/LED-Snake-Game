
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
};

//This shows the score from the value passed to it.
class ShowScore {
  public:
    void showScore(SevenSegment sSegment, int value);  
};


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
    boolean isTimeOver = false;
    void restart();
    void updateTimeByFrame();
    void showTime(SevenSegment sSegment);
    void flashZeroes();
};

SevenSegment sevenSegment;
Timer timer;
ShowScore sScore;



void setup() {
  //Sets all segments & digits as outputs
  sevenSegment.setup();
}

void loop() {
  //This loops forever, and ever, and ever, and ever...
  //Updates timer
  timer.updateTimeByFrame();
  
  //Shows the timer and shows the score by refering to the methods
  timer.showTime(sevenSegment);
  sScore.showScore(sevenSegment, 32);


//When the timer ends, the timer section of the display will go to zero and stay there. 
 if (timer.isTimeOver) {
    sevenSegment.selectFirstDigit();
    sevenSegment.selectSecondDigit();
    sevenSegment.showZero();
  }
}

//This is the ShowScore method to show the score (as implied)
void ShowScore::showScore(SevenSegment sSegment, int value) {
  int dNumber = 2;
  int ones = value % 10;
  int tens = value / 10;
  
  sSegment.selectThirdDigit();
  sSegment.displayDigit(tens);

  delay(dNumber);

  sSegment.selectFourthDigit();
  sSegment.displayDigit(ones);

  delay(dNumber);
}

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
  
  sevenSegment.selectFirstDigit();
  sevenSegment.displayDigit(tens);

  delay(dNumber);

  sevenSegment.selectSecondDigit();
  sevenSegment.displayDigit(ones);

  delay(dNumber);
}

// SEVEN SEGMENTS METHODS
void SevenSegment::setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinD, OUTPUT);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

//This displays the digit based on whatever single digit integer is passed to it. 
void SevenSegment::displayDigit(int value) {
  if (value == 0) {
    sevenSegment.showZero();
  } else if (value == 1) {
    sevenSegment.showOne();
  } else if (value == 2) {
    sevenSegment.showTwo();
  } else if (value == 3) {
    sevenSegment.showThree();
  } else if (value == 4) {
    sevenSegment.showFour();
  } else if (value == 5) {
    sevenSegment.showFive();
  } else if (value == 6) {
    sevenSegment.showSix();
  } else if (value == 7) {
    sevenSegment.showSeven();
  } else if (value == 8) {
    sevenSegment.showEight();
  } else if (value == 9) {
    sevenSegment.showNine();
  } else {
  }
}

//Shows the digit '0'
void SevenSegment::showZero() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}

//Shows the digit '1'
void SevenSegment::showOne(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

//Shows the digit '2'
void SevenSegment::showTwo(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}
  
//Shows the digit '3'
void SevenSegment::showThree(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}
    
//Shows the digit '4'
void SevenSegment::showFour(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
    
//Shows the digit '5'
void SevenSegment::showFive(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
    
//Shows the digit '6'
void SevenSegment::showSix(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
  
//Shows the digit '7'
void SevenSegment::showSeven(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

//Shows the digit '8'   
void SevenSegment::showEight(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
    
//Shows the digit '9'
void SevenSegment::showNine(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}

//Turns off all of the segments
void SevenSegment::AllturnOffSegments(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

//Selects the third digit for 
void SevenSegment::selectThirdDigit(){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
}
      
void SevenSegment::selectFirstDigit(){
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
}
      
void SevenSegment::selectSecondDigit(){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
}
      
void SevenSegment::selectFourthDigit(){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
}

void SevenSegment::selectAll4Digits(){
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
}