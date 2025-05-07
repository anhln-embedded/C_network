#include <stdio.h>
#include "wan_infor.h"
#include "parser_json_file.h"


int main(){
    log_config_t config = {
        .log_config_level = LOG_LVL_DEBUG,
        .log_config_type = LOG_STDOUT,
        .log_config_file = "application.log"
    };
    log_init(&config);
    cJSON *json_input = NULL;
    wan_config_t output;
    error_t err = parser_json_file("wan_config.json", &json_input);
    if (err != ERROR_NONE)
    {
        log_error("Failed to parse JSON file: %s", error_to_string(err));
        return -1;
    }

    err = wan_infor_parser_json(json_input, &output);
    if (err != ERROR_NONE)
    {
        log_error("Failed to parse WAN config: %s", error_to_string(err));
        cJSON_Delete(json_input);
        return -1;
    }
    log_debug("WAN Config Parsed Successfully");
    return 0;
}