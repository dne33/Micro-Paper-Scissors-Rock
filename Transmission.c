#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Ball.h"
#include "Transmission.h"


uint8_t encode_packet (Packet_t* Spacket) {
    uint8_t packet = 0;
        packet += (((Spacket->ball).x));
        packet = packet << 2;
        packet += (((Spacket->ball).v));
        packet = packet << 2;
        packet += ((Spacket->start_finish));
    return packet;
    }

void send_packet (Packet_t Spacket) 
{
    /**
     * @brief decodes an integer recieved and turns it into a Packet_t
     * 
     * @param num_recv 
     */
    void decode_num (uint8_t num_recv) {
        printf("START: %d\n", ((1 << 2)-1) & num_recv);
        printf("V: %d\n", ((1 << 2)-1) & (num_recv>>2));
        printf("X: %d\n", ((1 << 3)-1) & (num_recv>>4));
    }

// void send_packet (Packet_t* Spacket) 
// {
//     //code here to send the packet through the IR
// }

// Packet_t recv_packet (void)
// {
//     //code here for recieveing packet from IR
// }

// void process_packet (Packet_t* Rpacket)
// {
//     //process information within packet and all appropriate functions
// }

