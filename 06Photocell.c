#include <msp430g2553.h>

volatile long tempRaw;
char result[100];
volatile long sample[100];
int temp = 0;

void ConfigureAdc_temp();

void uart_init(void);
void ConfigClocks(void);
void strreverse(char* begin, char* end);
void itoa(int value, char* str, int base);
void port_init();

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    port_init();

    ConfigClocks();
    uart_init();

    _delay_cycles(5);                // Wait for ADC Ref to settle

    while(1){
                ConfigureAdc_temp();
                ADC10CTL0 |= ENC + ADC10SC +MSC;       // Converter Enable, Sampling/conversion start
                while((ADC10CTL0 & ADC10IFG) == 0);    // check the Flag, while its low just wait
                P1OUT |= BIT6;                         // green LED on
                _delay_cycles(2000000);               // delay for about 1 second so LED doesn't flash too fast
                tempRaw = ADC10MEM;                    // read the converted data into a variable
                P1OUT &= ~BIT6;                        // green LED off
                ADC10CTL0 &= ~ADC10IFG;                // clear the flag
                temp = (tempRaw* 48724 - 30634388) >> 16;
                itoa(((tempRaw* 48724 - 30634388) >> 16),result,10); // convert temperature reading to Fahrenheit
                int acount =0;
                                    while(result[acount]!='\0')
                                  {
                                      while((IFG2 & UCA0TXIFG)==0);                  //Wait Unitl the UART transmitter is ready
                                      UCA0TXBUF = result[acount++] ;                   //Transmit the received data.

                                  }
    }
}
// Configure ADC Temperature
void ConfigureAdc_temp(){
//change to CONSEQ3 to read sequenvce of chsnnels 
     ADC10CTL1 = INCH_4 + ADC10DIV_0 + CONSEQ_2;            //change INCH_10 to INCH_4 to switch from MSP's internal temp as input pin to p1.4 as input pin
     ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON ;//| ADC10IE; //Vref+, Vss, 64 ATD clocks per sample, internal references, turn ADCON
     __delay_cycles(5);                                 //wait for adc Ref to settle
      ADC10CTL0 |= ENC| MSC;                            //converter Enable, Sampling/Conversion start, multiple sample/conversion operations
}
void uart_init(void){
    UCA0CTL1 |= UCSWRST;                     //Disable the UART state machine
    UCA0CTL1 |= UCSSEL_3;                    //Select SMCLK as the baud rate generator source
    UCA0BR1 =0;
    UCA0BR0 = 104;                           //Produce a 9,600 Baud UART rate
    UCA0MCTL = 0x02;                         //Chooa propriately from Table 15-4 in User Guide
    UCA0CTL1 &= ~UCSWRST;                    //Enable the UART state naching
    IE2 |= UCA0RXIE;                         //Enable the UART receiver Interrupt
}
void ConfigClocks(void)
 {

  BCSCTL1 = CALBC1_1MHZ;                     // Set range
  DCOCTL = CALDCO_1MHZ;                      // Set DCO step + modulation
  BCSCTL3 |= LFXT1S_2;                       // LFXT1 = VLO
  IFG1 &= ~OFIFG;                            // Clear OSCFault flag
  BCSCTL2 = 0;                               // MCLK = DCO = SMCLK
 }
void strreverse(char* begin, char* end)      // Function to reverse the order of the ASCII char array elements
{
    char aux;
    while(end>begin)
        aux=*end, *end--=*begin, *begin++=aux;
}

void itoa(int value, char* str, int base) {         //Function to convert the signed int to an ASCII char array

    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* wstr=str;
    int sign;
                                                    // Validate that base is between 2 and 35 (inlcusive)
    if (base<2 || base>35){
        *wstr='\0';
        return;
    }
                                                    // Get magnitude and th value
    sign=value;
    if (sign < 0)
        value = -value;

    do                                              // Perform interger-to-string conversion.
        *wstr++ = num[value%base];                  //create the next number in converse by taking the modolus
    while(value/=base);                             // stop when you get  a 0 for the quotient

    if(sign<0)                                      //attach sign character, if needed
        *wstr++='-';
    *wstr='\0';                                     //Attach a null character at end of char array. The string is in reverse order at this point
    strreverse(str,wstr-1);                         // Reverse string

}
void port_init(){
    P1SEL |= BIT1 + BIT2;            // select non-GPIO  usage for Pins 1 and 2
    P1SEL2 |= BIT1 + BIT2;           // Select UART usage of Pins 1 and 2
}

