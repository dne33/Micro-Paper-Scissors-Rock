#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"


int main (void)
{
    system_init ();
    navswitch_init();
    pacer_init (PACER_RATE);
    

    

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