# EmbeddedSystems
This repository is dedicated to code files written and used in ECE09342-Intro to Embedded Systems.

IDE - Code Composer Studio (CCS)

Device - TI-MSP430G2553

The integer at the start of the name of each file indicates the lab # that file belongs to.

    -05WDT.c 
        Configures the MSP430's Watchdog Timer (WDT) to enable an interrupt every 256ms.
        Every time the interrupt occurs, the red and green LED toggle.
    
    -05softwarePWM.c
        Configures the MSP430's Timer A module to generate a PWM
        PWM controls LED brightness with 10% duty cycle and 500ms period
        
    -05hardwarePWM.c
        Configures Timer A module to generate a PWM using MSP's hardware.
        Uses MSP's internal pull-up resistor connected in parallel to Button (P1.3)

    -06
