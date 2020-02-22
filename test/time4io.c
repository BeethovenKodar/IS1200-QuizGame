// f)
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void) { // returns the status of the switches
    int sw = (PORTD & 0xF00) >> 8;
    return sw; //
}

// g) returns the status of the buttons
int getbtns(void) {
    return (PORTD & 0xE0) >> 5; //1110 0000 --> 111
}
