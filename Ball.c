#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Ball.h"

Ball_t init(uint8_t x_cord,uint8_t y_cord,uint8_t v_cord) 
{
    Ball_t new = {x_cord,y_cord,v_cord};
    return new;
}



