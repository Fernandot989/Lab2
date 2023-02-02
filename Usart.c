#include "Usart.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000

void usart(uint8_t sinc, uint8_t brgh, uint8_t brg16, uint8_t spbrg, 
                uint8_t spbrgh, uint8_t spen, uint8_t rx9, uint8_t cren,
                uint8_t txen, uint8_t tx9){
    
    TXSTAbits.SYNC = sinc;  
    TXSTAbits.BRGH = brgh;  
    BAUDCTLbits.BRG16 = brg16; 
    
    SPBRG  = spbrg;
    SPBRGH = spbrgh;
    
    RCSTAbits.SPEN = spen; 
    RCSTAbits.RX9  = rx9; 
    RCSTAbits.CREN = cren; 
    
    TXSTAbits.TXEN = txen; 
    TXSTAbits.TX9  = tx9;   
}