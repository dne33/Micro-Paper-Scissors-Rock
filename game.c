#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

void display_msg(char* message) {
    bool displaying = true;
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(message);
    while (displaying) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
           displaying = false;
        }
    }
}

int main (void)
{
    int index = 0;
    char rps[3] = {'R', 'P', 'S'};
    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    
    navswitch_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);
    

    while (1)
    {

        display_msg("SELECT: Rock Paper Scissors");
        if (navswitch_push_event_p (NAVSWITCH_WEST))
            if (index == 0) {
                index = 2;
            } else {
                index--;
            }

        if (navswitch_push_event_p (NAVSWITCH_PUSH))
            ir_uart_putc(rps[index]);

        if (ir_uart_read_ready_p ()) {
            char ch;
            if ((ch = ir_uart_getc ()) == 'R' || ch=='P'||ch=='S') {
                if (ch == 'R') {
                    index = 0;
                } else if (ch == 'P'){
                    index = 1;
                } else {
                    index = 2;
                }
            } 
        }
        display_character (rps[index]);
        
        }

}