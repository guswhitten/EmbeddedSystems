/*
This code was adapted from: drselim MSP430 & Multiple ADC on YouTube
https://youtu.be/Ev871bhGFt0
*/


#include <msp430.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char vt_chara3[5];
char vt_chara4[5];

char volta3[] = " A3:   ";
char volta4[] = " A4:   ";
char newline[] = " \r\n";
int val0 = 0;
int val1 = 0;
unsigned int adc[6];
void ser_output(char *str);
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    P1SEL = BIT1|BIT2;
    P1SEL2 = BIT1|BIT2;
    UCA0CTL1 |= UCSWRST+UCSSEL_2;

    UCA0BR0 = 52;
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS_0;
    UCA0CTL1 &= ~UCSWRST;

    ADC10CTL1 = INCH_7 + ADC10DIV_0 + CONSEQ_3 + SHS_0;
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + MSC + ADC10ON; //ADC10IE
    ADC10AE0 = BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT0;
    ADC10DTC1 = 8;

    while(1){
        ADC10CTL0 &= ~ENC;
        while (ADC10CTL1 & BUSY);
        ADC10CTL0 |= ENC + ADC10SC;
        ADC10SA = (unsigned int)adc;
        ltoa(adc[4],vt_chara3,10);
        ltoa(adc[3],vt_chara4,10);
        ser_output(volta3);
        ser_output(vt_chara3);
        ser_output(volta4);
        ser_output(vt_chara4);
        ser_output(newline);
        __delay_cycles(100000);
    }
}
void ser_output(char *str){
    while(*str != 0){
        while ((IFG2 & UCA0TXIFG) == 0);
        val0 = adc[3]; val1 = adc[4];
        UCA0TXBUF = *str++;
    }
}
