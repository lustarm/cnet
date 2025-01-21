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
    ssize_t b = read(c->server_fd, c->buffer, sizeof(c->buffer));
    c->len = b;
}

void strip_newline(char *buffer, size_t buffer_size)
{
    for (size_t i = 0; i < buffer_size; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0'; // Replace newline with null terminator
            break;           // Exit loop since we only need to strip one newline
        }
    }
}

bool check(cnet_t* net)
{
    if (net->len <= 0)
    {
        if (net->len == 0)
        {
            LOG_INFO("Client disconnected, trying to connect");
            net->connected = false;
            return true;
        }
        else
        {
            LOG_ERROR("Error reading from client, exiting SRW");
            net->connected = false;
            net->err = true;
            return true;
        }
    }

    return false;
}

void start_srw(client_t *client)
{
    ssize_t s;

    while(1)
    {
        assert(client != NULL);
        assert(client->net.connected == true);
        assert(client->net.err != true);

        memset(client->net.buffer, 0, 1024);

        read_str(&client->net);
        if(check(&client->net)) break;

        if(memcmp(client->net.buffer, "\n", strlen("\n")) == 0)
        {
            LOG_INFO("Buffer is nothing skipping");
            continue;
        }

        strip_newline(client->net.buffer, sizeof(client->net.buffer));

        LOG_DEBUG(client->net.buffer);
    }
}


