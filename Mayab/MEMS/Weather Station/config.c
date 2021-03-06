#include <pic18f4550.h>
#include "config.h"
#include "LCD.h"
#include "globalDefinitions.h"

void configPIC(){
    
    // CONFIGURATION BITS
        // CONFIG1L
        #pragma config PLLDIV = 1               // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
        #pragma config CPUDIV = OSC1_PLL2       // System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])

        // CONFIG1H
        #pragma config FOSC = HSPLL_HS          // Oscillator Selection bits (EC oscillator, CLKO function on RA6 (EC))
        #pragma config FCMEN = OFF              // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)

        // CONFIG2L
        #pragma config BORV = 3                 // Brown-out Reset Voltage bits (Minimum setting 2.05V)

        // CONFIG2H
        #pragma config WDT = OFF                // Watchdog Timer Enable bit (WDT enabled)

        // CONFIG3H
        #pragma config MCLRE = ON               // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

        // CONFIG4L
        #pragma config LVP = OFF                // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
    
    
    //AD Converter Configuration
        ADCON0 = 0b00000000;    // Turning the ADCON0 OFF
        ADCON1 = 0b00001101;    // Unimplemented x2
                                // Using VSS (0 V) as Vref-
                                // Using VDD (4.875 V) as Vref+
                                // Setting 2 analog and 11 digital ports x4
        ADCON2 = 0b10110110;    // Right Justified
                                // Unimplemented
                                // 16 TAD x3
                                // FOSC/64 x3 
        
    // Interruptions
        INTCONbits.GIE = 1;
        INTCONbits.PEIE_GIEL = 1;
        INT0IE = 1;
        INT0IF = 0;
        ADIE = 1;
        ADIF = 0;
    
    // Input/Output Settings
        TRISA = 0b00000111; // Setting pins of PORT A as Inputs/Outputs
        TRISB = 0b11111111; // Setting pins of PORT B as Inputs/Outputs
        TRISC = 0b00000000; // Setting pins of PORT C as Inputs/Outputs
        TRISD = 0b00000000; // Setting pins of PORT D as Inputs/Outputs
        TRISE = 0b00000000; // Setting pins of PORT E as Inputs/Outputs
    
    // Timer Settings
        T0CON = 0b01000001; // Setting the Timer for the wait_ms function
        
}

void wait_us(unsigned int time){
    char count;
    T0CON = 0b01000000;
    count = time * 2;
    TMR0L = 255 - count;
    T0CONbits.TMR0ON = _ON;
    while(T0IF == 0);
    T0CONbits.TMR0ON = _OFF;
    T0IF = 0;
}

void wait_ms(unsigned int time){
    T0CON = 0b01000001;
    for(unsigned int i = 0; i < time; i++){
        unsigned int count = 0;
        TMR0L = 131;
        T0IF = 0;
        T0CONbits.TMR0ON = _ON;
        while (count < 24){
            while (T0IF == 0);
            count++;
            T0IF = 0;
            TMR0L = 131;
        }
        T0CONbits.TMR0ON = _OFF;
    }
}

void wait_secs(unsigned int time){
    for(int j = 0; j < time; j++){
        wait_ms(1000);
    }
}

void convertAtoD(unsigned int channel){
    ADCON0bits.ADON = _ON;      // Turning the AD Converter ON
    __delay_us(10);              // 
    ADCON0bits.CHS = channel;    // Assign the channel to convert
    ADCON0bits.GO = 1;        // Starting the AD Conversion
}

void beep_on(){
    BUZZER = _ON;
}

void beep_off(){
    BUZZER = _OFF;
}