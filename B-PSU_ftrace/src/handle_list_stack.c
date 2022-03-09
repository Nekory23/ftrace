/*
** EPITECH PROJECT, 2021
** ftrace
** File description:
** handle_list_stack
*/

#include <stdlib.h>
#include "ftrace.h"

static mstack_t *create_node(unsigned long addr, char *name)
{
    mstack_t *new = malloc(sizeof(mstack_t));

    if (new == NULL)
        return NULL;
    new->addr = addr;
    new->name = name;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

mstack_t *handle_list_stack(mstack_t *stack, unsigned long addr, char *name)
{
    mstack_t *new = create_node(addr, name);
    mstack_t *tmp = stack;

    if (stack == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
    return stack;
}