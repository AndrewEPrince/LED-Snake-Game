#include <Arduino.h>
#include "Array.h"
#include "init.h"

int Array::get_size() const {
  return size;
}

int Array::operator[](int index) const {
  if (index >= 0 && index < size) {
    return data[index];
  } else {
    Serial.println("Index out of bounds");
    return -1;
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