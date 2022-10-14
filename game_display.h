#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include "system.h"

/* Display Single Character. */
void display_character (char character);
/* Display string on loop until Navswitch UP is pressed. */
void display_msg(char* message);
/* Display thr win counter. */
void win_counter(int win_count);

#endif //DISPLAY_H