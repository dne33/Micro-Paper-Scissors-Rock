#ifndef DISPLAY_H
#define DISPLAY_H
#include "Ball.h"
#include "system.h"
#include "pio.h"
#include "pacer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include "paddle.h"

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

void display_ball (Ball_t Ball);

void display_paddel (Paddle_t paddle);
#endif