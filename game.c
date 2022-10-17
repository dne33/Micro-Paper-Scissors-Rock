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


/* Looping the starting message until Navswitch North is pressed
    @param counter Indicates what stage the program is on*/
int start_loop(int counter)
{
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        counter++;
        tinygl_clear();
    }
    return counter;

}


/* Tidy up chosen being used as both an int and a char*/
int select_character_loop(int counter, char* player, char* chosen )
{
    *chosen = select_rps(*player, *chosen); 
    if  (*chosen == 0) {
        display_character('R');
    } else if (*chosen == 1) {
        display_character('P');
    } else if (*chosen == 2) {
        display_character('S');
    } else { 
        *player = *chosen;
        tinygl_clear();
        tinygl_update();
        counter++;
    }
    return counter;

}


/* Loop to send and recieve
    @param counter indicates what stage the program is at
    @param recv  pointer to indicate if the opponents selection has been stored
    @param opponent poointer to opponents selction
    @param ch a pointer to a temporary storage of incoming IR chararacters
    @param player the players selection */
int send_recv_loop(int counter, int* recv,char* opponent,char* ch,char player)
{
    navswitch_update ();
    button_update();

    if (*recv==1) {
        if (ir_uart_read_ready_p ()) {
            *ch = ir_uart_getc ();
            if (*ch == 'R' || *ch == 'P' || *ch == 'S' ) {
                *opponent = *ch;
                *recv = 0; //Stop receiving when a valid character has been stored.
                led_set(0,1); //Notify player that the opponents selction has been received 
            }
            *ch = '0';
        }
    }
    
    if (button_push_event_p(0)) {
        ir_uart_putc (player);
    }

    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        counter++;
        *recv = 1;
    }
    return counter;

}


/* Loop to process the result
    @param counter indicates what stage the program is at
    @param result pointer to if the player won or lost
    @param win_count pointer to number of wins the player has
    @param player the players selection 
    @param opponent pointer to opponents selction*/
    
void process_result_loop(int* counter, int* win_count, char* player, char* opponent)
{
    static char result = '0';
    navswitch_update ();
    led_set(0,0);
    if (result == '0')
    {
        result = get_result(*player, *opponent);
        if (result == 'L') {
            display_msg("LOSER");
        } else if (result == 'W') {
            display_msg("WINNER");
            *win_count = *win_count + 1;
        } else if (result == 'D') {
            display_msg("DRAW");
        } 
        tinygl_update();
    } else {
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            result = '0';
            tinygl_clear();
            *counter = *counter +1;
        }
    }
}


/* Loop to process the result
    @param counter indicates what stage the program is at
    @param win_count pointer to number of wins the player has
    @param player the players selection 
    @param opponent pointer to opponents selction
    @param chosen pointer to what value needs to be displayed in selection_loop*/
int win_count_loop(int counter, int* win_count, char* player, char* opponent, char* chosen)
{

    win_counter(*win_count);
    if (*win_count == 4) {
        display_msg("CONGRATULATIONS!");\
        *win_count = -1;
        counter++;
    } else {
        counter = 1;
        *chosen = 0;
        *player = '0';
        *opponent = '0';
    }
    return counter;
}


/* Loop to process the result
    @param counter indicates what stage the program is at
    @param player the players selection 
    @param opponent pointer to opponents selction
    @param chosen pointer to what value needs to be displayed in selection_loop*/
int reset_loop(int counter, char* player, char* opponent, char* chosen)
{
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        counter = 1;
        *chosen = 0;
        *player = '0';
        *opponent = '0';
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
        
        if (counter == 1) {  
            counter = select_character_loop(counter, &player, &chosen);
        }
        
        if (counter == 2) {
            counter = send_recv_loop(counter, &recv, &opponent, &ch, player);
        }

        if (counter == 3) {
            process_result_loop(&counter, &win_count, &player, &opponent);
        }

        if (counter == 4) {
            counter = win_count_loop(counter, &win_count, &player, &opponent, &chosen);
        }

        if (counter == 5) {
            counter = reset_loop(counter, &player, &opponent, &chosen);
        }
        
    }
    return 0;
}

