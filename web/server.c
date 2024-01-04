#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#define PORT 7666

char buffer[128] = {0};
void server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
//    char buffer[128] = {0};
    const char* message = "Hello from server!";

    // 创建socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


	int opt=1;
    // 设置socket选项 - 端口复用
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
	    perror("setsockopt failed");
	    exit(EXIT_FAILURE);
    }



    // 设置socket地址和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定socket到地址和端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // 接受连接请求
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // 从客户端接收数据
    while(1){
	    read(new_socket, buffer, 128);
	    printf("RPI Client: %s\n", buffer);
    }
#if 0
    // 向客户端发送消息
    send(new_socket, message, strlen(message), 0);
    printf("Message sent: %s\n", message);
#endif
    // 关闭socket
    close(new_socket);
    close(server_fd);
    return 0;
}

