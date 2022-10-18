/** @file   game.h
    @author  Matt Lane, Daniel Neal
    @date    13 October 2022
    @brief   Rock,Paper,Scissors game
*/
#ifndef GAME_H
#define GAME__H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "button.h"
#include "led.h"
#include "../../fonts/font5x5_1.h"
#include "game_display.h"
#include "game_logic.h"


/**
 * @brief Initialisation functions
 */
static void initalise (void);

/**
 * @brief Looping the starting message until Navswitch North is pressed
 * @return boolean if navswitch up is pressed
 */
static bool start_loop (void);

/**
 * @brief Tidy up chosen being used as both an int and a char 
 * @param player player pointer to store the selected character in
 * @param chosen chosen pointer to put the current character into (if not selected)
 * @return boolean if the character is selected
 */
static bool select_character_loop (char* player, char* chosen);


/**
 * @brief Selecting RPS loop and only clears screen when chosen
 * @param player player pointer to store the selected character in
 * @param chosen chosen pointer to put the current character into (if not selected)
 * @return boolean if the character is selected
 */
static bool send_recv_loop (char* opponent, char player);



/**
 * @brief Loop to process the result
 * @param win_count pointer to number of wins the player has
 * @param loss_count pointer to number of losses the player has
 * @param player the players selection 
 * @param opponent pointer to opponents selction
 * @return boolean if navswitch up is pressed
 */   
static bool process_result_loop (int* win_count, int* loss_count, char* player, char* opponent);


/**
 * @brief Loop to process the result and check win and loss counters
 * @param win_count pointer to number of wins the player has
 * @param loss_count pointer to number of losses the player has
 * @param player the players selection 
 * @param opponent pointer to opponents selction
 * @param chosen pointer to what value needs to be displayed in selection_loop
 * @return boolean if the player needs to fully reset the game
 */
static bool win_count_loop (int* win_count, int*loss_count, char* player, char* opponent, char* chosen);


/** 
 * @brief Loop to process the result
 * @param player the players selection 
 * @param opponent pointer to opponents selction
 * @param chosen pointer to what value needs to be displayed in selection_loop
 * @return boolean if the navswitch is pressed up 
*/
static bool reset_loop (char* player, char* opponent, char* chosen);

/**
 * @brief main loop of all the different game states 
 * @return int 0
 */
int main (void);




#endif //GAME_LOOP