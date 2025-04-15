#include "gui.h"
#include "log.h"


int main(int argc, char *argv[])
{   
    if (argc > 1) {
        log_set_level(atoi(argv[1]));
        printf("Log level set to %d\n", atoi(argv[1]));
    }
    gui_init();
    gui_display();
    return 0;
}
