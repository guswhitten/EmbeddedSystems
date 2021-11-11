#include <msp430.h>
#define RedLED BIT6
#define GreenLED BIT0
#define ToggleLeds (P1OUT ^= RedLED|GreenLED)
#define Button BIT3
void one(void)
{
    BCSCTL2 |= DIVS_3;              //BCSCTL2 = 0x06
    WDTCTL = WDT_MDLY_32;           //WDTCTL = 0x6910
    IE1 |= WDTIE;                   //IE1 = 0x01
    P1DIR = RedLED|GreenLED;        //P1DIR = 0x41      P1IN = 0x4C
    P1OUT = RedLED;                 //P1OUT = 0x40
    _enable_interrupts();
    LPM1;
}
#pragma vector = WDT_VECTOR
__interrupt void WDT(void)
    {
     P1OUT = ToggleLeds;
    }


//result -->   https://youtu.be/cwIxpn7dnvQ


