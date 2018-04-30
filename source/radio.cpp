/*
 * radio.cpp
 * =========
 * Receiver side
 *
 * Compile with 
 * #define MICROBIT_BLE_ENABLED      0
 * #define MICROBIT_BLE_PAIRING_MODE 0
 * in yotta_modules/microbit-dal/inc/core/MicroBitConfig.h
 *
 * see https://lancaster-university.github.io/microbit-docs/ubit/radio/# for details
 */

#include "MicroBit.h"
#include "LED-Matrix.h"
#include "registerdump.h"

MicroBit uBit;

static const uint16_t om[][12] = {
{
0b0011111100000000,
0b0100000010000000,
0b1000000001010000,
0b1000000001010000,
0b1000000001110000,
0b1000000000000000,
0b1000000000000000,
0b1000000001110000,
0b1000000001010000,
0b1000000001010000,
0b0100000010000000,
0b0011111100000000
},
{
0b0011111100000000,
0b0100000010000000,
0b1010001001010000,
0b1010100101010000,
0b1001011001110000,
0b1100010000000000,
0b0010100000000000,
0b1010101001110000,
0b0010100101010000,
0b1100011001010000,
0b0100000010000000,
0b0011111100000000
},
{
0b0000000000000000,
0b0000000000000000,
0b0010001000000000,
0b0010100100000000,
0b0001011000000000,
0b1100010000000000,
0b0010100000000000,
0b1010101000000000,
0b0010100100000000,
0b1100011000000000,
0b0000000000000000,
0b0000000000000000
}
};

const char OM[]="\nOM\n",
  MANI[]= "\nMANI\n",
  PADME[]= "\nPADME\n",
  HUM[]= "\nHUM\n";

static const uint16_t *show[]= {om[0], om[1], om[2], om[1]};
static const char *meditations[4]= {
  OM, MANI, PADME, HUM
};

uint16_t readback[12];

static volatile unsigned char omCount=0;

void onData(MicroBitEvent e)
{
    PacketBuffer b=uBit.radio.datagram.recv();
    omCount= b[0];
    uBit.serial.send("\r\nReceived ");
    uBit.serial.send(omCount);
    uBit.serial.send("\r\n");

    uBit.serial.send(meditations[omCount]);
    HT1632C_clr();
    HT1632C_Write_Pattern(show[omCount]);
    HT1632C_Read_Pattern(readback);
    for(int r=16; 4<r--; ) {
        for(int c=0; c<12; c++) {
            printf(readback[c]&(1<<r)?"#":".");
        }
        puts("");
    }
}

int main()
{
  NRF_GPIO_Type *gpiobase= (NRF_GPIO_Type *)NRF_GPIO_BASE;

  uBit.init();
  HT1632C_Init();

  uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
  uBit.radio.enable();
  uBit.serial.baud(115200);

  release_fiber();
}
