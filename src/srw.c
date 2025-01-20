/* == Socket Read Write (SRW) == */
#include <assert.h>
#include <string.h>

#include "srw.h"
#include "log.h"

// Simple helpers
void send_str(cnet_t* c, const char* str)
{
    write(c->server_fd, str, strlen(str));
}

void read_str(cnet_t* c)
{
    read(c->server_fd, c->buffer, sizeof(c->buffer));
}

void start_srw(client_t *client)
{

    while(1)
    {
        assert(client != NULL);
        assert(client->net.connected != false);
        assert(client->net.err != true);

        memset(client->net.buffer, 0, 1024);
        read_str(&client->net);
        if(memcmp(client->net.buffer, "\n", strlen("\n")) == 0)
        {
            LOG_INFO("Buffer is nothing skipping");
        }
    }
}


