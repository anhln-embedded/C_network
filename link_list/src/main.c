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
    Node_t *prev_node = *head;
    if (*head == NULL)
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
        while(current_node->next != NULL)
        {
            prev_node = current_node;
            current_node = current_node->next;
        }
        prev_node->next = NULL;
        free(current_node);
        current_node = NULL;
        prev_node = NULL;
    }
}

void delete_list(Node_t **heed, int position)
{
    Node_t *current_node = *heed;
    Node_t *temp = NULL;
    while (current_node != NULL && position > 0)
    {
        temp = current_node;
        current_node = current_node->next;
        position--;
    }
    if (current_node == NULL)
    {
        printf("Error Position\n");
        return;
    }
    if (temp == NULL)
    {
        *heed = current_node->next;
    }
    else
    {
        temp->next = current_node->next;
    }
    free(current_node);
    current_node = NULL;
    temp = NULL;            
}
void free_list(Node_t **heed)
{
    Node_t *current_node = *heed;
    Node_t *temp = NULL;
    while (current_node != NULL)
    {
        temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
    *heed = NULL;
}

void display_list(Node_t *head)
{
    Node_t *current_node = head;
    while (current_node != NULL)
    {
        printf("%d -> ", current_node->data);
        current_node = current_node->next;
    }
    printf("NULL\n");
}

int front(Node_t *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return -1;
    }
    return head->data;
}

int back(Node_t *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return -1;
    }
    Node_t *current_node = head;
    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }
    return current_node->data;
}

void sort_list(Node_t **head)
{
    Node_t *current_node = *head;
    Node_t *next_node = NULL;
    int temp;
    if (*head == NULL)
    {
        return;
    }
    while (current_node != NULL)
    {
        next_node = current_node->next;
        while (next_node != NULL)
        {
            if (current_node->data > next_node->data)
            {
                temp = current_node->data;
                current_node->data = next_node->data;
                next_node->data = temp;
            }
            next_node = next_node->next;
        }
        current_node = current_node->next;
    }
}
void reverse_list(Node_t **head)
{
    Node_t *prev = NULL;
    Node_t *current = *head;
    Node_t *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}



int main()
{
    Node_t *head = createNode(23);
    push_front(&head, 12);
    push_back(&head, 45);
    insert(&head, 34, 1);
    display_list(head);
    sort_list(&head);
    display_list(head);
    return 0;
}