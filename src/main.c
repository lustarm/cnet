#include "clnt.h"
#include "net.h"
#include <unistd.h>

int main() {
    client_t client;
    init_client(&client);

    while (client.running)
    {
        if(client.err) goto cleanup;
        read_str(&client.net);
        LOG_DEBUG("Read successfully: ", client.net.buffer);
    }

cleanup:
    // Redundent? I don't care.
    client.running = false;
    client.net.connected = false;
    close(client.net.server_fd);
    return 0;
}
