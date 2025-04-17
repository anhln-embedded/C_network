#include "gui.h"
#include "safe_macros.h"
#include "linked_list.h"


static void gui_display_header(void);
static void gui_display_route(route_ipv4_t *entry, int index);
static void gui_display_footer(void);
static void gui_printCentered(const char *str, int width);

void gui_init(void)
{
    route_ipv4_build();
}

void gui_display(void)
{
    route_ipv4_t *route_ipv4;
    list_head_t *pos;
    int i = 0;
    gui_display_header();
    LIST_FOR_EACH(pos, route_ipv4_get_head())
    {
        route_ipv4 = LIST_ENTRY(pos, route_ipv4_t, list);
        gui_display_route(route_ipv4 ,i);
        i++;
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

static void gui_display_route(route_ipv4_t *entry, int index)
{
    printf("| %3d | ", index);
    gui_printCentered(entry->destination, 15);
    printf(" | ");
    gui_printCentered(entry->gateway, 15);
    printf(" | ");
    gui_printCentered(entry->mask, 15);
    printf(" | ");
    gui_printCentered(entry->is_default ? "Yes" : "No", 11);
    printf(" |\n");
}

static void gui_display_footer(void)
{
    printf("+-----+-----------------+-----------------+-----------------+-------------+\n");
}

static void gui_printCentered(const char *str, int width)
{
    int len = SAFE_STRLEN(str);
    int padding = (width - len) / 2;
    printf("%*s%s%*s", padding, "", str, padding + (width - len) % 2, "");
}