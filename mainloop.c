void init_PSR (void) 
{

}

void reset_PSR (void) 
{

}

void determine_result (void) 
{

}

/**
 * @brief Encode a message of RPS 
 * (as opposed to being within 1 to 2 bit errors of eachother)
 *  
 * 
 * @param message RPS
 * @return char Encoded RPS
 */
char encode_message (char message) 
{
    //encode?
    return message;
}

/**
 * @brief  Decode and encoded RPS
 * 
 * @param message Encoded message
 * @return char Decoded message RPS
 */
char decode_message (char message) 
{
    //decode?
    return message;
}

/**
 * @brief send and/or receive transmission of RPS
 * 
 */
void send_recv_RPS (void) 
{
    if ("not game over and ready to recv") {
        char recv_msg;
        recv_msg = decode_message(ir_uart_getc ());
        if (recv_msg!=ROCK&&recv_msg!=PAPER&&recv_msg!=SCISSORS) {
            //assign selection
            recv_msg = "!"; //"!"" == not received correctly 
        }
    }
    if ("not game over and have char to send") {
        ir_uart_putc(encode_message(send_msg));
    }



}