/*
** EPITECH PROJECT, 2021
** ftrace
** File description:
** handle_list
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ftrace.h"

static symbol_t *create_node(unsigned long addr, char *name)
{
    symbol_t *new = malloc(sizeof(symbol_t));
    
    if (new == NULL) {
        perror("malloc");
        return NULL;
    }
    new->addr = addr;
    new->name = name;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

symbol_t *handle_list(symbol_t *list, data_t *data, Elf **elf, int i)
{
    symbol_t *new = create_node(data->symtab[i].st_value,
    elf_strptr(*elf, data->shdr->sh_link, data->symtab[i].st_name));
    symbol_t *tmp = list;

    if (list == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
    return list;
}

unsigned long get_addr(symbol_t *list, char *name)
{
    symbol_t *tmp = list;

    while (tmp != NULL)
    {
        if (!strcmp(tmp->name, name))
            return tmp->addr;
        tmp = tmp->next;
    }
    return 0;
}