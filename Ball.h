#ifndef BALL_H
#define BALL_H

#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t v;
} Ball_t;

Ball_t ball_init(uint8_t x_cord,uint8_t y_cord,uint8_t v_cord);

#endif 