/* SPDX-License-Identifier: LGPL-2.1-or-later */
#include <search.h>

#include "bus-locator.h"
#include "macro.h"

const BusLocator* const bus_home_mgr = &(BusLocator){
        .destination = "org.freedesktop.home1",
        .path = "/org/freedesktop/home1",
        .interface = "org.freedesktop.home1.Manager",
};

const BusLocator* const bus_import_mgr = &(BusLocator){
        .destination ="org.freedesktop.import1",
        .path = "/org/freedesktop/import1",
        .interface = "org.freedesktop.import1.Manager"
};

const BusLocator* const bus_locale = &(BusLocator){
        .destination = "org.freedesktop.locale1",
        .path = "/org/freedesktop/locale1",
        .interface = "org.freedesktop.locale1"
};

const BusLocator* const bus_login_mgr = &(BusLocator){
        .destination = "org.freedesktop.login1",
        .path = "/org/freedesktop/login1",
        .interface = "org.freedesktop.login1.Manager"
};

const BusLocator* const bus_machine_mgr = &(BusLocator){
        .destination ="org.freedesktop.machine1",
        .path = "/org/freedesktop/machine1",
        .interface = "org.freedesktop.machine1.Manager"
};

static char _network_destination[128] =  "org.freedesktop.network1";
static char _network_interface[128 + 32] =  "org.freedesktop.network1.Manager";

static BusLocator _bus_network_mgr = (BusLocator){
        .destination = _network_destination,
        .path = "/org/freedesktop/network1",
        .interface = _network_interface
};
const BusLocator* const bus_network_mgr = &_bus_network_mgr;

const BusLocator* const bus_portable_mgr = &(BusLocator){
        .destination = "org.freedesktop.portable1",
        .path = "/org/freedesktop/portable1",
        .interface = "org.freedesktop.portable1.Manager"
};

const BusLocator* const bus_resolve_mgr = &(BusLocator){
        .destination = "org.freedesktop.resolve1",
        .path = "/org/freedesktop/resolve1",
        .interface = "org.freedesktop.resolve1.Manager"
};

const BusLocator* const bus_systemd_mgr = &(BusLocator){
        .destination = "org.freedesktop.systemd1",
        .path = "/org/freedesktop/systemd1",
        .interface = "org.freedesktop.systemd1.Manager"
};

const BusLocator* const bus_timedate = &(BusLocator){
        .destination = "org.freedesktop.timedate1",
        .path = "/org/freedesktop/timedate1",
        .interface = "org.freedesktop.timedate1"
};

/* Shorthand flavors of the sd-bus convenience helpers with destination,path,interface strings encapsulated
 * within a single struct. */
int bus_call_method_async(
                sd_bus *bus,
                sd_bus_slot **slot,
                const BusLocator *locator,
                const char *member,
                sd_bus_message_handler_t callback,
                void *userdata,
                const char *types, ...) {

        va_list ap;
        int r;

        assert(locator);

        va_start(ap, types);
        r = sd_bus_call_method_asyncv(bus, slot, locator->destination, locator->path, locator->interface, member, callback, userdata, types, ap);
        va_end(ap);

        return r;
}

int bus_call_method(
                sd_bus *bus,
                const BusLocator *locator,
                const char *member,
                sd_bus_error *error,
                sd_bus_message **reply,
                const char *types, ...) {

        va_list ap;
        int r;

        assert(locator);

        va_start(ap, types);
        r = sd_bus_call_methodv(bus, locator->destination, locator->path, locator->interface, member, error, reply, types, ap);
        va_end(ap);

        return r;
}

int bus_get_property(
                sd_bus *bus,
                const BusLocator *locator,
                const char *member,
                sd_bus_error *error,
                sd_bus_message **reply,
                const char *type) {

        assert(locator);

        return sd_bus_get_property(bus, locator->destination, locator->path, locator->interface, member, error, reply, type);
}

int bus_get_property_trivial(
                sd_bus *bus,
                const BusLocator *locator,
                const char *member,
                sd_bus_error *error,
                char type, void *ptr) {

        assert(locator);

        return sd_bus_get_property_trivial(bus, locator->destination, locator->path, locator->interface, member, error, type, ptr);
}

int bus_get_property_string(
                sd_bus *bus,
                const BusLocator *locator,
                const char *member,
                sd_bus_error *error,
                char **ret) {

        assert(locator);

        return sd_bus_get_property_string(bus, locator->destination, locator->path, locator->interface, member, error, ret);
}

int bus_get_property_strv(
                sd_bus *bus,
                const BusLocator *locator,
                const char *member,
                sd_bus_error *error,
                char ***ret) {

        assert(locator);

        return sd_bus_get_property_strv(bus, locator->destination, locator->path, locator->interface, member, error, ret);
}

int bus_set_property(
                sd_bus *bus,
                const BusLocator *locator,
                const char *member,
                sd_bus_error *error,
                const char *type, ...) {

        va_list ap;
        int r;

        assert(locator);

        va_start(ap, type);
        r = sd_bus_set_propertyv(bus, locator->destination, locator->path, locator->interface, member, error, type, ap);
        va_end(ap);

        return r;
}

int bus_match_signal(
                sd_bus *bus,
                sd_bus_slot **ret,
                const BusLocator *locator,
                const char *member,
                sd_bus_message_handler_t callback,
                void *userdata) {

        assert(locator);

        return sd_bus_match_signal(bus, ret, locator->destination, locator->path, locator->interface, member, callback, userdata);
}

int bus_match_signal_async(
                sd_bus *bus,
                sd_bus_slot **ret,
                const BusLocator *locator,
                const char *member,
                sd_bus_message_handler_t callback,
                sd_bus_message_handler_t install_callback,
                void *userdata) {

        assert(locator);

        return sd_bus_match_signal_async(bus, ret, locator->destination, locator->path, locator->interface, member, callback, install_callback, userdata);
}

int bus_message_new_method_call(
                sd_bus *bus,
                sd_bus_message **m,
                const BusLocator *locator,
                const char *member) {

        assert(locator);

        return sd_bus_message_new_method_call(bus, m, locator->destination, locator->path, locator->interface, member);
}

static char _network_netns[32] = "";

static NetNs * const __network_netns = &(NetNs){
        .netns = _network_netns,
        .in_netns = 0
};

const NetNs * const network_netns = __network_netns;

static const char* _determine_netns(void){
        static bool inited = false;
        static char * netns = &_network_netns[0];
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
                printf("Call to /usr/bin/ip failed. Assuming not in namespace");
                return NULL;
        }
        if (strlen(netns) == 0){
                return NULL;
        }
       __network_netns->in_netns = 1;
        return netns;
}

__attribute__((constructor))
static void _init_bus_network_mgr(void){
        //if (getenv("SYSTEMD_DEBUG")){
        log_set_max_level(LOG_DEBUG);
        //}
        const char * const netns = _determine_netns();
        if (!netns){
                return;
        }
        strcpy((char*) &_network_netns[0], netns);
        const size_t base_len = strlen(_bus_network_mgr.destination);
        const size_t netns_len = strlen(netns);
        if (base_len + netns_len + 1 >= 128){
                printf("Name too long %s.%s", _bus_network_mgr.destination, netns);
        } else if (base_len + netns_len + 9 > 128 + 32){
                printf("Name too long %s.%s.Manager", _bus_network_mgr.destination, netns);
        }
        _network_destination[base_len] = '.';
        strcpy(_network_destination + base_len + 1, netns);
        strcpy(_network_destination + base_len + 1, netns);
        strcpy(_network_interface, _network_destination);
        _network_interface[base_len] = '.';
        _network_interface[base_len + netns_len + 1] = '.';
        strcpy(_network_interface + base_len + 2 + netns_len, "Manager");
}


const char* bus_network_cmpnt(const char* const name){
        static struct hsearch_data cmpnts = {0};
        static bool inited = false;
        if (!inited){
                hcreate_r(100, &cmpnts);
                inited = true;
        }
        ENTRY *item;
        ENTRY key ={
                .key = (char*) name,
                .data = NULL
        };
        hsearch_r(key, FIND, &item, &cmpnts);
        if (item){
                return item->data;
        }
        if (!name || (strlen(name) == 0)){
                return bus_network_mgr->destination;
        }
        const size_t len = strlen(bus_network_mgr->destination) + 1 + strlen(name);
        char* result = malloc(len + 1);
        memset(result, 0, len+1);
        strcpy(result, bus_network_mgr->destination);
        result[strlen(bus_network_mgr->destination)] = '.';
        strcpy(result + strlen(result), name);
        key.data = result;
        hsearch_r(key, ENTER, &item, &cmpnts);
        return (const char*) result;
}

