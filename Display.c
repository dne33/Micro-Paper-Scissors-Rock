#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Ball.h"
#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "stdint.h"
#include "stdio.h"


void display_ball (Ball_t Ball)
{
    Ball.x = 3;
    Ball.y = 3;
    system_init ();
    pacer_init (500);
    for (size_t i = 0; i < 7; i++){
        pio_config_set (rows[i],PIO_OUTPUT_HIGH); 
    }
    for (size_t i = 0; i < 5; i++) {
        pio_config_set (cols[i],PIO_OUTPUT_HIGH); 
    }    
    while (1) {

        pio_output_low(row[Ball.x]);
        pio_output_low(cols[Ball.y]);
        pacer_wait()
        Ball.x++;
        pio_output_high(row[Ball.x-1]);

    }
}