#include "gui.h"

static route_ipv4_node_t *g_phead = NULL;

static void gui_display_header(void);
static void gui_display_route(route_ipv4_node_t *node, int index);
static void gui_display_footer(void);
static void gui_printCentered(const char *str, int width);

void gui_init(void)
{
    route_ipv4_init();
    route_ipv4_get(&g_phead);
}

void gui_display(void)
{
    gui_display_header();
    route_ipv4_node_t *current = g_phead;
    int index = 1; 
    while (current != NULL)
    {
        gui_display_route(current, index);
        current = current->next;
        index++;
        gui_display_footer();
    }
}

void gui_cleanup(void)
{
    route_ipv4_cleanup(); 
}

static void gui_display_header(void)
{
    printf("+-----+-----------------+-----------------+-----------------+-------------+\n");
    printf("| IDX |   Destination   |     Gateway     |      Mask       | Is Default  |\n");
    printf("+-----+-----------------+-----------------+-----------------+-------------+\n");
}

static void gui_display_route(route_ipv4_node_t *node, int index)
{
    printf("| %3d | ", index);
    gui_printCentered(node->route.destination, 15);
    printf(" | ");
    gui_printCentered(node->route.gateway, 15);
    printf(" | ");
    gui_printCentered(node->route.mask, 15);
    printf(" | ");
    gui_printCentered(node->route.is_default ? "Yes" : "No", 11);
    printf(" |\n");
}

static void gui_display_footer(void)
{
    printf("+-----+-----------------+-----------------+-----------------+-------------+\n");
}

static void gui_printCentered(const char *str, int width)
{
    int len = strlen(str);
    int padding = (width - len) / 2;
    printf("%*s%s%*s", padding, "", str, padding + (width - len) % 2, "");
}