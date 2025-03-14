#ifndef H_CLIENT
#define H_CLIENT

#include "net.h"

#include <unistd.h>

typedef struct {
    cnet_t net;

    char name[16];
    char hash[32];
    bool err;
    bool running;
}client_t;

void init_client(client_t*);
void clean_client(client_t*);

#endif
