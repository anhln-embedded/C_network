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
#include "safe_macros.h"
#include "linked_list.h"

typedef struct{
    list_head_t list;
    char destination[16];
    char gateway[16];
    char mask[16];
    bool is_default;
} route_ipv4_t;

void route_ipv4_build(void);
list_head_t* route_ipv4_get_head(void);
void route_ipv4_cleanup(void);

#endif /* __ROUTE_IPV4_H__ */

 /********************************* END OF FILE ********************************/
/******************************************************************************/