#include <Arduino.h>
#include <stdint.h>
#include <Adafruit_NeoPixel.h>

constexpr int LED_PIN = 2;
constexpr int LEFT_BUTTON_PIN = 10;
constexpr int UP_BUTTON_PIN = 11;
constexpr int DOWN_BUTTON_PIN = 12;
constexpr int RIGHT_BUTTON_PIN = 13;

constexpr int NUM_LED_STRIPS = 8;
constexpr int LEDS_PER_STRIP = 8;
constexpr int BRIGHTNESS = 255;
constexpr int TOTAL_LEDS = NUM_LED_STRIPS * LEDS_PER_STRIP;

Adafruit_NeoPixel strip(NUM_LED_STRIPS * LEDS_PER_STRIP, LED_PIN, NEO_GRB + NEO_KHZ800);

// DEFINE CLASSES
class Array { 
private:
    int data[TOTAL_LEDS];
    int size;

public:
    Array() : size(0) {}

    void push_back(int value);
    void pop_back();
    int get_size() const;
    int operator[](int index) const;
};

enum class Direction {
    LEFT,
    UP,
    DOWN,
    RIGHT
};

class Snake {
  public:
      int position[2];
      int velocity[2];
      int length = 3;
      Array segments_x;
      Array segments_y;
      Direction current_direction;
      uint32_t color;
      bool is_switched = false;
      bool row_is_odd = false;
      bool is_alive = true;
  
      void update();
      void change_direction(Direction new_direction);
      void show();
      bool head_on_position(int x, int y);
      void check_death(); 
};

class Apple {
    public:
        int position[2]; // Position of the apple
        uint32_t color = strip.Color(0, 255, 0); // GREEN COLOR

        void spawn_random();
        void spawn_at(const int newPosition[2]);
        void show();
        bool check_collision(Snake);
};

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
// TIMER CLASS
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
// -------------------------

Snake snake1;
Apple apple1;
int left_button_state = 0;
int up_button_state = 0;
int down_button_state = 0;
int right_button_state = 0;
int prev_position[2];
int score = 0;
SevenSegment sevenSegment;
Timer timer;
ShowScore sScore;

// UTILITES 
void check_inputs(Snake &snake1) {
    left_button_state = digitalRead(LEFT_BUTTON_PIN);
    up_button_state = digitalRead(UP_BUTTON_PIN);
    down_button_state = digitalRead(DOWN_BUTTON_PIN);
    right_button_state = digitalRead(RIGHT_BUTTON_PIN);

    if (left_button_state == HIGH) {
        snake1.change_direction(Direction::LEFT);
    }
    if (up_button_state == HIGH) {
        snake1.change_direction(Direction::UP);
    }
    if (down_button_state == HIGH) {
        snake1.change_direction(Direction::DOWN);
    }
    if (right_button_state == HIGH) {
        snake1.change_direction(Direction::RIGHT);
    }
}

int position_to_i(const int position[2]) {
    return position[0] + NUM_LED_STRIPS * position[1];
}

int i_to_x(const int i, const int y) {
  if (y % 2 != 0 ){
    return LEDS_PER_STRIP - 1 - ((i % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
  }
  else {
    return ((i % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
  }
}

int i_to_y(const int i) {
  return i / LEDS_PER_STRIP % NUM_LED_STRIPS;
}

int xy_to_i(const int x, const int y) {
    return x + NUM_LED_STRIPS * y;
}
// ---------------

void setup() {
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
    pinMode(LEFT_BUTTON_PIN, INPUT);
    pinMode(UP_BUTTON_PIN, INPUT);
    pinMode(DOWN_BUTTON_PIN, INPUT);
    pinMode(RIGHT_BUTTON_PIN, INPUT);

    strip.setBrightness(BRIGHTNESS);

    apple1.spawn_random();
    apple1.show();

    snake1.color = strip.Color(255, 0, 0);
    snake1.position[0] = 2;
    snake1.position[1] = 2;
    snake1.velocity[0] = 1;
    snake1.velocity[1] = 0;
    snake1.current_direction = Direction::RIGHT;

    sevenSegment.setup();
}

void loop() {
  timer.updateTimeByFrame();
  
  timer.showTime(sevenSegment);
  sScore.showScore(sevenSegment, 32);

  if(snake1.is_alive) {
    snake1.update();
    Serial.print("px = ");
    Serial.print(snake1.position[0]);
    Serial.print(", py = ");
    Serial.print(snake1.position[1]);
    Serial.print(", vx = ");
    Serial.print(snake1.velocity[0]);
    Serial.print(", vy = ");
    Serial.println(snake1.velocity[1]);
  // Yousif's 60FPS hack :D
    for (int i = 0; i < 30; i++) {
    check_inputs(snake1);
    delay(16);
    }
  }
  else { // When you die
      //call end_screen
    Serial.println("ENDGAME STATE");
    strip.clear(); // Not working bc of TinkerCad(?)
    return;
  }
    //delay(wait);

    if (timer.isTimeOver) { // GAMEOVER
      timer.restart();
    }
}

// INITIALIZE CLASSES
// #ARRAY CLASS
int Array::get_size() const {
  return size;
}

int Array::operator[](int index) const {
  if (index >= 0 && index < size) {
    return data[index];
  } else {
    Serial.println("Index out of bounds");
    //Serial.println(index);
  }
}

void Array::push_back(int value) {
        if (size < TOTAL_LEDS) {
            data[size++] = value;
        } else {
            Serial.println("Array is full. Cannot push more elements.");
        }
    }

void Array::pop_back() {
    if (size > 0) {
        // Shift all elements down by one position
        for (int i = 0; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        // Clear the last element
        data[--size] = 0;
    } else {
        Serial.println("Array is empty. Cannot pop elements.");
    }
}
// ###############################################
// #APPLE CLASS
void Apple::spawn_random() {
    do {
        // random(0, TOTAL_LEDS) -> We make sure that the limit is always within the number of LEDs
        position[0] = random(0, TOTAL_LEDS) % LEDS_PER_STRIP;
        position[1] = random(0, TOTAL_LEDS) % NUM_LED_STRIPS;
    } while (check_collision(snake1)); // Look for another position if and only if The apple is in the SNAKE


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
// ######################################

// #SNAKE CLASS
void Snake::change_direction(Direction direction) {
    switch (direction) {
        case Direction::LEFT:
            if (current_direction != Direction::RIGHT) {
                velocity[0] = -1;
                velocity[1] = 0;
                current_direction = Direction::LEFT;
            }
            break;
        case Direction::UP:
            if (current_direction != Direction::DOWN) {
                velocity[0] = 0;
                velocity[1] = -1;
                current_direction = Direction::UP;
            }
            break;
        case Direction::DOWN:
            if (current_direction != Direction::UP) {
                velocity[0] = 0;
                velocity[1] = 1;
                current_direction = Direction::DOWN;
            }
            break;
        case Direction::RIGHT:
            if (current_direction != Direction::LEFT) {
                velocity[0] = 1;
                velocity[1] = 0;
                current_direction = Direction::RIGHT;
            }
            break;
    }
}

void Snake::check_death() {
  for (int i = 1; i < length; i++) {
    if (head_on_position(segments_x[i], segments_y[i])) {
      is_alive = false;
    }
  }
}

bool Snake::head_on_position(int xPos, int yPos) {
  return (segments_x[0] == xPos && segments_y[0] == yPos);
}

void Snake::show() {
  for (int i = 0; i < length; i++) {
    strip.setPixelColor(xy_to_i(segments_x[i], segments_y[i]), color);
    strip.show();
  }
  
  /*
  strip.setPixelColor(position_to_i(position), color);
    strip.setPixelColor(position_to_i(prev_position), strip.Color(0, 0, 0));
    strip.show();
  */
}

void Snake::update() {
    change_direction(current_direction);
    prev_position[1] = position[1];
    prev_position[0] = position[0];
    position[1] = ((((position[1] + velocity[1]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP) % NUM_LED_STRIPS;

    row_is_odd = (position[1] % 2 != 0) ? true : false;

    if (!row_is_odd && !is_switched) {
        position[0] = (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
    }
    else if (row_is_odd && !is_switched) {
        position[0] = LEDS_PER_STRIP - 1 - (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
        is_switched = true;
    }
    else if (!row_is_odd && is_switched) {
        position[0] = LEDS_PER_STRIP - 1 - (((position[0] + velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
        is_switched = false;
    }
    else if (is_switched) {
        position[0] = (((position[0] - velocity[0]) % LEDS_PER_STRIP) + LEDS_PER_STRIP) % LEDS_PER_STRIP;
    }
  
    segments_x.push_back(position[0]);
    segments_y.push_back(position[1]);
  
    if (position[0] == apple1.position[0] && position[1] == apple1.position[1]) {
        length++;
        score++;
        Serial.print("Length: "); // once you eat the second apple, length does not print to serialmonitor
        Serial.println(length);
        apple1.spawn_random();
        apple1.show();
    }
    else if (length < segments_x.get_size()) {
        strip.setPixelColor(xy_to_i(segments_x[0], segments_y[0]), strip.Color(0,0,0));
    segments_x.pop_back();
        segments_y.pop_back();
        Serial.println("POPPED");
    }
  if (snake1.is_alive) {
    snake1.check_death();
  }
  if (!snake1.is_alive) {
    Serial.println("YOU'RE DEAD");
    strip.clear();
  } else {
    snake1.show();
  }
}
// ######################################
// SEVEN SEGMENT CLASS
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
    showZero();
  } else if (value == 1) {
    showOne();
  } else if (value == 2) {
    showTwo();
  } else if (value == 3) {
    showThree();
  } else if (value == 4) {
    showFour();
  } else if (value == 5) {
    showFive();
  } else if (value == 6) {
    showSix();
  } else if (value == 7) {
    showSeven();
  } else if (value == 8) {
    showEight();
  } else if (value == 9) {
    showNine();
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
// ######################################
// CLASS TIMER
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
// ######################################
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
// ######################################
// ------------------------

