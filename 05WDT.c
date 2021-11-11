/*
We want to configure the clock to toggle the red and green LEDs every t = 256 ms.
First, we must configure the clock. We will use sub-main clock (SMCLK) which has frequency 1 MHz.
Since freq = 1 / period, we set the period to 0.256 and solve for desired freq (desired freq = 3.9 Hz)
We must use clock dividers to get from 1 MHz to 3.9 Hzwdtie
*/

#include <msp430.h>
void main(void)
{
    BCSCTL2 |= DIVS_3;              //SMCLK freq divided by 8 (1 MHz / 8 = 125 kHz)
    WDTCTL = WDT_MDLY_32;           //SMCLK freq divided by 32,768 (125 kHz / 32768 = 3.81 Hz)
    IE1 |= WDTIE;                   //To use WDT+ as an interval timer, this bit must be set to request an interrupt
    P1DIR = BIT6|BIT0;              //sets P1DIR to 0x41, making red onboard LED (p1.6) and green onboard LED (p1.0) outputs
    P1OUT = BIT6;                   //sets P1OUT to 0x40, so red LED starts on
    _enable_interrupts();           //enables interrupts
    LPM1;                           //Lower power mode --> CPU and MCLK disabled. SMCLK and ACLK still active
}
#pragma vector = WDT_VECTOR
__interrupt void WDT(void)
    {
     P1OUT ^= BIT6|BIT0;            //XOR operation toggles LEDs once per clock cycle
    }


//result -->   https://youtu.be/cwIxpn7dnvQ


