class SevenSegment {
  private:
    int pinA = 11;
    int pinB = 7;
    int pinC = 4;
    int pinD = 2;
    int pinE = 1;
    int pinF = 10;
    int pinG = 5;
    
    int D1 = 12;
    int D2 = 9;
    int D3 = 8;
    int D4 = 6;

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
    void turnOffAllSegments();
    void selectThirdDigit();
    void selectFirstDigit();
    void selectSecondDigit();
    void selectFourthDigit();
    void selectAll4Digits();
    void displayDigit(int value);
};

class ShowScore {
  public:
    void showScore(SevenSegment sSegment, int value);  
};

class Timer {

  private: 
    int tens = 1;
    int ones = 0;
    unsigned long previousMillis = 0;
    unsigned long interval = 1000UL;
    unsigned long seconds = 10;

  public:
    boolean isTimeOver = false;
    void restart();
    void updateTimeByFrame();
    void showTime(SevenSegment sSegment);
};

SevenSegment sevenSegment;
Timer timer;
ShowScore sScore;

void setup() {//set all segments & digits as outputs
  sevenSegment.setup();
}

void loop() {
  timer.updateTimeByFrame();
  
  timer.showTime(sevenSegment);
  sScore.showScore(sevenSegment, 32);

  if (timer.isTimeOver) { // GAMEOVER
    timer.restart();
  }
}

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

void Timer::restart() {
  seconds = 10;
  isTimeOver = false;
  ones = 1;
  tens = 0;
}

void Timer::updateTimeByFrame() {
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

void SevenSegment::showZero() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}

void SevenSegment::showOne(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
void SevenSegment::showTwo(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}
  
void SevenSegment::showThree(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}
    
void SevenSegment::showFour(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
    
void SevenSegment::showFive(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
    
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
    
void SevenSegment::showSeven(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
    
void SevenSegment::showEight(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
    
void SevenSegment::showNine(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}


void SevenSegment::turnOffAllSegments(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

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
