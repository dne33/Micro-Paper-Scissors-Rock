#ifndef PADDLE_H
#define PADDLE_H

#define START 4
#define LEFT_LIM 1
#define RIGHT_LIM 5
typedef struct {
    uint8_t pos;
} Paddle;

int8_t get_paddle_pos(Paddle* paddle) 

void init_paddle (Paddle* paddle) 

void move_paddle_left(Paddle* paddle)

void move_paddle_right(Paddle* paddle)

#endif //PADDLE_H