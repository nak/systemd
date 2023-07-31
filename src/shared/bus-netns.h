#pragma once
#include <stdbool.h>

typedef struct NetNs{
    const char* const netns;
    bool in_netns;
} NetNs;

extern const NetNs * const network_netns;

const char* bus_determine_netns(void);