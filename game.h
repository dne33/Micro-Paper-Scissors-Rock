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


/* Looping the starting message until Navswitch North is pressed*/
bool start_loop(void);


/* Loop for selecting R,P,or S
    @param player the players selection
    @param chosen pointer to what value needs to be displayed in selection_loop*/
bool select_character_loop(char* player, char* chosen);


/* Loop to send and recieve
    @param counter indicates what stage the program is at
    @param recv  pointer to indicate if the opponents selection has been stored
    @param opponent poointer to opponents selction
    @param ch a pointer to a temporary storage of incoming IR chararacters
    @param player the players selection */
bool send_recv_loop(char* opponent, char player);


/* Loop to process the result
    @param counter indicates what stage the program is at
    @param result pointer to if the player won or lost
    @param win_count pointer to number of wins the player has
    @param player the players selection 
    @param opponent pointer to opponents selction*/
bool process_result_loop(int* win_count, int* loss_count, char* player, char* opponent);


/* Loop to control the win count
    @param counter indicates what stage the program is at
    @param win_count pointer to number of wins the player has
    @param player the players selection 
    @param opponent pointer to opponents selction
    @param chosen pointer to what value needs to be displayed in selection_loop*/
bool win_count_loop(int* win_count, int*loss_count, char* player, char* opponent, char* chosen);


/* Loop to process the result
    @param counter indicates what stage the program is at
    @param player the players selection 
    @param opponent pointer to opponents selction
    @param chosen pointer to what value needs to be displayed in selection_loop*/
bool reset_loop(char* player, char* opponent, char* chosen);


/*Initalise all components need to run the game*/
void initalise (void);


#endif //GAME_LOOP