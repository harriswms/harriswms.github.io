#ifndef MACROS_H_
#define MACROS_H_

// GPIO interactions

#define S1_PRESSED()    (!(P7IN & BIT2))
#define S2_PRESSED()    (!(P7IN & BIT3))

#define RGB_R_ON()      P7OUT &= ~BIT5
#define RGB_G_ON()      P7OUT &= ~BIT7
#define RGB_B_ON()      P7OUT &= ~BIT6
#define RGB_R_OFF()     P7OUT |= BIT5
#define RGB_G_OFF()     P7OUT |= BIT7
#define RGB_B_OFF()     P7OUT |= BIT6
#define RGB_R_TOGGLE()  P7OUT ^= BIT5
#define RGB_G_TOGGLE()  P7OUT ^= BIT7
#define RGB_B_TOGGLE()  P7OUT ^= BIT6

#define LED_R_ON()      P1OUT |= BIT6
#define LED_G_ON()      P1OUT |= BIT7
#define LED_R_OFF()     P1OUT &= ~BIT6
#define LED_G_OFF()     P1OUT &= ~BIT7
#define LED_R_TOGGLE()  P1OUT ^= BIT6
#define LED_G_TOGGLE()  P1OUT ^= BIT7

// Voltage alarm inputs from external comparator

#define REACT_V_HIGH()  (P2IN & BIT1)
#define REACT_V_LOW()   (!(P2IN & BIT0))

#endif /* MACROS_H_ */
