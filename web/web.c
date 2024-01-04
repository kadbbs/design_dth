#include <libwebsockets.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "web.h"
#include "server.h"
// WebSocket 数据的结构体，用于存储每个会话的数据
struct per_session_data {
};
// WebSocket 服务器消息的回调函数
int callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
	switch (reason) {
		case LWS_CALLBACK_ESTABLISHED: // 处理新连接事件
			// 添加计时器，每秒发送一个时间戳
			lws_callback_on_writable(wsi);
			break;
		case LWS_CALLBACK_SERVER_WRITEABLE: // 处理发送数据事件
			// 发送时间戳
			{
				//sleep(1);
				
					lws_write(wsi, buffer, 9, LWS_WRITE_TEXT);
					//memset(buffer,0,128);
					lws_callback_on_writable(wsi);
				
			}
			break;
			// 其他事件省略
	}
	return 0;
}



void web(){
	
// 创建 WebSocket 协议
    static struct lws_protocols protocols[] = {
        {
            "websocket", // 协议名称，需要和前端代码中的 WebSocket 协议相同
            callback, // 回调函数指针
            sizeof(struct per_session_data), // 每个会话（连接）所拥有的数据大小
            0, // 没有更多的协议参数
            NULL, NULL, NULL
        },
        { NULL, NULL, 0, 0 } // 协议列表以 NULL 结尾
    };

    // 创建 WebSocket 上下文
    struct lws_context_creation_info info = {
        .port = 3001, // 监听端口号
        .protocols = protocols // 协议列表
    };
    struct lws_context *context = lws_create_context(&info);

    // 判断 WebSocket 上下文是否创建成功
    if (!context) {
        printf("Failed to create WebSocket context.\n");
        return -1;
    }

    // 进入循环，等待 WebSocket 连接
    while (1) {
        lws_service(context, 50);
	sleep(1);
    }

    // 清理并关闭 WebSocket 上下文
    lws_context_destroy(context);

    return 0;







}




#if 0
int main(int argc, char **argv) {
    // 创建 WebSocket 协议
	number=0;
    static struct lws_protocols protocols[] = {
        {
            "websocket", // 协议名称，需要和前端代码中的 WebSocket 协议相同
            callback, // 回调函数指针
            sizeof(struct per_session_data), // 每个会话（连接）所拥有的数据大小
            0, // 没有更多的协议参数
            NULL, NULL, NULL
        },
        { NULL, NULL, 0, 0 } // 协议列表以 NULL 结尾
    };

    // 创建 WebSocket 上下文
    struct lws_context_creation_info info = {
        .port = 3001, // 监听端口号
        .protocols = protocols // 协议列表
    };
    struct lws_context *context = lws_create_context(&info);

    // 判断 WebSocket 上下文是否创建成功
    if (!context) {
        printf("Failed to create WebSocket context.\n");
        return -1;
    }

    // 进入循环，等待 WebSocket 连接
    while (1) {
        lws_service(context, 50);
	number++;
	sleep(1);
    }

    // 清理并关闭 WebSocket 上下文
    lws_context_destroy(context);

    return 0;
}
#endif


