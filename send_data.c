#include <stdio.h>
#include "display.h"
#include "font.h"
#include "dht11.h"


#include <stdlib.h>

#include <string.h>

#include <sys/socket.h>

#include <arpa/inet.h>

#include <unistd.h>

#include "send_data.h"

#define PORT 7666

#define SERVER_IP "10.42.0.1"

//extern uint32 databuff;


int sock ;
void s_init(){

	//int sock = 0;

	struct sockaddr_in serv_addr;

	char buffer[32] = {0};

	const char* message = "Hello from client!";



	// 创建socket

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

		perror("socket creation failed");

		exit(EXIT_FAILURE);

	}



	// 设置服务器地址和端口

	serv_addr.sin_family = AF_INET;

	serv_addr.sin_port = htons(PORT);



	// 将IP地址从字符串转换为二进制格式

	if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {

		perror("invalid address or address not supported");

		exit(EXIT_FAILURE);

	}



	// 连接服务器

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {

		perror("connection failed");

		exit(EXIT_FAILURE);

	}




};


void senddata(char *buffer,int size) {
		    sprintf(buffer,"%d#%d#%d#%d", (databuf >> 24) & 0xff , (databuf >> 16) & 0xff , (databuf >> 8) & 0xff, databuf & 0xff);
		    send(sock, buffer, size, 0);

		    printf("Message sent: %s\n", buffer);
    }

#if 0
    // 从服务器接收数据

    read(sock, buffer, 1024);

    printf("Server: %s\n", buffer);

#endif

    // 关闭socket





