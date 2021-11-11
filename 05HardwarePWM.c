#include "msp430G2553.h"
void main(void)
{
 WDTCTL = WDTPW + WDTHOLD;  // Stop WDT

 P1DIR |= BIT6;             // P1.6 to output
 TACTL = TASSEL_2 + MC_1 + ID_3 + TACLR;//+TACLR;

 TACCR0 = 31250; // Set maximum count value (PWM Period
 TACCR1 = 6250; // initialise counter compare value

 TACCTL0 |= CCIE;
 TACCTL1 |= CCIE;

 TACCTL0 &=~CCIFG;
 TACCTL1 &=~CCIFG;

 _enable_interrupts(); // Enter LPM0
}
#pragma vector = TIMER0_A0_VECTOR       //define the interrupt service vector
__interrupt void TA0_ISR (void)    // interrupt service routine
    {
    P1OUT |=BIT6;
    TACCTL0 &=~CCIFG;
    }

#pragma vector = TIMER0_A1_VECTOR       //define the interrupt service vector
__interrupt void TA1_ISR (void)    // interrupt service routine
    {
    P1OUT &=~BIT6;
    TACCTL1 &=~CCIFG;

    }
