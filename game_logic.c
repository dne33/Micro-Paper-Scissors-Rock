#include "game_logic.h"

/* Returns the result of a RPS Battle.
    @param player character representaion of players choice
    @param opponent character representaion of opponents choice */
char get_result(char player, char opponent) 
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
        return result;
    }
    return '0';
}

/* Allows selection of Rock,Paper, or Scissors.
    @param player character representaion of players choice
    @param index  the index of the rps array to display */
char select_rps(char player, int index) 
{
    char rps[3] = {'R', 'P', 'S'};
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        if (index == 0) {
            index = 2;
        } else {
            index--;
        }
    }
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        if (index == 2) {
            index = 0;
        } else {
            index++;
        } 
    }
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        player = rps[index];
        return player;
    }
    return index;
}