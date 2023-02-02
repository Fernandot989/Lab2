#ifndef Usart_H
#define	Usart_H

#include <xc.h> 
#include <stdint.h>

void usart ( uint8_t sinc, uint8_t brgh, uint8_t BRG16, uint8_t spbrg, 
                uint8_t spbrgh, uint8_t spen, uint8_t rx9, uint8_t cren,
                uint8_t txen, uint8_t tx9);


#endif