#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bus-netns.h"
#include "log.h"

static char _network_netns[32] = "";

static NetNs * const __network_netns = &(NetNs){
        .netns = _network_netns,
        .in_netns = false
};

const NetNs * const network_netns = __network_netns;

const char* bus_determine_netns(void){
    static bool inited = false;
    static char * netns = &_network_netns[0];
    if (access("/usr/sbin/ip", F_OK) != 0){
        return NULL;
    }
    if (inited){
        return strlen(netns) == 0?NULL:netns;
    }
    FILE* fp = popen("/usr/sbin/ip netns identify", "r");
    while (fgets(netns, sizeof(netns), fp) != NULL) {
        if (strlen(netns) != 0){
            netns[strlen(netns)-1] = 0;
            break;
        }
    }
    inited = true;
    if (pclose(fp) != 0){
        log_debug("Call to /usr/sbin/ip failed. Assuming not in namespace");
        return NULL;
    }
    if (strlen(netns) == 0){
        return NULL;
    }
    strcpy((char*) &_network_netns[0], netns);
    __network_netns->in_netns = true;
    return netns;
}
