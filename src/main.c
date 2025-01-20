#include "clnt.h"

int main() {
    client_t client;
    init_client(&client);

    while (client.running)
    {
        LOG_ERROR("%s", client.err_msg);
        sleep(5);
    }

error:
    LOG_ERROR("%s", client.err_msg);
    return 0;
}
