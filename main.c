#include "display.h"
#include "font.h"
#include "dht11.h"
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
#include "send_data.h"
#include <pthread.h>
//int i2cHand;
#define TMP  60



int main(int argc,char *argv[]){
	if (2 > argc)
	{
		printf("Usge: %s <gpio_pin>\n", argv[0]);
		return 0;
	}
	if (-1 == wiringPiSetup())
	{
		printf("Setup WiringPi failed!\n");
		return 1;
	}
	int tmp_limit=TMP;
	if(argc==3){
		tmp_limit=atoi(argv[2]);
	}

		printf("tmp_argv:%d",tmp_limit);
	delay(1000); // 毫秒
	wiringPiSetupSys();
	pinMode(LED, OUTPUT);
	i2cHand = wiringPiI2CSetup(I2C_ADDR);	/*加载i2c设备*/
	OLED_Init(i2cHand);
	OLED_CLS();
	 //show_str( (u8*)"Hello!!!", FONT_8x16, 0, 64-16 );
	// show_char((u8*)&F8X16['A'-' '],6,8,8,8);
		
#if 0	
	for(int i=0;i<64;i++){
	
	}	
		oled_draw_point(0,32,1);	
		oled_draw_point(0,16,1);	
	
#endif

	//OLED_ShowStr(1,0,ch,1);

	u8 rh[64];
	u8 tmp[64];
	
	//pthread_t tid;
	//pthread_create(&tid,NULL,fun,NULL);

	s_init();
	char sendbuf[32];
	while(1)
	{
		GPIO_init(atoi(argv[1]));

		DHT11_start(atoi(argv[1]));

		if (DHT11_read(atoi(argv[1])))
		{
			memset(sendbuf,0,32);
		    	sprintf(sendbuf,"%d#%d#%d#%d", (databuf >> 24) & 0xff , (databuf >> 16) & 0xff , (databuf >> 8) & 0xff, databuf & 0xff);
			senddata(sendbuf,strlen(sendbuf));
			printf("RH:%d.%d\n", (databuf >> 24) & 0xff, (databuf >> 16) & 0xff); 
			memset(rh,0,64);
			sprintf(rh,"RH:%d.%d",(databuf >> 24) & 0xff, (databuf >> 16) & 0xff);
			OLED_ShowStr(1,0,rh,1);
			printf("TMP:%d.%d\n", (databuf >> 8) & 0xff, databuf & 0xff);

			if(((databuf >> 8) & 0xff)>tmp_limit){
				digitalWrite(27, 0); // output a high level
			}else{
				digitalWrite(27, 1); // output a high level
			}
			memset(tmp,0,64);
			sprintf(tmp,"TMP:%d.%d", (databuf >> 8) & 0xff, databuf & 0xff);
			OLED_ShowStr(1,4,tmp,1);
			databuf = 0;

		}
		else
		{
			printf("Sensor dosent ans!\n");
			databuf = 0;
		}
		sleep(3);
	}

#if 0	
	while (1)
	{
		digitalWrite(LED, HIGH);  //开
		delay(500); // 毫秒
		digitalWrite(LED, LOW);	  //关
		delay(500);
 
		OLED_Full();
		delay(1000);
 
		OLED_CLS();
		delay(1000); // 毫秒
 
	} 

#endif
	exit(0);
}
