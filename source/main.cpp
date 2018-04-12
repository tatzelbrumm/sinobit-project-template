/**
 * This is a simple template for use with Sino:bit.
 *
 * Forked from Calliope Mini project 
 * Original copyright: 
 * @copyright (c) Calliope gGmbH.
 * @author Matthias L. Jugel.
 *
 * Licensed under the Apache License 2.0
 */

#include <MicroBit.h>

MicroBit uBit;


int main(void) {
    uBit.init();
    uBit.serial.baud(115200);
    uBit.serial.send("Sino:bit template v1.0\r\n");

    uBit.serial.send("Hello world!\r\n");
}