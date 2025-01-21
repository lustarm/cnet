/* == Socket Read Write (SRW) == */
#include <assert.h>
#include <string.h>

#include "srw.h"
#include "log.h"
#include "net.h"

// Simple helpers
void send_str(cnet_t* c, const char* str)
{
    c -> len = write(c->server_fd, str, strlen(str));
}

void read_str(cnet_t* c)
{
    c->len = read(c->server_fd, c->buffer, sizeof(c->buffer));
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
            LOG_INFO("Client disconnected");
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
    // On func entry it should be connected
    assert(client->net.connected);
    // Auth
    send_str(&client->net, "\x00\x00\x00\x01");
    LOG_DEBUG("Sent authorization to server");

    while(true)
    {
        if(!client->net.connected)
        {
            LOG_DEBUG("Client not connected; restarting client net");
            sleep(5);
            client->net.connected = false;
            start_net(&client->net);
        }

        assert(client != NULL);
        assert(client->net.connected == true);
        assert(client->net.err != true);

        memset(client->net.buffer, 0, 1024);

        read_str(&client->net);
        if(check(&client->net)) continue;

        if(memcmp(client->net.buffer, "\n", strlen("\n")) == 0)
        {
            LOG_INFO("Buffer is nothing skipping");
            continue;
        }
        // For now just use this
        strip_newline(client->net.buffer, sizeof(client->net.buffer));
        LOG_DEBUG(client->net.buffer);
    }
}


