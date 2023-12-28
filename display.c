// An highlighted block
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>
#include<termios.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
#include<sys/types.h>
#include<errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <unistd.h>
typedef unsigned          char uint8_t;
typedef uint8_t  u8;
#define OLED_CMD   0x00
#define OLED_DAT   0x01
int fd;                                 
unsigned char  yi[16]={"Angle of beam:"};
unsigned char  er[16]={"ming"};
unsigned char san[16]={"Distance:"};
unsigned char  si[16]={"okok"};
const unsigned char zi[];
/*const unsigned char picture1[];
const unsigned char picture2[];
const unsigned char picture3[];
const unsigned char picture4[];
const unsigned char picture5[];
const unsigned char picture6[];
const unsigned char picture7[];
*/
#if 0
void WriteCmd(int fd,unsigned char I2C_Command)//写命令
{
	wiringPiI2CWriteReg8(fd,0x00, I2C_Command);
}
#endif
//画点函数
void OLED_SetPos(unsigned char x, unsigned char y) 
{ 
   WriteCmd(0xb0+y);
   WriteCmd(((x&0xf0)>>4)|0x10);
   WriteCmd((x&0x0f)|0x01);
}
//BMP位图显示
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
   unsigned int j=0;
   unsigned char x,y;

 if(y%8==0)
   	y = 0;
 else
   	y += 1;
   for(y=y0;y<y1;y++)
   {
   	OLED_SetPos(x0,y);
   	for(x=x0;x<x1;x++)
   	{
   		 wiringPiI2CWriteReg8(fd,0x40,BMP[j++]);
   	}
   }
}


void init(void)//OLED初始化
{
   wiringPiSetup();
       fd=wiringPiI2CSetup(0x3c);//i2c?
       wiringPiI2CWriteReg8(fd,0x00,0xa1);//t?í??90xa0
       wiringPiI2CWriteReg8(fd,0x00,0xc8);//L?úí??90xc0
       wiringPiI2CWriteReg8(fd,0x00,0x8d);//A?5w?
       wiringPiI2CWriteReg8(fd,0x00,0x14);
       wiringPiI2CWriteReg8(fd,0x00,0xa6);//óí?>:90xa7
       wiringPiI2CWriteReg8(fd,0x00,0xaf);// >:
}

void qingping(void)//清屏
{
   char zt1,zt2;
   for(zt1=0;zt1<8;zt1++)
   {
   	wiringPiI2CWriteReg8(fd,0x00,0xb0+zt1);
           for(zt2=0;zt2<128;zt2++) wiringPiI2CWriteReg8(fd,0x40,0x00);
   }
}


void ascii(float Angle,float distance)//字符显示函数
{
   sprintf(er,"%f",Angle);  // float 0 char
   sprintf(si,"%f",distance); // double 0 char 
   int zt;
       char zt3,zt4;
   for(zt3=0;zt3<4;zt3++)
       {
   	wiringPiI2CWriteReg8(fd,0x00,0xb0+(zt3*2));
               for(zt4=0;zt4<16;zt4++)
               {
   		         for(zt=0;zt<8;zt++)
                       {
                       	if(zt3==0) wiringPiI2CWriteReg8(fd,0x40,zi[yi[zt4]*16+zt]);
                               else if(zt3==1)  wiringPiI2CWriteReg8(fd,0x40,zi[er[zt4]*16+zt]);
                               else if(zt3==2)  wiringPiI2CWriteReg8(fd,0x40,zi[san[zt4]*16+zt]);
                               else if(zt3==3)  wiringPiI2CWriteReg8(fd,0x40,zi[si[zt4]*16+zt]);
                       }
   	}
               wiringPiI2CWriteReg8(fd,0x00,0xb0+(zt3*2)+1);
               for(zt4=0;zt4<16;zt4++)
               {
               	for(zt=0;zt<8;zt++)
                       {
                       	if(zt3==0) wiringPiI2CWriteReg8(fd,0x40,zi[yi[zt4]*16+zt+8]);
                               else if(zt3==1)  wiringPiI2CWriteReg8(fd,0x40,zi[er[zt4]*16+zt+8]);
                               else if(zt3==2)  wiringPiI2CWriteReg8(fd,0x40,zi[san[zt4]*16+zt+8]);
                               else if(zt3==3)  wiringPiI2CWriteReg8(fd,0x40,zi[si[zt4]*16+zt+8]);
                       }
               }
   }
}


int main()
{
   float Angle = 2.98754546;
   float distance = 5.754644545;

   init();
   delay(10);
   qingping();//清屏
   delay(10);
   ascii(Angle,distance);//字符显示
   delay(10);
   	
   while(1)
   {
	   /*
   	//qingping();
   	OLED_DrawBMP(0,0,128,8,(unsigned char *)picture1);
   	delay(1);
   	OLED_DrawBMP(0,0,128,8,(unsigned char *)picture2);
   	delay(1);
   	OLED_DrawBMP(0,0,128,8,(unsigned char *)picture3);
   	delay(1);
   	OLED_DrawBMP(0,0,128,8,(unsigned char *)picture4);
   	delay(1);
   	OLED_DrawBMP(0,0,128,8,(unsigned char *)picture5);
   	delay(1);
   	OLED_DrawBMP(0,0,128,8,(unsigned char *)picture6);
   	delay(1);
   	OLED_DrawBMP(0,0,128,8,(unsigned char *)picture7);
   	delay(1);

	*/
   }
}

