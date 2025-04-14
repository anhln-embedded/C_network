/*
 ******************************************************************************
 * @file       log.h
 * @author     Luu Ngoc Anh
 * @date       14/04/2025
 ******************************************************************************
 */

#ifndef __ROUTE_IPV4_H__
#define __ROUTE_IPV4_H__
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "log.h"
#include "safe_string_macros.h"


typedef struct{
    char iface[16];
    char destination[16];
    char gateway[16];
    char mask[16];
    bool is_default;
} route_ipv4_t;

typedef struct route_ipv4_node_t
{
    route_ipv4_t route;   
    struct route_ipv4_node_t *next;
} route_ipv4_node_t;

void route_ipv4_init(void);
void route_ipv4_get(route_ipv4_node_t **head);
void route_ipv4_cleanup(void);



#endif /* __ROUTE_IPV4_H__ */

 /********************************* END OF FILE ********************************/
/******************************************************************************/