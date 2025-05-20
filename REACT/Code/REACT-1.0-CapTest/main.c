// Control code for REACT v1.0 PCB

#include <msp430.h> 
#include <stdint.h>
#include <stddef.h>

#include "macros.h"
#include "capacitors.h"

// Pin config for capacitor banks

CapBank bank1 = (CapBank) {
    .enPort     = &P8OUT,
    .enMask     = BIT1,
    .ctlPort   = &P8OUT,
    .ctlMask   = BIT3
};

CapBank bank2 = (CapBank) {
    .enPort     = &P3OUT,
    .enMask     = BIT5,
    .ctlPort   = &P8OUT,
    .ctlMask   = BIT2
};

CapBank bank3 = (CapBank) {
    .enPort     = &P3OUT,
    .enMask     = BIT4,
    .ctlPort   = &P3OUT,
    .ctlMask   = BIT6
};

CapBank bank4 = (CapBank) {
    .enPort     = &P2OUT,
    .enMask     = BIT2,
    .ctlPort   = &P3OUT,
    .ctlMask   = BIT7
};

// Banks should be organized from smallest to largest here
// But all banks same size in REACT v1.0
CapBank* cbpArray[] = {&bank1, &bank2, &bank3, &bank4};

// Increase capacitance by smallest available step
// Returns 1 on success, 0 on failure
inline uint8_t stepCapUp(){
    size_t i;
    for(i = 0; i < sizeof(cbpArray) / sizeof(cbpArray[0]); i++){
        if(expandCapBank3State(cbpArray[i])){
            return 1;
        }
    }
    return 0;
}

// Decrease capacitance by smallest available step
// Returns 1 on success, 0 on failure
inline uint8_t stepCapDown(){
    size_t i;
    for(i = 0; i < sizeof(cbpArray) / sizeof(cbpArray[0]); i++){
        if(contractCapBank3State(cbpArray[i])){
            return 1;
        }
    }
    return 0;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    // Setup GPIO
    P7DIR |= BIT5 | BIT6 | BIT7;    // RGB LED output
    P1DIR |= BIT6 | BIT7;           // LED1 and LED2 output
    P7DIR &= ~(BIT2 | BIT3);        // S1 and S2 input

    P7OUT |= BIT5 | BIT6 | BIT7;    // Startup with RGB off
    P1OUT &= ~(BIT6 | BIT7);        // Startup with LEDs off

    P7REN |= BIT2 | BIT3;           // Buttons pull to gnd, pullup resistor
    P7OUT |= BIT2 | BIT3;

    // Setup clocks
    CSCTL0_H = CSKEY_H;             // Unlock CS
    CSCTL1 = DCOFSEL_0;             // DCO -> 1 MHz
    CSCTL2 = SELA__VLOCLK |         // SMCLK = MCLK = DCO, ACLK = VLOCLK = ~10 kHz
             SELS__DCOCLK |
             SELM__DCOCLK;
    CSCTL0_H = 0;                   // Lock CS
    __delay_cycles(100);

    // Setup measurement timer
    TA0CCTL0 = CCIE;
    TA0CCR0 = 500;                  // 10 kHz clock -> 0.05 second period
    TA0CTL = TASSEL__ACLK | MC__UP;

    __bis_SR_register(GIE);         // Enable interrupts

    // Init all capacitor banks
    size_t i;
    for(i = sizeof(cbpArray) / sizeof(cbpArray[0]); i --> 0;){
        initCapBank(cbpArray[i]);
    }

    // Vhigh_alarm is P2.1
    // Vlow_alarm is P2.0
    // Comparator output is push-pull so no need for pullup/down
    P2DIR &= ~(BIT0 | BIT1);        // Comparator alarm input

    PM5CTL0 &= ~LOCKLPM5;           // Disable GPIO high-z

    // Application code goes here
    while(1){
        __no_operation();
    }

	return 0;
}

// Timer0_A1 Interrupt Vector (TAIV) handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER0_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    if(REACT_V_HIGH()){
        stepCapUp();
    }
    if(REACT_V_LOW()){
        stepCapDown();
    }
}
