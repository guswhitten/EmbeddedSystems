/*
This code generates a PWM signal using hardware components and an interrupt
*/
#include "msp430G2553.h"
#define BUTTON1 BIT1
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop WDT
    P1DIR |= BIT6;                              // P1.6 to output
    P1SEL |= BIT6;                              // P1.6 to TA0.1
    P1SEL2 &= ~BIT6;                            // P1.6 to TA0.1
    P1REN |= BUTTON1;                           // Enables resistor
    P1OUT |= BUTTON1;                           // Pull-up Resistor
    P1IE |= BUTTON1;                            // Enables interrupt
    P1IES |= ~BUTTON1;                          // Falling edge select
    P1IFG &= ~BUTTON1;                          // Clears any flags
    TA0CTL = TASSEL_2 + MC_1+ID_3;              //+TACLR;
    TA0CCR0 = 32768;                            // Set maximum count value (PWM Period)
    TA0CCR1 = 6554;                             // initialise counter compare value (PWM duty cycle)
    TA0CCTL1 = OUTMOD_7;                        // PWM set to reset
    _enable_interrupts();                       // Enter LPM0
}
#pragma vector=PORT1_VECTOR // Button interrupt
__interrupt void Port_1(void) {
 P1OUT ^=BIT6;
 P1IFG &= ~BUTTON1;
}


// result --> https://youtu.be/Vu1HVEJCDqs
