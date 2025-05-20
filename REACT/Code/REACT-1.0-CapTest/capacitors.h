#ifndef CAPS_H_
#define CAPS_H_

#include <stdint.h>

// Port direction reg address is (port output reg address + OUT_DIR_OFFSET)
#define OUT_DIR_OFFSET 2

typedef enum CapBankState{
    DISCONNECTED_SER,
    DISCONNECTED_PAR,
    CONNECTED_SER,
    CONNECTED_PAR
} CapBankState;

typedef struct CapBank{
    volatile uint8_t* enPort;
    uint8_t enMask;
    volatile uint8_t* ctlPort;
    uint8_t ctlMask;
    CapBankState state;
} CapBank;

void initCapBank(CapBank* bank);
void setCapBankState(CapBank* bank, CapBankState state);
uint8_t expandCapBank3State(CapBank* bank);
uint8_t contractCapBank3State(CapBank* bank);

#endif /* CAPS_H_ */
