/** @file   game.c
    @author  Matt Lane, Daniel Neal
    @date    13 October 2022
    @brief   Rock,Paper,Scissors game
*/


#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "button.h"
#include "led.h"
#include "../fonts/font5x5_1.h"

/* Define pacer rate in Hz. */
#define PACER_RATE 500
#define MESSAGE_RATE 12

<<<<<<< HEAD
int main (void) 
=======

int get_result(char player, char opponent,int win_count) 
{
    char result = '0';
    if (opponent == player) {
        result = 'D';
    }
    else if (player == 'S' && opponent == 'R') {
        result = 'L';
    }
    else if (player == 'S' && opponent == 'P') {
        result = 'W';
    }
    else if (player == 'R' && opponent == 'P') {
        result = 'L';
    }
    else if (player == 'R' && opponent == 'S') {
        result = 'W';
    }
    else if (player == 'P' && opponent == 'R') {
        result = 'W';
    }
    else if (player == 'P' && opponent == 'S') {
        result = 'L';
    }
    if (result != '0') {
        if (result == 'L') {
            display_msg("LOSER");
        } else if (result == 'W') {
            display_msg("WINNER");
            win_count++;
        } else if (result == 'D') {
            display_msg("DRAW");
        }
        tinygl_clear();
        result = '0';
    }
    return win_count;
}

void init(void) 
{
    system_init ();
    navswitch_init ();
    button_init ();
    ir_uart_init();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);

    pacer_init (PACER_RATE);

}

int main (void)
>>>>>>> ad71dc656e3377ce57d3aa1e55e4504821add741
{
    int counter = 0;
    int recv = 0;
    char player = '0';
    char opponent = '0';
    char ch = '0';
    int win_count = -1;

    init();
    
    while (1)
    {
        tinygl_update();
        button_update();
        pacer_wait();

        while(counter == 0) {
            display_msg("PUSH UP TO START");
            counter++;
        }

        if (player == '0') {
            char chosen = select_rps(player);
            if  (chosen == 'RX') {
                display_character('R')
            } else if (chosen == 'PX') {
                display_character('R')
            } else if (chosen == 'SX') {
                display_character('R')
            } else { 
                led_set(0,1)
                player = chosen;
            }
        }

        

        if (ir_uart_read_ready_p ()) {
            ch = ir_uart_getc ();
            if (ch == 'R' || ch == 'P' || ch == 'S' ) {
                opponent = ch;
                ch = '0';
            }
    
        }
        
        button_update();
        if (button_push_event_p(0)) {
            ir_uart_putc (player);
        }

    
        if (player != '0' && opponent != '0') {
            ir_uart_putc(player);
            led_set(0,0);
            ir_uart_putc('X'); // Break up repetitive sending of rps 
            result = get_result(player, opponent,win_count);
            if (result == 'L') {
                display_msg("LOSER");
            } else if (result == 'W') {
                display_msg("WINNER");
                win_count++;
            } else if (result == 'D') {
                display_msg("DRAW");
            }
            tinygl_clear();
            win_counter(win_count);
            if (win_count == 4) {
                display_msg("CONGRATULATIONS!");
                tinygl_clear();
                win_count = 0;
            }
            counter = 0;
            player = '0';
            opponent = '0';
        }
        
        
    }
    return 0;
    
}

