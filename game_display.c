
#include "game_display.h"

/* Display single character.
    @param character the charater to be displayed */
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/* Display string on loop. 
    @param message the string to be displayed*/
void display_msg(char* message) 
{
    tinygl_init(PACER_RATE);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text(message);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    
}

/* Display the win count using a row of LED.
    @param win_count current number of wins by player */
void win_counter(int win_count)
{
    tinygl_point_t point = {win_count,6};
    tinygl_pixel_set(point,1);
    tinygl_update();
}
