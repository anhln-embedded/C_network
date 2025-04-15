#include "route_ipv4.h"

static route_ipv4_node_t *g_phead = NULL;
static route_ipv4_node_t *g_ptail = NULL;

static route_ipv4_node_t *link_list_create_node(route_ipv4_t route);
static void link_list_push_back(route_ipv4_t route);
static void link_list_delete_list();
static void route_ipv4_build(void);

static void hex_to_ip(const char *hex, char *ip);

void route_ipv4_init(void)
{
    route_ipv4_build();
    log_debug("Route IPv4 module initialized");
}
void route_ipv4_get(route_ipv4_node_t **head)
{
    *head = g_phead;
}
void route_ipv4_cleanup(void)
{
    link_list_delete_list();
}

static route_ipv4_node_t *link_list_create_node(route_ipv4_t route)
{
    route_ipv4_node_t *new_node = (route_ipv4_node_t *)malloc(sizeof(route_ipv4_node_t));
    if (new_node == NULL)
    {
        log_error("Memory allocation failed");
        link_list_delete_list();
        return NULL;
    }
    new_node->route = route;
    new_node->next = NULL;
    return new_node;
}

static void link_list_delete_list()
{
    route_ipv4_node_t *current = g_phead;
    route_ipv4_node_t *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    g_phead = NULL;
    g_ptail = NULL;
    log_debug("Route IPv4 node deleted");
}

static void link_list_push_back(route_ipv4_t route)
{
    route_ipv4_node_t *new_node = link_list_create_node(route);
    if (new_node == NULL)
    {
        log_error("Failed to create new route node");

        return;
    }
    if (g_phead == NULL)
    {
        g_phead = new_node;
        g_ptail = new_node;
    }
    else
    {
        g_ptail->next = new_node;
        g_ptail = new_node;
    }
    log_debug("Route IPv4 node created");
}


static void route_ipv4_build(void)
{
    FILE *fp = fopen("/proc/net/route", "r");
    static char line[256];
    route_ipv4_t route;
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

            int matched = sscanf(line, "%15s %8s %8s %X %*s %*s %*s %8s",
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

            hex_to_ip(dest_hex, route.destination);
            hex_to_ip(gw_hex, route.gateway);
            hex_to_ip(mask_hex, route.mask);
            route.is_default = (flags & 0x2) != 0;
            
            log_debug("Parsed route line: %s", line);
            log_debug("Parsed route destination: %s", route.destination);
            log_debug("Parsed route gateway: %s", route.gateway);
            log_debug("Parsed route mask: %s", route.mask);
            log_debug("Parsed route is_default: %s", route.is_default ? "true" : "false");
            link_list_push_back(route);
        }
    }
}

static void hex_to_ip(const char *hex, char *ip)
{
    unsigned int raw_ip;
    sscanf(hex, "%x", &raw_ip);

    unsigned char b1 = (raw_ip & 0x000000FF);
    unsigned char b2 = (raw_ip & 0x0000FF00) >> 8;
    unsigned char b3 = (raw_ip & 0x00FF0000) >> 16;
    unsigned char b4 = (raw_ip & 0xFF000000) >> 24;

    sprintf(ip, "%u.%u.%u.%u", b1, b2, b3, b4);
}
