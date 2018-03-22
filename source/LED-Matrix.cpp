#include "MicroBit.h"
#include "LED-Matrix.h"

/******************Instructions**********************/
#define SYS_DIS 0x00                //Turn off system shock
#define SYS_EN  0x01                //Turn on  system shock
#define LED_OFF 0x02                //Turn off LED display
#define LED_ON  0x03                //Turn on LED display
#define BLINK_OFF   0x08            //Close blink
#define BLINK_ON    0x09            //Open blink
#define SLAVE_MODE  0x10            //Slave mode
#define RC_MASTER_MODE  0x18        //Use internal clock
#define COM_OPTION  0x24            //24:16COM NMOS COM PMOS
#define PWM_DUTY    0xAF            //PWM Brightness Control
/****************I/O definition**********************/

DigitalOut HT_CS(P0_16);
DigitalOut HT_RD(P0_22);
DigitalOut HT_WR(P0_23);
DigitalInOut HT_DAT(P0_21, PIN_INPUT, PullNone, 0);

static unsigned char com[12] = {
  0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x24, 0x28, 0x2C
};

void HT1632C_Write(unsigned char Data, unsigned char cnt)      //MCU writes the data to ht1632c, and the high position is in front
{
  unsigned char i;
  for(i=0; i<cnt; i++) {
    HT_WR=0;
    if(Data&0x80) {
      HT_DAT=1;
    } else {
      HT_DAT=0;
    }
    Data<<=1;
    HT_WR=1;
  }
}

void HT1632C_Write_CMD(unsigned char cmd) //MCU writes commands to ht1632c
{
  HT_DAT.output();
  HT_CS=0;
  HT1632C_Write(0x80,3);
  HT1632C_Write(cmd,9);
  HT_CS=1;
}

void HT1632C_Write_DAT(unsigned char Addr, const uint16_t data[], unsigned char num)
{
  HT_DAT.output();
  HT_CS=0;
  HT1632C_Write(0xa0,3);
  HT1632C_Write(Addr<<1,7);

  uint16_t d= data[num];
  for(unsigned char i=0; i<12; i++) {
    HT_WR=0;
    if(d&0x8000) {
      HT_DAT=1;
    } else {
      HT_DAT=0;
    }
    d<<=1;
    HT_WR=1;
  }
  HT_CS=1;
}

void HT1632C_clr(void)  //Clear function
{
    unsigned char i;
    HT_DAT.output();
    HT_CS=0;
    HT1632C_Write(0xa0,3);
    HT1632C_Write(0x00,7);
    for(i=0; i<48; i++) {
        HT1632C_Write(0,8);
    }
    HT_CS=1;
}

void HT1632C_Init(void) //HT1632C Init Function
{
  HT_CS=1;
  HT_WR=1;
  HT_DAT=1;
  HT1632C_Write_CMD(SYS_DIS);         //Close the HT1632C internal clock
  HT1632C_Write_CMD(COM_OPTION);      //Select HT1632C work mode
  HT1632C_Write_CMD(RC_MASTER_MODE);  //Select internal clock
  HT1632C_Write_CMD(SYS_EN);          //Open the HT1632C internal clock
  HT1632C_Write_CMD(PWM_DUTY);        //Init the PWM Brightness
  HT1632C_Write_CMD(BLINK_OFF);       //Close blink
  HT1632C_Write_CMD(LED_ON);          //Turn on LED display
}

uint16_t HT1632C_Read_DATA(unsigned char Addr)
{
  unsigned char i;
  HT_DAT.output();
  HT_CS=0;
  HT1632C_Write(0xc0,3);
  HT1632C_Write(Addr<<1,7);
  HT_DAT.input();
  int16_t data=0;
  for(i=0; i<12; i++) {
    HT_RD=0;
    data= data<<1 | HT_DAT;
    HT_RD=1;
  }
  HT_CS=1;
  return data<<4;
}

void HT1632C_Write_Pattern(const uint16_t pattern[])
{
  for (int col=0; col<12; col++) {
    HT1632C_Write_DAT(com[col],pattern,col);
  }
}

void HT1632C_Read_Pattern(uint16_t pattern[])
{
  for (int col=0; col<12; col++) {
    pattern[col]= HT1632C_Read_DATA(com[col]);
  }
}
