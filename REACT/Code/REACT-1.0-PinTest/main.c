// Basic program to validate buttons and LEDs on REACT v1.0 PCB

#include <msp430.h>

#include "macros.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;

	// Setup GPIO
	P7DIR |= BIT5 | BIT6 | BIT7;    // RGB LED output
	P1DIR |= BIT6 | BIT7;           // LED1 and LED2 output
	P7DIR &= ~(BIT2 | BIT3);        // S1 and S2 input

	P7OUT |= BIT5 | BIT6 | BIT7;    // Startup with RGB off
	P1OUT &= ~(BIT6 | BIT7);        // Startup with LEDs off

	P7REN |= BIT2 | BIT3;           // Buttons pull to gnd, pullup resistor
	P7OUT |= BIT2 | BIT3;

	PM5CTL0 &= ~LOCKLPM5;           // Disable GPIO high-z
	
	while(1){
        if(S1_PRESSED){
            RGB_R_ON();
            RGB_G_ON();
            RGB_B_ON();
        }else{
            RGB_R_OFF();
            RGB_G_OFF();
            RGB_B_OFF();
        }
        if(S2_PRESSED){
            LED_R_ON();
            LED_G_ON();
        }else{
            LED_R_OFF();
            LED_G_OFF();
        }
	}

	return 0;
}
