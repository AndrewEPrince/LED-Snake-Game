#include "EndCard.h"

int THEEND [16][16] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
  {1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
  {1, 1, 0, 1, 1, 1, 0, 1, 1, 1 ,0, 1, 0, 1, 1, 1},
  {1, 1, 0, 1, 1, 1, 0, 1, 1, 1 ,0, 1, 0, 1, 1, 1},
  {1, 1, 0, 1, 1, 1, 0, 1, 1, 1 ,0, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1},
  {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
  {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1},
  {0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1},
 };

void lightLed (int** array) 
{
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            if (row %2 == 0) { // Row is currently even
                if (array[row][col] == 0) {
                    strip.setPixelColor(row*MAX_ROW+col, strip.Color(0, 0, 0));
                } 
                else 
                {
                    strip.setPixelColor(row*MAX_ROW+col, strip.Color(255, 255, 255));
                }
            } 
            else // Row is odd
            {
                
                if (array[row][16-col] == 0) 
                {
                    strip.setPixelColor(row*MAX_ROW+MAX_COL-col, strip.Color(0, 0, 0));
                }
                else 
                {
                    strip.setPixelColor(row*MAX_ROW+MAX_COL-col, strip.Color(255, 255, 255));
                }
            }
        }
        
    }
}
