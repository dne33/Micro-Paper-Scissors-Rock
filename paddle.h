#ifndef PADDLE_H
#define PADDLE_H
#include <stdint.h>

#define START 4
#define LEFT_LIM 1
#define RIGHT_LIM 5

typedef struct {
    uint8_t pos;
} Paddle_t;

int8_t get_paddle_pos(Paddle_t* paddle); 

Paddle_t init_paddle (void);

void move_paddle_left(Paddle_t* paddle);

void move_paddle_right(Paddle_t* paddle);

#endif //PADDLE_H