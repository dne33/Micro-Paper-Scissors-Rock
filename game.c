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

int main (void) 
{
    int counter = 0;
    char player = '0';
    char opponent = '0';
    char ch = '0';
    char chosen = 0;
    int win_count = -1;
    display_msg("PUSH UP TO START");
    while (1)
    {
        pacer_wait();

        if (counter==0) {
            tinygl_update();
            navswitch_update ();
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                counter++;
                tinygl_clear();
            }
        }
        
        if (counter == 1) {
            tinygl_update();
            chosen = select_rps(player, chosen);
            if  (chosen == 0) {
                display_character('R');
            } else if (chosen == 1) {
                display_character('P');
            } else if (chosen == 2) {
                display_character('S');
            } else { 
                led_set(0,1);
                player = chosen;
                counter++;
                tinygl_clear();
                tinygl_update();
            }
            
        }
        
        if (counter == 2) {

            //Hangs Here cannot figure out why? button is pressing but hangs on send.
            if (ir_uart_read_ready_p ()) {
                ch = ir_uart_getc ();
                if (ch == 'R' || ch == 'P' || ch == 'S' ) {
                    opponent = ch;
                    ch = '0';
                    counter++;
                }
    
            }

            button_update();
            if (button_push_event_p(0)) {
                tinygl_clear ();
                ir_uart_putc (player);
            }

        }
            
        if (counter==3) {
            ir_uart_putc(player);
            led_set(0,0);
            ir_uart_putc('X'); // Break up repetitive sending of rps 
            char result = get_result(player, opponent);
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

