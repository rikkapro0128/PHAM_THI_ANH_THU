#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000
#include <xc.h>
// pre = 1
void xung1() {
    TRISC2 = 1;
    TRISC1 = 1;
    TMR2 = 0;
    PR2 = 124;
    CCPR1L = 50;
    CCP1CON = 0x0C;
    CCP2CON = 0x00;
    DC1B1 = 0;
    DC1B0 = 0;
    TRISC2 = 0;
    TRISC1 = 0;
    RC1 = 0;
    T2CON = 0x00;
    T2CKPS1 = 0;
    T2CKPS0 = 0;
    TMR2ON = 1;
}

void xung2() {
    TRISC2 = 1;
    TRISC1 = 1;
    TMR2 = 0;
    PR2 = 124;
    CCPR2L = 100;
    CCP2CON = 0x0C;
    CCP1CON = 0x00;
    DC2B1 = 0;
    DC2B0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    RC2 = 0;
    T2CON = 0x00;
    T2CKPS1 = 0;
    T2CKPS0 = 0;
    TMR2ON = 1;
}

void main(void) {
    ANSEL = ANSELH = 0;
    TRISB = WPUB = 0x07;
    nRBPU = TRISD0 = 0;
    RD0 = 1;
    while(1) { 
        if(!RB0) {
            while(!RB0);
            xung1(); 
        }else if(!RB1) {
            while(!RB1);
            xung2();
        }
    }
}
