/*
** EPITECH PROJECT, 2021
** ftrace
** File description:
** get_arg
*/

#include <string.h>
#include <stdlib.h>
#include "ftrace.h"

void get_arg(func_t *func, int const ac, char const **av)
{
    int i = 0;

    func->cmd = strdup(av[1]);
    if (ac > 2) {
        func->arg = malloc(sizeof(char *) * (ac));
        for (i = 1; i != ac; ++i)
            func->arg[i-1] = strdup(av[i]);
    }
    if (i == 0)
        func->arg = NULL;
    else
        func->arg[i] = NULL;
}