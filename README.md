# EmbeddedSystems
This repository is dedicated to code files written and used in ECE09342-Intro to Embedded Systems.

IDE - Code Composer Studio (CCS)

Device - TI-MSP430G2553

The integer at the start of the name of each file indicates the lab # that file belongs to.

    -05WDT.c 
        Configures the MSP430's Watchdog Timer (WDT) to enable an interrupt every 256ms.
        Every time the interrupt occurs, the red and green LED toggle.
    
    -05softwarePWM.c
        Turns off WDT since this program uses timer A module (TA0xxxx)
        in order to access MSP430 "up mode"
        Timer counts til it reaches 
