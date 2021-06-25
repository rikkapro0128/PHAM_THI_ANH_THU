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
#include "lcd.h"

unsigned int i = 0, reload = 0;

void main(void) {
    ANSEL = ANSELH = 0;
    TRISB = WPUB = 0x01;
    nRBPU = 0;
    GIE = 1;
    INTF = 0;
    INTE = 1;
    INTEDG = 1;
    const char ten[] = {'P', 'h', 0x00, 'm', ' ', 'T', 'h', 0x01 , ' ', 'A', 'n', 'h', ' ', 'T', 'h', 0x02};
    const char thongtin[] = {0x03, 'H', 'V', 'T', '1', '5', 'B', '-', '1', '9', '5', '1', '7', '1', '7', '1'};
    const char kytu_1[] 
    = {
        0, 12, 18, 18, 15, 0, 4, 0,// aj 0x00
        4, 0, 4, 4, 4, 0, 4, 0,// ij 0x01
        3, 1, 18, 18, 18, 18, 12, 0,// uw 0x02   
        14, 9, 9, 29, 9, 9, 14, 0, // DD 0x03
        0X99
    };
    i = 0;
    lcd_init();
    lcd_put_byte(0, 0x40);
    while(lcd_busy());
    while(kytu_1[i] != 0x99) {
        lcd_put_byte(1, kytu_1[i]);
        while(lcd_busy());
        i++;
    }
    lcd_putc('\f');
    lcd_gotoxy(0, 0);
    for(i = 0; i < 16; i++) {
        lcd_putc(ten[i]);
    }
    lcd_gotoxy(0, 1);
    for(i = 0; i < 16; i++) {
        lcd_putc(thongtin[i]);
    }
    while(1) {
        if(reload) {
            break;
        }
    };
}

void __interrupt() myIsr() {
    INTF = 0;
    const char line_1[] = {'T', 'h', 'i', ' ', 'k', 0x00, 't', ' ', 't', 'h', 0x01, 'c', ' ', 'm', 0x02, 'n'};
    const char line_2[] = {'L', 0x03, 'p', ' ', 'T', 'r', 0x04, 'n', 'h', ' ', 'N', 'g', 0x05, 't'}; 
    const char kytu_2[] 
    = {
        1, 5, 10, 4, 10, 12, 7, 0, // ees 0x00
        2, 4, 0, 18, 18, 18, 12, 0, // us 0x01
        12, 18, 0, 12, 18, 18, 12, 0, // oo 0x02
        12, 18, 12, 18, 15, 0, 4, 0, // aaj 0x03
        10, 1, 8, 8, 8, 0, 8, 0, // if 0x04
        0, 21, 10, 0, 12, 20, 15, 0, // aws 0x05
        0X99
    };
    i = 0;
    lcd_init();
    lcd_put_byte(0, 0x40);
    while(lcd_busy());
    while(kytu_2[i] != 0x99) {
        lcd_put_byte(1, kytu_2[i]);
        while(lcd_busy());
        i++;
    }
    lcd_putc('\f');
    lcd_gotoxy(0, 0);
    for(i = 0; i < 16; i++) {
        lcd_putc(line_1[i]);
    }
    lcd_gotoxy(1, 1);
    for(i = 0; i < 14; i++) {
        lcd_putc(line_2[i]);
    }
    __delay_ms(2000);
    reload = 1;
}
