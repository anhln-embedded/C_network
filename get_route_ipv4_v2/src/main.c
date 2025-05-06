#include "gui.h"
#include "log.h"
int main(int argc, char *argv[]){
    if(argc > 1)
    {
        log_set_level(atoi(argv[1]));
    }
    gui_init();
    gui_display();
    gui_cleanup();
    return 0;
}