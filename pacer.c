#include <avr/io.h>
#include "pacer.h"
#define CPU_F 8000000
#define TIMER1_PRESCALE 1024

static uint16_t pacer_period;

/* Initialise the pacer module.  */
void pacer_init (uint16_t pacer_frequency)
{
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;
    uint16_t tick = ((500/pacer_frequency)*(CPU_F/TIMER1_PRESCALE)/1000);
    pacer_period = tick;
    
    /* TODO: initialise timer/counter peripheral the
       same way as in lab2/lab2-ex2/timer.c but also calculate 
       the timer/counter value from the pacer frequency */
}


/* Pace a while loop.  */
void pacer_wait (void)
{
    while (TCNT1 < pacer_period) {
        continue;
    }
    TCNT1 = 0x00;
    /* TODO: Implement the same way as the timer_delay () function 
       lab2-except reset TCNT1 after the while loop. */

}
