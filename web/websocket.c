#include <libwebsockets.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);
static int callback_websockets(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);

static struct lws_protocols protocols[] = {
    {"http-only", callback_http, 0, 0},
    {"websocket", callback_websockets, 0, 0},
    {NULL, NULL, 0, 0} /* ç»æåè®®æ°ç» */
};

int number = 0;  // è¦å®æ¶æ´æ°çæ°å­

int main() {
    struct lws_context_creation_info info;
    struct lws_context *context;
    const char *interface = NULL;
    int port = PORT;
    const char *cert_path = NULL;
    const char *key_path = NULL;
    int opts = 0;

    memset(&info, 0, sizeof(info));

    info.port = port;
    info.iface = interface;
    info.protocols = protocols;
    info.ssl_cert_filepath = cert_path;
    info.ssl_private_key_filepath = key_path;
    info.gid = -1;
    info.uid = -1;
    info.options = opts;

    context = lws_create_context(&info);
    if (!context) {
        fprintf(stderr, "libwebsocket init failed\n");
        return -1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        lws_service(context, 50);

        // Simulate updating the number every second
        usleep(1000000);  // Sleep for 1 second
        number++;

        lws_callback_on_writable_all_protocol(context, &protocols[1]);
    }

    lws_context_destroy(context);

    return 0;
}

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    return 0;
}

static int callback_websockets(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            printf("Client connected\n");
            
            // Send the current number to the client
            {
                char message[MAX_BUFFER_SIZE];
                snprintf(message, sizeof(message), "%d", number);
                lws_write(wsi, (unsigned char *)message, strlen(message), LWS_WRITE_TEXT);
            }
            break;

        case LWS_CALLBACK_RECEIVE:
		printf("LWS_CALLBACK_RECEIVE\n");
            // Handle received data, in this example, we just ignore it
            break;

        case LWS_CALLBACK_SERVER_WRITEABLE:
            // Send the current number to clients
            {
                char message[MAX_BUFFER_SIZE];
                snprintf(message, sizeof(message), "%d", number);
                lws_write(wsi, (unsigned char *)message, strlen(message), LWS_WRITE_TEXT);
            }
            break;

        default:
            break;
    }

    return 0;
}
