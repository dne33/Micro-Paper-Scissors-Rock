#include "system.h"
#include "navswitch.h"

/* Returns the result of a RPS Battle. */
int get_result(char player, char opponent,int win_count) 
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
}

/* Allows selection of Rock,Paper, or Scissors.*/
char select_rps(char player) 
{
    int index = 0;
    char rps[3] = {'R', 'P', 'S'};

    while (player == '0') {
        tinygl_update ();
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
            led_set(0,1);
            tinygl_clear();
            return player;
            
        }
        return 'X';
        
    }
    return player;
}