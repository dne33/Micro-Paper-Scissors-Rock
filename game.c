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


/* Displays CONGRATULATIONS if the player reaches 5 wins
    @param win_count current number of wins by the player */
int winner(int win_count) {
    win_counter(win_count);
    if (win_count == 4) {
        display_msg("CONGRATULATIONS!");
        return 1;
        win_count = -1;
    }
    return 0;
}


/* Looping the starting message until Navswitch North is pressed
    @param counter indicates what stage the program is on*/
int start_loop(int counter)
{
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        counter++;
        tinygl_clear();
    }
    return counter;

}


/*Initalise all components need to run the game*/
void initalise (void)
{
    system_init();
    ir_uart_init ();
    button_init();
    navswitch_init();
    pacer_init(PACER_RATE);

} 
            
int main (void) 
{

    initalise();
    int counter = 0;
    char player = '0';
    char opponent = '0';
    char result = '0';
    char ch = '0';
    char chosen = 0;
    int win_count = -1;
    int recv = 1;
    display_msg("PUSH UP TO START");

    while (1)
    {
        pacer_wait();
        tinygl_update();
        
        if (counter==0) {
            counter = start_loop(counter);
        }
        
        if (counter == 1) {  // could pass pointers of counter to update while still returning chosen neatly
            chosen = select_rps(player, chosen); 
            if  (chosen == 0) {
                display_character('R');
            } else if (chosen == 1) {
                display_character('P');
            } else if (chosen == 2) {
                display_character('S');
            } else { 
                player = chosen;
                tinygl_clear();
                tinygl_update();
                counter++;
            }
            
        }
        
        if (counter == 2) {
            navswitch_update ();
            button_update();

            if (recv==1) {
                if (ir_uart_read_ready_p ()) {
                    ch = ir_uart_getc ();
                    if (ch == 'R' || ch == 'P' || ch == 'S' ) {
                        opponent = ch;
                        recv = 0; //Stop receiving when a valid character has been stored.
                        led_set(0,1); //Notify player that the opponents selction has been received 
                    }
                    ch = '0';
                }
            }
         
            if (button_push_event_p(0)) {
                ir_uart_putc (player);
            }

            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                counter++;
                recv = 1;
            }                
            

        }

            
        if (counter == 3) {
            result = get_result(player, opponent);
            if (result == 'L') {
                display_msg("LOSER");
            } else if (result == 'W') {
                display_msg("WINNER");
                win_count++;
            } else if (result == 'D') {
                display_msg("DRAW");
            }
            tinygl_update();
            counter++;
            led_set(0,0);
        } 

        if (counter == 4) {
            navswitch_update ();
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
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

