#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "paddle.h"

/**
 * @brief Get the paddle pos object
 * 
 * @param paddle pointer to paddle struct
 * @return int8_t paddle position
 */
int8_t get_paddle_pos (Paddle* paddle) 
{
    return paddle->pos
}

/**
 * @brief Initialise paddle object at the start point (4)
 * 
 * @param paddle pointer to paddle struct
 */
void init_paddle (Paddle* paddle) 
{
    paddle->pos = START;
}

/**
 * @brief Move the paddle left if possible
 * 
 * @param paddle pointer to paddle struct
 */
void move_paddle_left (Paddle* paddle)
{
    if (paddle->pos > LEFT_LIM) {
        paddle_pos--;
    }
}

/**
 * @brief Move the paddle right if possible
 * 
 * @param paddle pointer to paddle struct
 */
void move_paddle_right (Paddle* paddle) 
{
    if (paddle->pos > RIGHT_LIM) {
        paddle_pos--;
    }
}



