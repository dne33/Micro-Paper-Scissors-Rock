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
    char player = '0';

    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("Select: Rock Paper Scissors");
    navswitch_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);
    

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        
        if (navswitch_push_event_p (NAVSWITCH_EAST))
            player = 'R';

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) 
            player = 'P';

        if (navswitch_push_event_p (NAVSWITCH_WEST)) 
            player = 'S';

        if (navswitch_push_event_p (NAVSWITCH_PUSH))
            ir_uart_putc(player);

        
        if (ir_uart_read_ready_p ()) {
            char opponent;
            char result;
            opponent = ir_uart_getc ();
            if (opponent == player) {
                result = 'D';
            }
            else if (player == 'S' && opponent == 'R')
            {
                result = 'L';
            }
            else if (player == 'S' && opponent == 'P')
            {
                result = 'W';
            }
            else if (player == 'R' && opponent == 'P')
            {
                result = 'L';
            }
            else if (player == 'R' && opponent == 'S')
            {
                result = 'W';
            }
            else if (player == 'P' && opponent == 'R')
            {
                result = 'W';
            }
            else if (player == 'P' && opponent == 'S')
            {
                result = 'L';
            }
            if (result != '0')
            {
                display_character(result);
                pacer_wait();
                pacer_wait();
                pacer_wait();
                pacer_wait();
            }
        }      
    }
    display_character (player);
}

