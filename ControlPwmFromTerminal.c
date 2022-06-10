#include <msp430.h>

int duty = 0;

void PWM(int duty);
void port_config(void);
void clock_config(void);
void uart(void);
int main(void) {
    WDTCTL = WDTPW + WDTHOLD;                           // Stop WDT
    port_config();
    clock_config();
    uart();
    _enable_interrupts();
    while(1);
}
                                                  /* RX ISR : Start conversion on demand, i.e. whenever t is received*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
    if (UCA0RXBUF == '1') {
        PWM(10);
    }
    else if (UCA0RXBUF == '2') {
        PWM(20);
    }
    else if (UCA0RXBUF == '3') {
        PWM(30);
    }
    else if (UCA0RXBUF == '4') {
        PWM(40);
    }
    else if (UCA0RXBUF == '5') {
        PWM(50);
    }
}

void PWM(int duty) {
    TACCR0 = 1000;
    TACCR1 = (TACCR0*duty)/100;
    TACCTL1 = OUTMOD_7;
    TACTL = TASSEL_2|MC_1|ID_2;
}
void port_config(void) {
    P1DIR = 0xFF;                                 //All P2.x output
    P1OUT &= 0x00;                                //reset
                                                  /* Configure Pin Muxing P1.1 RXD and P1.2 TXD */
    P1SEL = BIT1 | BIT2 |BIT6 ;
    P1SEL2 = BIT1 | BIT2;
}

void uart(void){
                                                /* Place UCA0 in Reset to be configured */
    UCA0CTL1 = UCSWRST;
                                                /* Baud Rate configuration */
    UCA0CTL1 |= UCSSEL_2;                       // SMCLK
    UCA0BR0 = 104;                              // 1MHz 9600
    UCA0BR1 = 0;                                // 1MHz 9600
    UCA0MCTL = UCBRS0;                          // Modulation UCBRSx = 1
                                                /* Take UCA0 out of reset */
    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0RXIE;                            //Enable USCI_A0 RX interrupt
}

void clock_config(void) {
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
}

