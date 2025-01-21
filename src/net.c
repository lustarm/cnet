#include <assert.h>

#include "net.h"

void init_net(cnet_t* net)
{
    while(!net->connected)
    {
        // Make sure we never call this again
        // and if we do we die
        assert(net->connected == false);
        assert(net->err == false);

        net->server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(net->server_fd < 0)
        {
            net->err = true;
            LOG_ERROR("Failed to create socket");
            exit(-1);
        }

        net->server_addr.sin_family = AF_INET;
        net->server_addr.sin_port = htons(8000);

        if(inet_pton(AF_INET, "127.0.0.1", &net->server_addr.sin_addr) <= 0)
        {
            net->err = true;
            LOG_ERROR("Invalid address / Address not supported");
            exit(-1);
        }

        net->status = connect(net->server_fd,
                              (struct sockaddr*)&net->server_addr,
                              sizeof(net->server_addr));
        if(net->status < 0)
        {
            // net->err = true;
            LOG_ERROR("Failed to connect to server trying again in 5 seconds");
            sleep(5);
            continue;
        }

        net->connected = true;
        LOG_INFO("Successfully connected to server");
        break;
    }
}
