#ifndef H_CLIENT
#define H_CLIENT

#include "net.h"

#include <unistd.h>

typedef struct {
    cnet_t net;

    char hash[32];

    bool err;
    char err_msg[256];

    bool running;
}client_t;

void init_client(client_t* client);

#endif
