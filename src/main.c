#include "clnt.h"
#include "srw.h"

int main() {
    client_t client;

    init_client(&client);

    start_srw(&client);

    clean_client(&client);
    return 0;
}
