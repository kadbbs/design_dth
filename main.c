#include "display.h"
#include "front.h"
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
 


int mian(int argc,char *argv[]){

	if (2 != argc)

	{

		printf("Usge: %s <gpio_pin>\n", argv[0]);

		return 0;

	}



	if (-1 == wiringPiSetup())

	{

		printf("Setup WiringPi failed!\n");



		return 1;

	}

	
	delay(1000); // 毫秒
 
	wiringPiSetupSys();
 
	pinMode(LED, OUTPUT);
 
	i2cHand = wiringPiI2CSetup(I2C_ADDR);	/*加载i2c设备*/
	OLED_Init(i2cHand);
 


	while(1)

	{

		GPIO_init(atoi(argv[1]));



		DHT11_start(atoi(argv[1]));



		if (DHT11_read(atoi(argv[1])))

		{

			printf("RH:%d.%d\n", (databuf >> 24) & 0xff, (databuf >> 16) & 0xff); 

			printf("TMP:%d.%d\n", (databuf >> 8) & 0xff, databuf & 0xff);



			databuf = 0;

		}

		else

		{

			printf("Sensor dosent ans!\n");

			databuf = 0;

		}



		sleep(3);

	}

	
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





 



















	exit(0);
}
