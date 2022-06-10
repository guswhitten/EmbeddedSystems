//press t from terminal and then green will be on
#include <msp430.h>

void port_init(void);
void clock_init(void);
void uart_init(void);

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
    port_init();
    clock_init();
    uart_init();
    _enable_interrupts();
    while(1);
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
    if (UCA0RXBUF == 't') {
        P1OUT ^=0x01;
    }
    else if (UCA0RXBUF == 'r') {
        P1OUT ^=0x40;
    }
    else if (UCA0RXBUF == 'a') {
        P1OUT ^=0x41;
    }
    else if (UCA0RXBUF == 'f') {
        P1OUT ^=0x01;
    }
}
void port_init(void){
    P1DIR = 0xFF;                               //All P2.x output
    P1OUT &= 0x00;                              //reset
                                                /* Configure Pin Muxing P1.1 RXD and P1.2 TXD */
    P1SEL = BIT1 | BIT2 ;
    P1SEL2 = BIT1 | BIT2;
}
void clock_init(void){
                                                /* Use Calibration values for 1MHz Clock DCO*/
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
}
void uart_init(void){
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




