#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "button.h"
#include "led.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

void display_msg(char* message) {
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
void get_result(char player, char opponent) {
    char result;
    if (opponent == player) {
        result = 'D';
    }
    else if (player == 'S' && opponent == 'R')
    {
        result = 'L';
    }
    else if (player == 'S' && opponent == 'P')
    {
        result = 'W';
    }
    else if (player == 'R' && opponent == 'P')
    {
        result = 'L';
    }
    else if (player == 'R' && opponent == 'S')
    {
        result = 'W';
    }
    else if (player == 'P' && opponent == 'R')
    {
        result = 'W';
    }
    else if (player == 'P' && opponent == 'S')
    {
        result = 'L';
    }
    if (result != '0')
    {
        if (result == 'L') {
            display_msg("loser");
        } else if (result == 'W') {
            display_msg("winner");
        } else {
            display_msg("draw");
        }
    }
}

int main (void)
{
    int counter = 0;
    int index = 0;
    char rps[3] = {'R', 'P', 'S'};
    char player = '0';
    char opponent = '0';
    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init ();
    button_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);
    
    
    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        if (counter == 0) {
            display_msg("SELECT: Rock Paper Scissors");
        }
        if (counter == 0) {
            counter ++;
        }
           
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
        }
        

        if (ir_uart_read_ready_p ()) {
            char opponent;
            char result;
            char ch;
            ch = ir_uart_getc ();
            if (ch == 'R' || ch == 'P' || ch == 'S' ) {
                opponent = ch;
            } 
        } 
        button_update();
        if (button_push_event_p(0)) {
            ir_uart_putc(rps[index]);
        }
        if (player != '0' && opponent != '0') {
            ir_uart_putc(rps[index]);
            get_result(player, opponent);
        }
        display_character (rps[index]); 
    }
    return 0;
    
}

