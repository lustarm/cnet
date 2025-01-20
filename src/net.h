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

    char data[1024];

    struct sockaddr_in server_addr;
    socklen_t addr_len;

    int status;
    bool connected;

    bool err;
    char err_msg[512];
} cnet_t;

void init_net(cnet_t*);

#endif
