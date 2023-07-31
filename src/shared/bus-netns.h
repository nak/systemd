#pragma once


typedef struct NetNs{
    const char* const netns;
    unsigned char in_netns;
} NetNs;

extern const NetNs * const network_netns;

const char* bus_determine_netns(void);