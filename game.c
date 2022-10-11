#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "Display.h"
#include "Ball.h"


int main (void)
{
    uint8_t x = 3;
    uint8_t y = 4;
    uint8_t v = 0;


    Ball_t Ball = ball_init(x,y,v);
    display_ball(Ball);
}