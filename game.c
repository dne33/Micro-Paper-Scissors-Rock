/** @file   game.c
    @author  Matt Lane, Daniel Neal
    @date    13 October 2022
    @brief   Rock,Paper,Scissors game
*/


#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "button.h"
#include "led.h"
#include "../fonts/font5x5_1.h"

/* Define pacer rate in Hz. */
#define PACER_RATE 500
#define MESSAGE_RATE 12



void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

void display_msg_no_esc(char* message) {
    bool displaying = true;
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_point_t point = {0,0};
    tinygl_draw_message(message, point, 1);\
    tinygl_update();

}

void display_msg(char* message) 
{
    bool displaying = true;
    
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(message);
    while (displaying) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
           displaying = false;
        }
    }
}


void win_counter(int win_count)
{
    tinygl_point_t point = {win_count,6};
    tinygl_pixel_set(point,1);
    tinygl_update();
}

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
        if (result == 'L') {
            display_msg("LOSER");
        } else if (result == 'W') {
            display_msg("WINNER");
            win_count++;
        } else if (result == 'D') {
            display_msg("DRAW");
        }
        tinygl_clear();
        result = '0';
    }
    return win_count;
}

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
        
        display_character (rps[index]);

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            player = rps[index];
            led_set(0,1);
            tinygl_clear();
            return player;
            
        }
        
        
    }
    return player;
}

int main (void)
{
    int counter = 0;
    int recv = 0;
    char player = '0';
    char opponent = '0';
    char ch = '0';
    int win_count = -1;
    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init ();
    button_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);
    
    
    while (1)
    {
        tinygl_update();
        button_update();
        pacer_wait();

        while(counter == 0) {
            display_msg_no_esc("PUSH UP TO START");
            counter++;
        }
        if (player == '0') {
            player = select_rps(player);
        }

        
        if (recv == 0) {
            if (ir_uart_read_ready_p ()) {
                ch = ir_uart_getc ();
                recv = 1;
                if (ch == 'R' || ch == 'P' || ch == 'S' ) {
                    opponent = ch;
                    ch = '0';
                } else {
                    ch = '0';
                    recv = 0;
                }
            } 
        }
        

        button_update();
        if (button_push_event_p(0)) {
            ir_uart_putc(player);
        }

        if (recv == 1) {
            if (player != '0' && opponent != '0') {
                ir_uart_putc(player);
                led_set(0,0);
                ir_uart_putc('X'); // Break up repetitive sending of rps 
                win_count = get_result(player, opponent,win_count);
                win_counter(win_count);
                if (win_count == 4) {
                    display_msg("CONGRATULATIONS!");
                    tinygl_clear();
                    win_count = 0;
                }
                counter = 0;
                recv = 0;
                player = '0';
                opponent = '0';
            }
        }
        
    }
    return 0;
    
}

