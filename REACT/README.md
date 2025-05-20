## Overview

This is a PCB implementation of a generic intermittent system combined with the dynamic capacitance
circuit described in our ASPLOS 2024 paper "Energy-adaptive Buffering for Efficient, Responsive, and
Persistent Batteryless Systems", available [here](https://harriswms.github.io/files/React.pdf).

#### Project Status

V1.1 is under development and will break the two major components of the system into separate pieces,
allowing them to be used separately. One side will contain a generic MSP430-based intermittent system,
while the other will contain the REACT capacitor banks and control circuits. All power and control signals
for REACT will be broken out to jumpers so that you can connect REACT to other systems, use the generic
intermittent system with a non-REACT energy buffer, or easily combine the two for a complete single-PCB
batteryless system.

An assembled and validated PCB for V1.0 is available in the lab and partially works. The MSP430 can be used
to control REACT, and REACT works as intended. However, the power control circuit between the MSP430 and REACT
does not work, so the board can't function as a full batteryless system as is. You can load the REACT firmware
to the MSP430 and control REACT normally, so it could be used as a self-contained energy buffer or just to
evaluate the energy buffer itself. V1.1 will fix the power gate and separate the two components for individual
use.

## Hardware

Schematic and PCB designs are generated in KiCad version 9.

TODO

LEDs and switches are available for basic debugging and interactive use.

#### Jumpers

**J1:** Debug header for programming the MSP430FR5994.

**J2:** Power select jumper for intermittent system. The center pin is connected to the system supply voltage;
it can draw power either from the debug header or from the output of the power gate for batteryless operation.

**J3, J4, J6, J7, J8:** Jumpers to connect and disconnect the LEDs. There is one RGB LED and one LED containing
separate red and green lights.

**J5:** GPIO breakout header.

## Software

Code is generated as Code Composer Studio version 11 projects.

[REACT-1.0-PinTest](Code/REACT-1.0-PinTest) is a simple bring-up test program to verify solder connections,
programmability, etc.

[REACT-1.0-CapTest](Code/REACT-1.0-CapTest) is a skeleton program implementing the firmware component of REACT.
This can be used as a template for intermittent applications which use REACT.
