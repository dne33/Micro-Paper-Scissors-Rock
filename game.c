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


int main (void)
{
    char character = 'A';

    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("SELECT: Rock Paper Scissors");
    navswitch_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);
    

    while (1)
    {
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            pacer_wait ();
            tinygl_update ();
        }
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        
        if (navswitch_push_event_p (NAVSWITCH_EAST))
            character = 'R';
            display_character (character);

        if (navswitch_push_event_p (NAVSWITCH_SOUTH))
            character = 'P';
            display_character (character);

        if (navswitch_push_event_p (NAVSWITCH_WEST))
            character = 'S';
            display_character (character);

        if (navswitch_push_event_p (NAVSWITCH_PUSH))
            ir_uart_putc(character);

        if (ir_uart_read_ready_p ()) {
            char ch;
            ch = ir_uart_getc ();
            character = ch;
        }

        
        }

}