#include "clnt.h"
#include "srw.h"
#include <string.h>

int main(int argc, char *argv[]) {
    // ./cnet "name"
    client_t client;
    memcpy(client.name, argv[0], 16);

    init_client(&client);

    start_srw(&client);

    clean_client(&client);
    return 0;
}
