#include "communication.h"
#include "util_comm.h"
#include <string.h>
#include <stdio.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
     /* TODO
     * Send the encoding of the characters: R, I, C, K
     */

    send_squanch('R' - 64);
    send_squanch('I' - 64);
    send_squanch('C' - 64);
    send_squanch('K' - 64);
}

void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */
    
    for (uint8_t i = 0; i <= 4; i++) {
        char c = recv_squanch () + 64;
        fprintf(stdout, "%c", c);
    }
}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */

    for (uint8_t i = 0; i <= 9; i++) {
       char c = recv_squanch ();
       send_squanch (c);
       send_squanch (c);
    }
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{
     /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */
    
    char hello[10] = "HELLOTHERE";
    uint8_t lungime = strlen(hello);
    lungime = lungime << 4;
    lungime = lungime >> 2;
    send_squanch(lungime);

    for (uint8_t i = 0; i <strlen(hello); i++) 
        send_squanch(hello[i] - 64);
}

void recv_message(void)
{
     /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */
    
    uint8_t lungime;
    lungime = recv_squanch (); 
    lungime = lungime << 2;
    lungime = lungime >> 4;
    // reversing the encoding used at send_message
    
    fprintf(stdout, "%hhd", lungime);

    for (uint8_t i = 1; i <= lungime; i++) {
        char c = recv_squanch () + 64;
        fprintf(stdout, "%c", c);
    }
}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */

    char msg1[15] = "PICKLERICK";
    char msg2[15] = "VINDICATORS";
    char mesaj[15];
    uint8_t lungime_primita = recv_squanch (); 
    uint8_t c;

    lungime_primita = lungime_primita << 2;
    lungime_primita = lungime_primita >> 4;

    for (uint8_t i = 0; i < lungime_primita; i++)
        c = recv_squanch (); 
        
    switch (c) {
        case (16) : 
            strcpy(mesaj, msg1); 
            // mesajul este PICKLERICK daca caracterul este P (16)
            break;
        default :
            strcpy(mesaj, msg2); 
            // mesajul este VINDICATORS pentru orice alt caracter
    }  

    uint8_t lungime; 
    lungime = strlen(mesaj);
    lungime = lungime << 4;
    lungime = lungime >> 2;
    send_squanch (lungime);

    // length encoding 

    for (uint8_t i = 0; i < strlen(mesaj); i ++)
        send_squanch(mesaj[i] - 64);

    // sending the encoded message
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */

    uint8_t current_bit_1;
    uint8_t current_bit_2;
    uint8_t k = 0; 
    uint8_t c3 = 0;

    for (uint8_t i = 0; i <= 3; i++) {
        current_bit_1 = ((c1 >> i) & (uint8_t) 1) << (k+1); 

        current_bit_2 = ((c2 >> i) & (uint8_t) 1) << k; 

        c3 = c3 | current_bit_1; 
        c3 = c3 | current_bit_2; 

        k = k + 2; 
    }
    send_squanch(c3);

}
uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */

    uint8_t k = 0;
    uint8_t current_bit_1;
    uint8_t current_bit_2;
    res = 0;

        for(uint8_t i = 0; i <= 6; i += 2) {

            current_bit_1 = (c >> (i+1)) & 1;
            current_bit_2 = (c >> i) & 1; 
            res = res | (current_bit_2 << k); 
            res = res | (current_bit_1 << (k+4));
            k++; 
        }

    return res;
}
