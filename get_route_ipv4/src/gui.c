#include "gui.h"

static route_ipv4_node_t *g_phead = NULL;

static void gui_display_header(void);
static void gui_display_route(route_ipv4_node_t *node);
static void gui_display_footer(void);

void gui_init(void)
{
    route_ipv4_init();
    route_ipv4_get(&g_phead);
}
void gui_display(void)
{
    gui_display_header();
    route_ipv4_node_t *current = g_phead;
    while (current != NULL)
    {
        gui_display_route(current);
        current = current->next;
    }
    gui_display_footer();
}

void gui_cleanup(void)
{
}

static void gui_display_header(void)
{
}
static void gui_display_route(route_ipv4_node_t *node)
{
    printf("Interface: %s\n", node->route.iface);
    printf("Destination: %s\n", node->route.destination);
    printf("Gateway: %s\n", node->route.gateway);
    printf("Mask: %s\n", node->route.mask);
    printf("Is Default: %s\n", node->route.is_default ? "Yes" : "No");
    printf("\n");
}
static void gui_display_footer(void)
{
}