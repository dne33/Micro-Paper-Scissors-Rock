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
#include "game_display.h"
#include "game_logic.h"

/* Define pacer rate in Hz. */
#define PACER_RATE 500
#define MESSAGE_RATE 12

int winner(int win_count) {
    win_counter(win_count);
    if (win_count == 4) {
        display_msg("CONGRATULATIONS!");
        return 1;
        win_count = 0;
    }
    return 0;
}
            
int main (void) 
{
    int counter = 0;
    char player = '0';
    char opponent = '0';
    char ch = '0';
    char chosen = 0;
    int win_count = -1;
    display_msg("PUSH UP TO START");
    ir_uart_init ();
    while (1)
    {
        tinygl_update();
        if (counter==0) {
            navswitch_update ();
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                counter++;
                tinygl_clear();
            }
        }
        
        if (counter == 1) {
            chosen = select_rps(player, chosen);
            if  (chosen == 0) {
                display_character('R');
            } else if (chosen == 1) {
                display_character('P');
            } else if (chosen == 2) {
                display_character('S');
            } else { 
                
                player = chosen;
                led_set(0,1);
                counter++;
                tinygl_clear();
                tinygl_update();
            }
            
        }
        
        if (counter == 2) {
            if (ir_uart_read_ready_p ()) {
                ch = ir_uart_getc ();
                if (ch == 'R' || ch == 'P' || ch == 'S' ) {
                    ir_uart_putc (player);
                    opponent = ch;
                    ch = '0';
                }
            }

            button_update();
            if (button_push_event_p(0)) {
                ir_uart_putc (player);
            }
        }
            
        if (counter==3) {
            led_set(0,0);
            char result = get_result(player, opponent);
            if (result == 'L') {
                display_msg("LOSER");
            } else if (result == 'W') {
                display_msg("WINNER");
                win_count++;
            } else if (result == 'D') {
                display_msg("DRAW");
            }
            counter++;
        }  
        if (counter == 4) {
            navswitch_update ();
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                ir_uart_putc('X'); // Break up repetitive sending of rps 
                tinygl_clear();
                if(winner(win_count)==1) {
                    counter++;
                } else {
                    counter = 1;
                    chosen = 0;
                    player = '0';
                    opponent = '0';
                }
                
            }
        }
        if (counter == 5) {
            navswitch_update ();
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                counter = 1;
                chosen = 0;
                player = '0';
                opponent = '0';
            }
        }
    }
    return 0;
    
}

