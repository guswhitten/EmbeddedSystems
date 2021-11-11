/*
This code generates a PWM signal with 500 ms period and 10% duty cycle.
TACCR1 is chosen to select duty cycle   (Duty cycle = TACCR1 / TACCR0 * 100)
TACCR0 is chosen to select period       (TACCR0 = F * T / D - 1)

*/ 
#include "msp430G2553.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;               // Stop WDT
     P1DIR |= 0x40;                         // P1.6 pin set to make red LED output
     P1OUT = 0x00;                          // clear P1OUT register
     P1SEL |= BIT6;                         // selects which pin to modulate using the PWM (in this case p1.6)
     TACCR0 = 62499;                        // sets PWM Time Period/ frequency (1 KHz)
     TACCTL1 = OUTMOD_7;                    // reset/set mode 7 for output signal
     TACCR1 = 6250;                         // TACCR1 / TACCR0 = Duty Cycle (6250 / 62499 = 0.1 = 10%)
     TACTL = TASSEL_2 + MC_1 + ID_3;        // selects SMCLK (1 MHz) and Up Mode
    
     while(1){
         P1OUT ^= BIT6;                     // repeatedly blinks red led with modulated signal (p1.6)
     }
}

// result --> https://youtu.be/ZWwsvIdafrg
