#include "MicroBit.h"
#include "font.h"

MicroBit uBit;

/******************指令表/Instructions**********************/
#define SYS_DIS 0x00                //关闭系统震荡/Turn off system shock
#define SYS_EN  0x01                //打开系统震荡/Turn on  system shock
#define LED_OFF 0x02                //关闭LED显示/Turn off LED display
#define LED_ON  0x03                //打开LED显示/Turn on LED display
#define BLINK_OFF   0x08            //关闭闪烁   /Close blink
#define BLINK_ON    0x09            //打开闪烁   /Open blink            
#define SLAVE_MODE  0x10            //从模式     /Slave mode
#define RC_MASTER_MODE  0x18        //内部RC时钟 /Use internal clock 
#define COM_OPTION  0x24            //24:16COM，NMOS。C：COM，PMOS。
#define PWM_DUTY    0xAF            //PWM亮度控制 /PWM Brightness Control
/****************引脚定义 I/O definition**********************/

DigitalOut HT_CS(P0_16);
DigitalOut HT_RD(P0_22);
DigitalOut HT_WR(P0_23);
DigitalInOut HT_DAT(P0_21, PIN_INPUT, PullNone, 0);


static unsigned char com[12] = {0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x24, 0x28, 0x2C};

uint16_t readback[12];

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

void HT1632C_Write_CMD(unsigned char cmd)                     //MCU向HT1632c写命令/MCU writes commands to ht1632c
{
  HT_DAT.output();
  HT_CS=0;
  HT1632C_Write(0x80,3);                                    //ID:100
  HT1632C_Write(cmd,9);
  HT_CS=1;
}

void HT1632C_Write_DAT(unsigned char Addr, const uint16_t data[], unsigned char num)
{
  HT_DAT.output();
  HT_CS=0;
  HT1632C_Write(0xa0,3);                                    //ID:101
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

void HT1632C_clr(void)  //清屏函数/Clear function
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

void HT1632C_Init(void)                 //HT1632C初始化函数/HT1632C Init Function
{
  HT_CS=1;
  HT_WR=1;
  HT_DAT=1;
  HT1632C_Write_CMD(SYS_DIS);         //关闭HT1632C内部RC时钟/Close the HT1632C internal clock
  HT1632C_Write_CMD(COM_OPTION);      //选择HT1632C工作模式/Select HT1632C work mode
  HT1632C_Write_CMD(RC_MASTER_MODE);  //选择内部RC时钟/Select internal clock
  HT1632C_Write_CMD(SYS_EN);          //打开HT1632C内部RC时钟/Open the HT1632C internal clock
  HT1632C_Write_CMD(PWM_DUTY);        //PWM亮度设置/Init the PWM Brightness
  HT1632C_Write_CMD(BLINK_OFF);       //关闭闪烁   /Close blink
  HT1632C_Write_CMD(LED_ON);          //打开LED显示/ Turn on LED display
}

int16_t HT1632C_Read_DATA(unsigned char Addr)
{
  unsigned char i;
  HT_DAT.output();
  HT_CS=0;
  HT1632C_Write(0xc0,3);                                    //ID:101
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

void ExpandGlyph(const uint8_t glyph[18], uint16_t *bitmap)
{
    for (uint8_t col=0; col<6; col++) {
        uint8_t column= col<<1;
        uint8_t lsn= glyph[12+col];
        uint16_t c0= (glyph[column]<<8) + (lsn & 0xF0);
        uint16_t c1= (glyph[column+1]<<8) + ((lsn << 4) & 0xF0);
        *bitmap++= c0;
        *bitmap++= c1;
    }
}

void WriteGlyph(const uint8_t glyph[18])
{
    uint16_t bitmap[12];
    ExpandGlyph(glyph, bitmap);
    for (int c= 0; c<12; c++) {
        HT1632C_Write_DAT(com[c], bitmap, c);
    }
}

int main()
{
  NRF_GPIO_Type *gpiobase= (NRF_GPIO_Type *)NRF_GPIO_BASE;

  uBit.init();
  uBit.serial.baud(115200);

  HT1632C_Init();
  int count=0;
 considered_harmful:
  HT1632C_clr();
  WriteGlyph(glyph[count]);
  uBit.serial.send(charcode[count++]);
  uBit.serial.send("\n");
  count%=3000;
  for(int i=0; i<12; i++) {
    readback[i]= HT1632C_Read_DATA(com[i]);
  }
  for(int r=16; 4<r--; ) {
    for(int c=0; c<12; c++) {
      printf(readback[c]&(1<<r)?"#":".");
    }
    puts("");
  }
  wait(0.4);
  printf("Dir  %08lx: ", uint32_t(&gpiobase->DIR));
  printf("%08lx\r\n", gpiobase->DIR);
  printf("In   %08lx: ", uint32_t(&gpiobase->IN));
  printf("%08lx\r\n", gpiobase->IN);

  goto considered_harmful;
}
