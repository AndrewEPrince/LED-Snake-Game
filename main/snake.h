#include "Array.h"
#include <stdint.h>
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