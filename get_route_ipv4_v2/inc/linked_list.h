/*
 ******************************************************************************
 * @file       log.h
 * @author     Luu Ngoc Anh
 * @date       04/04/2025
 ******************************************************************************
 */

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct list_head_s
{
    struct list_head_s *next;
    struct list_head_s *prev;
} list_head_t;

#define LIST_HEAD_INIT(name) {&(name), &(name)}
#define LIST_HEAD(name) list_head_t name = LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(ptr)  \
    do                       \
    {                        \
        (ptr)->next = (ptr); \
        (ptr)->prev = (ptr); \
    } while (0)

#define LIST_ENTRY(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

#define LIST_ENTRY_HEAD(ptr, type, member) \
    ((ptr)->next == (ptr) ? NULL : LIST_ENTRY((ptr)->next, type, member))

#define LIST_FOR_EACH(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define LIST_FOR_EACH_SAFE(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#define LIST_FOR_EACH_ENTRY(pos, head, member)                 \
    for (pos = LIST_ENTRY((head)->next, typeof(*pos), member); \
         &pos->member != (head);                               \
         pos = LIST_ENTRY(pos->member.next, typeof(*pos), member))
#define LIST_FOR_EACH_ENTRY_SAFE(pos, n, head, member)          \
    for (pos = LIST_ENTRY((head)->next, typeof(*pos), member),  \
        n = LIST_ENTRY(pos->member.next, typeof(*pos), member); \
         &pos->member != (head);                                \
         pos = n, n = LIST_ENTRY(n->member.next, typeof(*n), member))
static inline void
__list_add(list_head_t *new, list_head_t *prev, list_head_t *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void
list_add_tail(list_head_t *new, list_head_t *head)
{
    __list_add(new, head->prev, head);
}

static inline void
__list_del(list_head_t *prev, list_head_t *next)
{
    next->prev = prev;
    prev->next = next;
}
static inline void
list_del(list_head_t *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}

static inline void
list_del_init(list_head_t *entry)
{
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}

static inline int
list_empty(list_head_t *head)
{
    return head->next == head;
}

static inline int
list_count(list_head_t *head)
{
    list_head_t *pos;
    int ret = 0;

    for (pos = (head)->next; pos != (head); pos = pos->next)
    {
        ret++;
    }

    return ret;
}

static inline void
__list_splice(list_head_t *list, list_head_t *prev, list_head_t *next)
{
    list_head_t *first = list->next;
    list_head_t *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

static inline void
list_splice_tail(list_head_t *list, list_head_t *head)
{
    if (0 == list_empty(list))
    {
        __list_splice(list, head->prev, head);
    }
}

static inline void
list_replace(list_head_t *old, list_head_t *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}
static inline void
list_replace_init(list_head_t *old, list_head_t *new)
{
    list_replace(old, new);
    INIT_LIST_HEAD(old);
}

#endif /* __LINKED_LIST_H__ */

/********************************* END OF FILE ********************************/