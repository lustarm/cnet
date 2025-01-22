#include "srw.h"

int main(int _argc, char *argv[])
{
    // redundent, used to make warning go away
    (void)_argc;
    // ./cnet "name" will be changed later to lazy rn
    client_t client;
    memcpy(client.name, argv[0], 16);

    init_client(&client);

    start_srw(&client);

    clean_client(&client);
    return 0;
}
