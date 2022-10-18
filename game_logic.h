/** @file   game_logic.h
    @author  Matt Lane, Daniel Neal
    @date    13 October 2022
    @brief   Rock,Paper,Scissors game
*/

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "system.h"
#include "navswitch.h"

/* Returns the result of a RPS Battle.
    @param player character representaion of players choice
    @param opponent character representaion of opponents choice */
char get_result(char player, char opponent);

/* Allows selection of Rock,Paper, or Scissors.
    @param player character representaion of players choice
    @param index  the index of the rps array to display */
char select_rps(char player, int index);

#endif //GAME_LOGIC

