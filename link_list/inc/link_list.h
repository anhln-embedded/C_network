/*
 ******************************************************************************
 * @file       link_list.h
 * @author     Luu Ngoc Anh
 * @date       14/04/2025
 * @brief      Safe string and memory operation macros
 ******************************************************************************
 */

 #ifndef __LINK_LIST_H__
 #define __LINK_LIST_H__
 

 typedef struct Node_t
{
    int data;
    struct Node_t *next;
} Node_t;


Node_t *link_list_create_node(int data);
void link_list_push_front(Node_t **head, int data);
void link_list_push_back(Node_t **head, int data);
void link_list_insert(Node_t **head, int data, int position);
void link_list_pop_front(Node_t **head);
void link_list_pop_back(Node_t **head);
void link_list_delete_node(Node_t **head, int position);
void link_list_delete_list(Node_t **head);
void link_list_display(Node_t *head);
int link_list_front(Node_t *head);
int link_list_back(Node_t *head);
void link_list_sort(Node_t **head);
void link_list_reverse(Node_t **head);

 
 #endif /* __LINK_LIST_H__ */
 
 /********************************* END OF FILE ********************************/
 