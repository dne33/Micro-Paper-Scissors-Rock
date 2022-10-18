/** @file   game_logic.h
    @author  Matt Lane, Daniel Neal
    @date    13 October 2022
    @brief   Rock,Paper,Scissors game
*/

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "system.h"
#include "navswitch.h"

/**
 * @brief Allows selection of Rock,Paper, or Scissors
 * @param player character representaion of players choice
 * @param index  the index of the rps array to display 
 * @return Either the player or the index of the RPS to be displayed
 */
char get_result (char player, char opponent);

/**
 * @brief Allows selection of Rock,Paper, or Scissors
 * @param player character representaion of players choice
 * @param index  the index of the rps array to display 
 * @return Either the player or the index of the RPS to be displayed
 */
char select_rps (char player, int index);

#endif //GAME_LOGIC

