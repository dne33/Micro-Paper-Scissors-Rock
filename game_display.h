#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x5_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

/* Display Single Character. */
void display_character (char character);
/* Display string on loop until Navswitch UP is pressed. */
bool display_msg(char* message);
/* Display thr win counter. */
void win_counter(int win_count);

#endif //DISPLAY_H