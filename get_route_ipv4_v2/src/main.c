#include <stdio.h>
#include "route_ipv4.h"
#include "gui.h"

int main(void){
    gui_init();
    gui_display();
    gui_cleanup();
    return 0;
}