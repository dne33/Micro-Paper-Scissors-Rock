#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x5_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

/* Display single character.
    @param character the charater to be displayed */
void display_character (char character);

/* Display string on loop. 
    @param message the string to be displayed*/
void display_msg(char* message);

/* Display the win count using a row of LED.
    @param win_count current number of wins by player */
void win_counter(int win_count);

#endif //DISPLAY_H