#ifndef DISPLAY_H

#define DISPLAY_H

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>
#include<termios.h>
#include<string.h>
#include<sys/time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "front.h" 
// LED Pin - wiringPi pin 0 是 BCM_GPIO 17。  ssd1306
//利用 wiringPiSetupSys 进行初始化时必须使用 BCM 编号
//选择其他 pin 编号时，请同时使用 BCM 编号
//更新 Property Pages - Build Events - Remote Post-Build Event 命令
//它使用 gpio 导出进行 wiringPiSetupSys 的设置
#define	LED	17
 
#define I2C_ADDR 0x3c
typedef unsigned char  u8;
typedef enum {
    FONT_6x8     = 0,
    FONT_8x16       ,
} FONT_TYPE; 
extern int i2cHand;
 
 
void WriteCmd(int fd, unsigned char I2C_Command);//写命令

 
void OLED_Init(int fd);
 
void WriteData(int fd, unsigned char I2C_Data);//写数据
 
 
void OLED_SetPos(int fd, unsigned char x, unsigned char y); //设置起始点坐标
 
/*写 缓存数据*/
void Write_DataBuffer(void);//这个是将DataBuffer数组里面的值，全部写进屏里去
 
void OLED_Full(void);//全屏填充
 
 
void OLED_CLS(void);//清屏

void oled_flush_with( u8 *gram );

void oled_set_pos( u8 x, u8 y, u8 val );
void oled_draw_point( u8 x, u8 y, u8 val );


void show_char( u8 *font_buf, u8 width, u8 hight, u8 x, u8 y );
void show_str( u8 *str, FONT_TYPE font_type, u8 x, u8 y ) ;
#endif
