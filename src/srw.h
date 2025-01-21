/* == Socket Read Write (SRW) == */
#pragma once

#include "net.h"
#include "clnt.h"

void start_srw(client_t*);

// Simple helpers
void send_str(cnet_t* c, const char* str);
void read_str(cnet_t* c);

