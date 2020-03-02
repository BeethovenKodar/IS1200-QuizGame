#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void) // returns the status of the switches
{ 
    int sw = (PORTD & 0xF00) >> 8;
    return sw;
}

int getbtns(void) // returns the status of the buttons
{
    return ((PORTD & 0xE0) >> 4) | ((PORTF & 0x2) >> 1);
}

/*
int getbtnsInv(void)
{
    return (((((PORTD & 0xE0) >> 4) | (((PORTF & 0x2) >> 1)) & 0x1) << 7) |
            ((((PORTD & 0xE0) >> 4) | (((PORTF & 0x2) >> 1)) & 0x2) << 6) |
            ((((PORTD & 0xE0) >> 4) | (((PORTF & 0x2) >> 1)) & 0x4) << 5) |
            ((((PORTD & 0xE0) >> 4) | (((PORTF & 0x2) >> 1)) & 0x8) << 4) >> 4);
}
//1234
// ((40000000 | 
// 03000000 |
// 00200000 |
// 00010000 |
// 00004321) >> 4)
*/