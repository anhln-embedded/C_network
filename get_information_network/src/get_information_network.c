#include "get_information_network.h"
#include "safe_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

get_infor_network_error_t get_infor_default_gateway(char *gateway)
{
    get_infor_network_error_t res = GET_INFOR_NETWORK_OK;
    FILE *fp;
    char buffer[128];
    char *default_gateway = NULL;

    fp = popen("ip route | grep default", "r");
    if (fp == NULL) {
        get_infor_network_error_t res = GET_INFOR_NETWORK_NO_FILE;
        return res;
    }

    if (SAFE_FGETS(buffer, sizeof(buffer), fp) != NULL) {
        char *token = SAFE_STRTOK(buffer, " ");
        while (token != NULL) {
            if (SAFE_STRCMP(token, "via") == 0) {
                token = SAFE_STRTOK(NULL, " ");
                if (token != NULL) {
                    default_gateway = token;
                    break;
                }
            }
            token = SAFE_STRTOK(NULL, " ");
        }
    }
    pclose(fp);

    if (default_gateway != NULL) {
        SAFE_STRNCPY(gateway, default_gateway, SAFE_STRLEN(default_gateway) + 1);
        gateway[SAFE_STRLEN(default_gateway)] = '\0';
    } else {
        res = GET_INFOR_NETWORK_NO_DATA;
    }
    return res;
}