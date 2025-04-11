#include <stdio.h>
#include "log.h"

int main(){
    init_logger();
    set_log_level(LOG_LVL_DEBUG);
    log_message(LOG_LVL_DEBUG, "This is a debug message.");
}