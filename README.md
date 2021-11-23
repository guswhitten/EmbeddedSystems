# EmbeddedSystems
This repository is dedicated to code files written and used in ECE09342-Intro to Embedded Systems.

IDE - Code Composer Studio (CCS)

Device - TI-MSP430G2553

The integer at the start of the name of each file indicates the lab # that file belongs to.
Lab 05 involves timers and Pulse Width Modulation (PWMs). 

    -05WDT.c 
        Configures the MSP430's Watchdog Timer (WDT) to enable an interrupt every 256ms.
        Every time the interrupt occurs, the red and green LED toggle.
    
    -05softwarePWM.c
        
