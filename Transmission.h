#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <stdint.h>
#include "Ball.h"

typedef struct {
    Ball_t ball;
    int8_t start_finish;
} Packet_t;
void send_packet (Packet_t* Spacket);
Packet_t recv_packet (void);
void process_packet (Packet_t* Rpacket);
#endif