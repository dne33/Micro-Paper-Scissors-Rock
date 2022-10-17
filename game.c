/** @file   game.c
    @author  Matt Lane, Daniel Neal
    @date    13 October 2022
    @brief   Rock,Paper,Scissors game
*/

#include "game.h"

/**
 * @brief Looping the starting/ending message until Navswitch North is pressed 
 * @param counter Indicates what stage the program is on
 */
#include "game.h"


/*Initalise all components need to run the game*/
void initalise (void)
{
    system_init();
    ir_uart_init ();
    button_init();
    navswitch_init();
    pacer_init(PACER_RATE);

} 


/* Looping the starting message until Navswitch North is pressed*/
bool start_loop(void)
{
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        tinygl_clear();
        return true;
    }
    return false;

}

/**
 * @brief Tidy up chosen being used as both an int and a char 
 */

bool select_character_loop(char* player, char* chosen )
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
        led_set(0,1);
        tinygl_clear();
        tinygl_update();
        return true;
    }
    return false;

}


/**
 * @brief Allows for users to press a button to transmit selections.
 * @param opponent poointer to opponents selction
 * @param player the players selection
 */
bool send_recv_loop(char* opponent, char player)
{
    static int sending = 0;
    char ch = '0';
    navswitch_update ();
    button_update();
    if (ir_uart_read_ready_p ()) {
        ch = ir_uart_getc ();
        if (ch == 'R' || ch == 'P' || ch == 'S' ) {
            if (ir_uart_write_ready_p()) {
                ir_uart_putc (player);
                *opponent = ch;
                ch = '0';
                return true;
            }
        }
    }

    if (button_push_event_p(0) || sending == 1) {
        if (ir_uart_write_ready_p()) {
            sending = 0;
            ir_uart_putc (player);
        } else {
            sending = 1;
        }
    }
    return false;

}

/**
 * @brief Loop to process the result
 * @param counter indicates what stage the program is at
 * @param result pointer to if the player won or lost
 * @param win_count pointer to number of wins the player has
 * @param player the players selection 
 * @param opponent pointer to opponents selction*
 */   
bool process_result_loop(int* win_count, int* loss_count, char* player, char* opponent)
{
    static char result = '0';
    navswitch_update ();
    led_set(0,0);
    if (result == '0') {
        result = get_result(*player, *opponent);
        if (result == 'L') {
            display_msg("LOSER");
            *loss_count = *loss_count + 1;
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
            return true;
        }
    }
    return false;
}

/**
 * @brief Loop to process the result
 * @param counter indicates what stage the program is at
 * @param win_count pointer to number of wins the player has
 * @param player the players selection 
 * @param opponent pointer to opponents selction
 * @param chosen pointer to what value needs to be displayed in selection_loop
 */
bool win_count_loop(int* win_count, int*loss_count, char* player, char* opponent, char* chosen)
{
    ir_uart_putc ('X');
    win_counter(*win_count);
    if (*win_count == 4) {
        display_msg("CONGRATULATIONS!");
        *win_count = -1;
        *loss_count = 0;
        return true;
    } else if (*loss_count == 5) {
        display_msg("UNLUCKY!");
        *win_count = -1;
        *loss_count = 0;
        return true;
    } else {
        *chosen = 0;
        *player = '0';
        *opponent = '0';
        return false;
    }
}


/* Loop to process the result
    @param counter indicates what stage the program is at
    @param player the players selection 
    @param opponent pointer to opponents selction
    @param chosen pointer to what value needs to be displayed in selection_loop*/
bool reset_loop(char* player, char* opponent, char* chosen)
{
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        *chosen = 0;
        *player = '0';
        *opponent = '0';
        return true;
    }
    return false;
    
}


int main (void) 
{

    initalise();
    int counter = 0;
    char player = '0';
    char opponent = '0';
    char chosen = 0;
    int win_count = -1;
    int loss_count = 0;
    display_msg("PUSH UP TO START");

    while (1)
    {
        pacer_wait();
        tinygl_update();
        
        if (counter==0) {
            if (start_loop()) {
                counter ++;
            }
        }
        
        if (counter == 1) {  
            if (select_character_loop(&player, &chosen)) {
                counter++;
            }
        }
        
        if (counter == 2) {
            if (send_recv_loop(&opponent, player)) {
                counter++;
            }
        }

        if (counter == 3) {
            if (process_result_loop(&win_count, &loss_count, &player, &opponent)) {
                counter++;
            }
        }

        if (counter == 4) {
            if (win_count_loop(&win_count, &loss_count, &player, &opponent, &chosen)) {
                counter++;
            } else {
                counter = 1;
            }
        }

        if (counter == 5) {
            if (reset_loop(&player, &opponent, &chosen)) {
                counter = 1;
            }
        }
    }
    return 0;
}

