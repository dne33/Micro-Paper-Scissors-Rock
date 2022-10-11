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
#include "paddle.h"
#include "navswitch.h"

int main (void)
{
    system_init ();
    navswitch_init();
    pacer_init (500);
    uint8_t x = 3;
    uint8_t y = 3;
    uint8_t v = 0;
    Ball_t Ball = ball_init(x,y,v);
    display_ball(Ball);
    Paddle_t paddle = init_paddle();
    display_paddel(paddle);

    

    while(1)
    {
        pacer_wait ();
        navswitch_update();


        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                move_paddle_right(&paddle);
                display_paddel (paddle);
            }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                move_paddle_left(&paddle);
                display_paddel (paddle);
            }
    }
}