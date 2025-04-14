#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "link_list.h"


int main()
{
    Node_t *head = link_list_create_node(23);
    link_list_push_front(&head, 12);
    link_list_push_back(&head, 45);
    link_list_insert(&head, 34, 1);
    link_list_display(head);
    link_list_sort(&head);
    link_list_display(head);
    return 0;
}

