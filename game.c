/** @file   game.c
    @author  Matt Lane, Daniel Neal
    @date    13 October 2022
    @brief   Rock,Paper,Scissors game
*/

#include "game.h"

/**
 * @brief Initialisation functions
 */
void initalise (void)
{
    system_init ();
    ir_uart_init ();
    button_init ();
    navswitch_init ();
    pacer_init (PACER_RATE);

} 

/**
 * @brief Looping the starting message until Navswitch North is pressed
 * @return boolean if navswitch up is pressed
 */
bool start_loop (void)
{
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        tinygl_clear ();
        return true;
    }
    return false;

}

/**
 * @brief Selecting RPS loop and only clears screen when chosen
 * @param player player pointer to store the selected character in
 * @param chosen chosen pointer to put the current character into (if not selected)
 * @return boolean if the character is selected
 */
bool select_character_loop (char* player, char* chosen )
{
    *chosen = select_rps (*player, *chosen); 
    if  (*chosen == 0) {
        display_character ('R');
    } else if (*chosen == 1) {
        display_character ('P');
    } else if (*chosen == 2) {
        display_character ('S');
    } else { // Player has "Locked in" their choice 
        *player = *chosen;
        led_set (0,1);
        tinygl_clear ();
        tinygl_update ();
        return true;
    }
    return false;

}


/**
 * @brief Allows for users to press a button to transmit selections.
 * @param opponent poointer to opponents selction
 * @param player the players selection
 * @return boolean if the player has both sent and recieved a char
 */
bool send_recv_loop (char* opponent, char player)
{
    static int sending = 0;
    static char ch = '0';
    navswitch_update ();
    button_update ();
    if (ir_uart_read_ready_p ()) {
        ch = ir_uart_getc ();
        if (ch == 'R' || ch == 'P' || ch == 'S' ) {
            if (ir_uart_write_ready_p ()) { // Ensure both layers have sent and recv 
                ir_uart_putc (player);
                *opponent = ch;
                ch = '0';
                return true;
            }
        }
    }

    if (button_push_event_p (0) || sending == 1) {
        if (ir_uart_write_ready_p ()) {
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
 * @param win_count pointer to number of wins the player has
 * @param loss_count pointer to number of losses the player has
 * @param player the players selection 
 * @param opponent pointer to opponents selction
 * @return boolean if navswitch up is pressed
 */   
bool process_result_loop (int* win_count, int* loss_count, char* player, char* opponent)
{
    static char result = '0';
    navswitch_update ();
    led_set (0,0);
    if (result == '0') {
        result = get_result (*player, *opponent);
        if (result == 'L') {
            display_msg ("LOSER");
            *loss_count = *loss_count + 1;
        } else if (result == 'W') {
            display_msg ("WINNER");
            *win_count = *win_count + 1;
        } else if (result == 'D') {
            display_msg ("DRAW");
        } 
        tinygl_update ();
    } else {
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            result = '0';
            tinygl_clear ();
            return true;
        }
    }
    return false;
}

/**
 * @brief Loop to process the result and check win and loss game_states
 * @param win_count pointer to number of wins the player has
 * @param loss_count pointer to number of losses the player has
 * @param player the players selection 
 * @param opponent pointer to opponents selction
 * @param chosen pointer to what value needs to be displayed in selection_loop
 * @return boolean if the player needs to fully reset the game
 */
bool win_count_loop (int* win_count, int*loss_count, char* player, char* opponent, char* chosen)
{
    ir_uart_putc ('X');
    win_game_state (*win_count);
    if (*win_count == 4) {
        display_msg ("CONGRATULATIONS!");
        *win_count = -1;
        *loss_count = 0;
        return true;
    } else if (*loss_count == 5) {
        display_msg ("UNLUCKY!");
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


/** 
 * @brief Loop to process the result
 * @param player the players selection 
 * @param opponent pointer to opponents selction
 * @param chosen pointer to what value needs to be displayed in selection_loop
 * @return boolean if the navswitch is pressed up 
*/
bool reset_loop (char* player, char* opponent, char* chosen)
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

/**
 * @brief main loop of all the different game states 
 * @return int 0
 */
int main (void) 
{
    initalise ();
    int game_state = 0;
    char player = '0';
    char opponent = '0';
    char chosen = 0;
    int win_count = -1;
    int loss_count = 0;
    display_msg ("PUSH UP TO START");

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        if (game_state==0) { // Initial screen
            if (start_loop ()) {
                game_state ++;
            }
        }
        if (game_state == 1) { //selecting a character
            if (select_character_loop (&player, &chosen)) {
                game_state++;
            }
        }
        if (game_state == 2) { // sending and recieving chosen characters
            if (send_recv_loop (&opponent, player)) {
                game_state++;
            }
        }
        if (game_state == 3) { // process a win/loss/draw
            if (process_result_loop (&win_count, &loss_count, &player, &opponent)) {
                game_state++;
            }
        }

        if (game_state == 4) { // Check win/loss counter for overall win/loss
            if (win_count_loop (&win_count, &loss_count, &player, &opponent, &chosen)) {
                game_state++;
            } else {
                game_state = 1;
            }
        }

        if (game_state == 5) { /*If overall win/loss occurs reset fully 
                                and allow for one more text scroll*/ 
            if (reset_loop (&player, &opponent, &chosen)) {
                game_state = 1;
            }
        }
    }
    return 0;
}

