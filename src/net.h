#ifndef H_NET
#define H_NET

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "log.h"

typedef struct {
    int server_fd;

    char buffer[1024];

    struct sockaddr_in server_addr;
    socklen_t addr_len;

    int status;
    bool connected;

    bool err;
    char err_msg[512];
} cnet_t;

// Simple helpers
inline static void send_str(cnet_t* c, const char* str)
{
    write(c->server_fd, str, strlen(str));
}

inline static void read_str(cnet_t* c)
{
    read(c->server_fd, c->buffer, sizeof(c->buffer));
}

void init_net(cnet_t*);

#endif
