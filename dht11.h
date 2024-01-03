#ifndef DHT11_H
#define DHT11_H


#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>



#include <wiringPi.h>



typedef unsigned char uint8;

typedef unsigned int  uint16;

typedef unsigned long uint32;



uint32 databuf;



/*

//初始化引脚

//上电1s内不操作，维持电平稳定

*/

void GPIO_init(int gpio_pin);


/*

//起始信号

1.主机初状态是高电平，要超过1s稳定电平

2.主机再拉低延时18ms-30ms

3.主机末状态是高电平，等待

*/

void DHT11_start(int gpio_pin);


/*

//主机接受数据

1.主机接受到从机回复的响应信号

2.格式0——54us的低电平+23到27us的高电平

格式1——54us的低电平+68到74us的高电平

3.思路：从识别到低电平开始，然后去除掉掉前面54秒的低电平还有

*/

uint8 DHT11_read(int gpio_pin);



#endif
