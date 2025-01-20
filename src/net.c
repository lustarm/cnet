#include <assert.h>

#include "net.h"

inline static void send_str(cnet_t* c, const char* str)
{
    write(c->server_fd, str, strlen(str));
}

inline static void read_str(cnet_t* c)
{
    read(c->server_fd, c->data, sizeof(c->data));
}

void init_net(cnet_t* client)
{
    // Make sure we never call this again
    // and if we do we die
    assert(client->connected == false);

    client->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client->server_fd < 0)
    {
        client->err = true;
        strcpy(client->err_msg, "Failed to create socket");
        return;
    }

    if(setsockopt(client->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                  &(int){1}, sizeof(int)))
    {
        client->err = true;
        strcpy(client->err_msg, "Failed to set socket option");
        return;
    }

    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(8000);

    if(inet_pton(AF_INET, "127.0.0.1", &client->server_addr.sin_addr) <= 0)
    {
        client->err = true;
        strcpy(client->err_msg, "Invalid address / Address not supported");
        return;
    }

    client->status = connect(client->server_fd,
                                      (struct sockaddr*)&client->server_addr,
                                       sizeof(client->server_addr));
    if(client->status < 0)
    {
        client->err = true;
        strcpy(client->err_msg, "Failed to connect to server");
        return;
    }

    client->connected = true;

    LOG_INFO("Successfully connected to server");
}
