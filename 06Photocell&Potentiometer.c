/*
This code was adapted from: drselim MSP430 & Multiple ADC on YouTube
https://youtu.be/Ev871bhGFt0
*/
#include <msp430.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char v3[5];
char v4[5];
char a3[] = " A3:   ";
char a4[] = " A4:   ";
char newline[] = " \r\n";

unsigned int adc[6];                             // declare array of ints to reserve mem for reading sensor data 
void ser_output(char *str);                     //declare transmission subfunction
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    P1SEL = BIT1|BIT2;                                                 //set P1.1 and P1.2 as digital comm pins by setting
    P1SEL2 = BIT1|BIT2;                                                //bits 1 and 2 of P1SEL and P1SEL2
    UCA0CTL1 |= UCSWRST+UCSSEL_2;                                      //pause operation while configuring, choose SMCLK

    UCA0BR0 = 52;                                              //generate 19200 baud rate
    UCA0BR1 = 0;                                               // "   "     "     "     "
    UCA0MCTL = UCBRS_0;                                        // second modulation stage select is 1
    UCA0CTL1 &= ~UCSWRST;                                      // clear SW reset, ready for operation

    ADC10CTL1 = INCH_7 + ADC10DIV_0 + CONSEQ_3 + SHS_0;         //INCH_7 starting channel for conversion
                                                                //ADC10DIV_0 divide clock by 1
                                                                //CONSEQ_3 enables multiple channel conversion, starting with A7....A0
                                                                //SHS_0 sample and hold source = ADC10SC
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + MSC + ADC10ON;            //SREF_0 use 3.3v as Vref+ and GND as Vref-
                                                                //ADC10SHT_2 sample and hold time = 16*ADC10CLK
                                                                //MSC allows multiple sample and conversion operations
                                                                //ADC10ON enables adc module
    ADC10AE0 = BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT0;         //must enable same pin here as in ADC10CTL1
                                                                //In this case, A7...A0
    ADC10DTC1 = 8;                                              //how many transfers per block?

    while(1){
        ADC10CTL0 &= ~ENC;                                  //hold conversion
        while (ADC10CTL1 & BUSY);                           //don't proceed until ADC10BUSY is reset (last conversion finished)
        ADC10CTL0 |= ENC + ADC10SC;                         //enable conversion and then start ADC conversion
        ADC10SA = (unsigned int)adc;                        //set data transfer start address to address of adc array
        ltoa(adc[4],v3,10);                                 //convert long data received from p1.3 to a string
        ltoa(adc[3],v4,10);                                 //convert long data received from p1.4 to a string
        ser_output(a3);                                     // transmit string "A3:    "
        ser_output(v3);                                     //transmit p1.3's data value
        ser_output(a4);                                     //transmit string "A4:    "
        ser_output(v4);                                     //transmit p1.4's data value
        ser_output(newline);
        __delay_cycles(100000);                             //delay 0.1 second
    }
}
void ser_output(char *str){
    while(*str != 0){
        while ((IFG2 & UCA0TXIFG) == 0);            //wait until UCA0TXIFG bit is set inside IFG2
        UCA0TXBUF = *str++;                         //transmit data
    }
}
