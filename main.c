/******************************************************************
Universidad del Valle de Guatemala
IE2023 Programación de Microcontroladores
Autor: Fernando Donis
Compilador: XC8, MPLAB X IDE (v6.00)
Proyecto: Laboratorio 2
Hardware: PIC16F887
Creado: 26/01/2023
Última Modificación: 01/02/2023
******************************************************************/

#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RB5
#define D6 RD6
#define D7 RD7

float vADC;
uint16_t valADC, portEs, a = 1;
int ce, de, u;
char unid, decen, cent;


#include "LCD.h"
#include "LCD8.h"
#include "ADC_config.h"
#include "ADC_read.h"
#include "Usart.h"

void portconfi(void);
char intachar(uint8_t n);
uint8_t deshacer(int p, uint16_t n);
uint16_t map(uint8_t v, uint8_t minen, uint8_t maxen, uint8_t minsa,uint16_t maxsa);

void __interrupt() isr (void)
{    
    if(PIR1bits.RCIF){
        portEs = RCREG;
        if(portEs == '+'){
            a = a++;
        }
        else if(portEs == '-'){
            a = a--;
        }
        else{
            a = a;
        }
    }
}

void main(void) {
  TRISD = 0x00;
  Lcd8_Init();
  Lcd8_Clear();
  portconfi();
  Lcd8_Set_Cursor(1,2);
  Lcd8_Write_String("S1: S2: S3:");
  while(1)
  {
    valADC = ADC_read (0x00000000);
    
    vADC = map(valADC, 0, 255, 0, 500);
    unid = intachar(deshacer(2, vADC));
    Lcd8_Set_Cursor(2,1);
    Lcd8_Write_Char(unid);
    Lcd8_Set_Cursor(2,2);
    Lcd8_Write_String(".");
    decen = intachar(deshacer(1, vADC));
    Lcd8_Set_Cursor(2,3);
    Lcd8_Write_Char(decen);
    cent = intachar(deshacer(0, vADC));
    Lcd8_Set_Cursor(2,4);
    Lcd8_Write_Char(cent);
    __delay_ms(5);
  
    valADC = ADC_read (0x00000001);
    
    vADC = map(valADC, 0, 255, 0, 500);
    unid = intachar(deshacer(2, vADC));
    Lcd8_Set_Cursor(2,6);
    Lcd8_Write_Char(unid);
    Lcd8_Set_Cursor(2,7);
    Lcd8_Write_String(".");
    decen = intachar(deshacer(1, vADC));
    Lcd8_Set_Cursor(2,8);
    Lcd8_Write_Char(decen);
    cent = intachar(deshacer(0, vADC));
    Lcd8_Set_Cursor(2,9);
    Lcd8_Write_Char(cent);
    __delay_ms(5);
    
    ce = (a/100);
    Lcd8_Set_Cursor(2,11);
    Lcd8_Write_Char(ce);
    Lcd8_Set_Cursor(2,12);
    Lcd8_Write_String(".");
    Lcd8_Set_Cursor(2,13);
    de = (a%100);
    Lcd8_Write_Char(de);
    Lcd8_Set_Cursor(2,14);
    u = (de%10);
    Lcd8_Write_Char(u);
    __delay_ms(5);
    
    return;
    }
}

void portconfi(void){

    TRISB = 0b11000000;
    PORTB = 0b11000000;
    INTCONbits.GIE = 1;      
    INTCONbits.RBIE = 1;    
    INTCONbits.RBIF = 0;    
    IOCB = 0b11000000;      
    WPUB = 0b11000000;   
    OPTION_REGbits.nRBPU = 0; 
    
    TRISD = 0;
    PORTD = 0;
    TRISC = 0;
    PORTC = 0;
    
    usart(0,1,1,25,0,1,0,1,1,0);
    
}

char intachar(uint8_t n){
    if(n == 0){
        return '0';
    }
    else if(n == 1){
        return '1';
    }
    else if(n == 2){
        return '2';
    }
    else if(n == 3){
        return '3';
    }
    else if(n == 4){
        return '4';
    }
    else if(n == 5){
        return '5';
    }
    else if(n == 6){
        return '6';
    }
    else if(n == 7){
        return '7';
    }
    else if(n == 8){
        return '8';
    }
    else if(n == 9){
        return '9';
    }
}

uint8_t deshacer(int p, uint16_t nume){
    uint8_t cente;
    uint8_t dec;
    uint8_t uni;
    cente = (nume/100);
    dec = (nume%100);
    uni = (dec%10);
    if(p == 2){
        return cente;
    }
    else if(p == 1){
        return (dec/10);
    }
    else if (p == 0){
        return uni;
    }  
    
}


uint16_t map(uint8_t v, uint8_t minen, uint8_t maxen, uint8_t minsa,uint16_t maxsa){
    uint16_t resultado;
    resultado = (((maxsa-minsa)* (long long)(v-minen))/maxen)+minsa;
    return resultado;
}