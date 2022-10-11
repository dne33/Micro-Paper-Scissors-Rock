#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "Display.h"
#include "Ball.h"

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "stdint.h"
#include "stdio.h"




void display_ball (Ball_t Ball)
{
    system_init();
    pacer_init(1);
    for (size_t i = 0; i < 7; i++){
        pio_config_set (rows[i],PIO_OUTPUT_HIGH); 
    }
    for (size_t i = 0; i < 5; i++) {
        pio_config_set (cols[i],PIO_OUTPUT_HIGH); 
    }    
    while (1)
    {
        pio_output_low(rows[Ball.x]);
        pio_output_low(cols[Ball.y]);
        pacer_wait();
        pio_output_high(rows[Ball.x]);
        pio_output_high(cols[Ball.y]);
        Ball.y--;
    }
    


}