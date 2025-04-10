#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node_t
{
    int data;
    struct Node *next;
} Node_t;

Node_t *createNode(int data)
{
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push_front(Node_t **head, int data)
{
    Node_t *new_node = createNode(data);
    if (*head != NULL)
    {
        new_node->next = *head;
    }
    *head = new_node;
}

void push_back(Node_t **head, int data)
{
    Node_t *new_node = createNode(data);
    Node_t *current_node = *head;
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new_node;
        new_node->next = NULL;
    }
}

void insert(Node_t **head, int data, int position)
{
    Node_t *new_node = createNode(data);
    if (position == 0)
    {
        new_node->next = *head;
        *head = new_node;
    }
    else
    {
        Node_t *current_node = *head;
        int index = 0;
        while (current_node != NULL && index < position - 1)
        {
            current_node = current_node->next;
            index++;
        }
        if (current_node != NULL)
        {
            new_node->next = current_node->next;
            current_node->next = new_node;
        }
        else
        {
            printf("Error Position\n");
            free(new_node);
        }
    }
}

void pop_front(Node_t **head)
{
    if (*head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    else
    {
        Node_t *tmep = *head;
        *head = (*head)->next;
        free(tmep);
    }
}

void pop_back(Node_t **head)
{
    Node_t *current_node = *head;
    if (current_node == NULL)
    {
        printf("List is empty\n");
        return;
    }
    else if (current_node->next == NULL)
    {
        pop_front(head);
    }
    else
    {
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        Node_t *temp = current_node->next;
        current_node->next = NULL;
        free(temp);
    }
}

void delete_list(Node_t **heed, int position)
{
    
}
void free_list(Node_t **heed)
{
}

int main()
{
    Node_t *head = createNode(23);
    return 0;
}