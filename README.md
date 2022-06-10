# EmbeddedSystems
This repository is dedicated to C programs that are all usable in Code Composer Studio with a TI-MSP430G2553 microcontroller

## Textbook reference (PDF Drive):
Programmable Microcontrollers with Applications (Unsalan, Gurhan) https://www.pdfdrive.com/deniz-programmable-microcontrollers-with-applications-msp430-launchpad-with-ccs-and-grace-e196719615.html

## Microcontroller:
TI-MSP430G2553: https://www.ti.com/product/MSP430G2553

## Software / IDE:
Code Composer Studio: https://software-dl.ti.com/ccs/esd/documents/ccs_downloads.html

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

    -06Photocell.c
        This code captures the sensor analog data from a PCB-mounted photoresistor
        Then configures the MSP's Analog-to-Digital Conversion (ADC) module to convert to digital data.
        Displays the digital data live to the Terminal, or a graph through UART
    
    -06Photocell&Potentiometer.c
        This code captures the sensor analog data from both a PCB-mounted photoresistor & a potentiometer
        Then configures the MSP's Analog-to-Digital Conversion (ADC) module to convert both to digital data.
        Displays the digital data live to the Terminal or a graph through UART
        
    -07ThingSpeak.cs
        Creates Windows Form application which produces a Graphical User Interface (GUI) to manage serial transmission
        Reads data serially from port 1 (COM6) at 19,200 bauds/s
        Expects to get data from two sensors and displays them in individual textbox on the GUI
        Transmits the data to ThingSpeak channel, which displays the data visually
        
    
