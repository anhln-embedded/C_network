#ifndef _GET_INFOR_NETWORK_H_
#define _GET_INFOR_NETWORK_H_

#include <stdio.h>



typedef enum {
    GET_INFOR_NETWORK_ERROR = 0,
    GET_INFOR_NETWORK_OK = 1,
    GET_INFOR_NETWORK_TIMEOUT = 2,
    GET_INFOR_NETWORK_NO_DATA = 3,
    GET_INFOR_NETWORK_NO_MEMORY = 4,
    GET_INFOR_NETWORK_NO_FILE = 5,
    GET_INFOR_NETWORK_NO_PERMISSION = 6,
    GET_INFOR_NETWORK_NO_INTERFACE = 7,
} get_infor_network_error_t;

get_infor_network_error_t get_infor_default_gateway(char *gateway);

#endif // _GET_INFOR_NETWORK_H_