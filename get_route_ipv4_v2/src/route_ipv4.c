#include "route_ipv4.h"

LIST_HEAD(l_route_ipv4);

static void add_block_route_ipv4(const char *destination, const char *gateway, const char *mask, bool is_default);
static void hex_to_ip(const char *hex, char *ip);

void route_ipv4_build(void)
{
    FILE *fp = fopen("/proc/net/route", "r");
    char line[256];
    if (fp == NULL)
    {
        log_error("Failed to open /proc/net/route");
    }
    else
    {
        log_debug("Opened /proc/net/route");
        fgets(line, sizeof(line), fp);
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            char iface[16], dest_hex[16], gw_hex[16], mask_hex[16];
            unsigned int flags;

            int matched = SAFE_SSCANF(line, "%15s %8s %8s %X %*s %*s %*s %8s",
                                 iface, dest_hex, gw_hex, &flags, mask_hex);

            if (matched < 4)
            {
                log_error("Failed to parse line: %s", line);
                continue;
            }

            if (!(flags & 0x1))
            {
                log_debug("Skipping line: %s", line);
                continue;
            }
            hex_to_ip(dest_hex, dest_hex);
            hex_to_ip(gw_hex, gw_hex);
            hex_to_ip(mask_hex, mask_hex);
            add_block_route_ipv4(dest_hex, gw_hex, mask_hex, (flags & 0x2) != 0);
        }
        fclose(fp);
    }
    log_debug("Route IPv4 build completed");
    log_debug("Route IPv4 list head: %p", &l_route_ipv4);
    log_debug("Route IPv4 list head next: %p", l_route_ipv4.next);
    log_debug("Route IPv4 list head prev: %p", l_route_ipv4.prev);
    log_debug("Route IPv4 list count: %d", list_count(&l_route_ipv4));

}

list_head_t* route_ipv4_get_head(void)
{
    return (&l_route_ipv4);
}

void route_ipv4_cleanup(void)
{
    route_ipv4_t *route;
    list_head_t *pos, *n;

    LIST_FOR_EACH_SAFE(pos, n, &l_route_ipv4)
    {
        route = LIST_ENTRY(pos, route_ipv4_t, list);
        list_del(&route->list);
        free(route);
    }
    log_debug("Route IPv4 cleanup completed");
    log_debug("Route IPv4 list head: %p", &l_route_ipv4);
    log_debug("Route IPv4 list head next: %p", l_route_ipv4.next);
    log_debug("Route IPv4 list head prev: %p", l_route_ipv4.prev);
    log_debug("Route IPv4 list count: %d", list_count(&l_route_ipv4));
    log_debug("Route IPv4 cleanup completed");
}

static void add_block_route_ipv4(const char *destination, const char *gateway, const char *mask, bool is_default)
{
    route_ipv4_t *route = malloc(sizeof(route_ipv4_t));
    if (route)
    {
        SAFE_STRNCPY(route->destination, destination, sizeof(route->destination));
        SAFE_STRNCPY(route->gateway, gateway, sizeof(route->gateway));
        SAFE_STRNCPY(route->mask, mask, sizeof(route->mask));
        route->is_default = is_default;
        list_add_tail(&route->list, &l_route_ipv4);
    }
}


static void hex_to_ip(const char *hex, char *ip)
{
    unsigned int ip_int;
    SAFE_SSCANF(hex, "%X", &ip_int);
    snprintf(ip, 16, "%u.%u.%u.%u",
             ip_int & 0xFF,
             (ip_int >> 8) & 0xFF,
             (ip_int >> 16) & 0xFF,
             (ip_int >> 24) & 0xFF);
}