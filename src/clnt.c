#include <assert.h>

#include "clnt.h"
#include "log.h"
#include "net.h"
#include "hash.h"

inline static void check_hash(client_t* client)
{
    char hash[32];
    if (sha256_file("./src/main.c", hash) != 0)
    {
        client->err = true;
        strcpy(client->err_msg, "Failed to calculate hash");
        return;
    }

    char computed_hash[65];  // 64 characters + null terminator
    hash_to_hex(hash, computed_hash);

    LOG_DEBUG("Hash found: %s", computed_hash);
    LOG_DEBUG("Predefined hash: %s", client->hash);

    if (memcmp(computed_hash, client->hash, 64) != 0)  // Compare only the 64 characters
    {
        LOG_INFO("Hash does NOT match the predefined hash. Changing old hash");
        memcpy(client->hash, computed_hash, 65);  // Ensure we copy the null terminator
        return;
    }
}

void init_client(client_t* client)
{
    // Make sure we don't call twice
    assert(client->running == false);
    client->running = true;

    strcpy(client->hash,
           "024b849af22b3177a4a120d15133efeb474bb05b13d56805fd8d7aecfae808e8");
    check_hash(client);

    init_net(&client->net);
    if(client->net.err)
    {
        client->err = true;
        strcpy(client->err_msg, client->net.err_msg);
        return;
    }
}


