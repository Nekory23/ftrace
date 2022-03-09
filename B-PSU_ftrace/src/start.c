/*
** EPITECH PROJECT, 2021
** B-PSU_Strace
** File description:
** start
*/

#include <libelf.h>
#include <string.h>
#include <stdio.h>
#include "ftrace.h"

static int display_help(const char *bin)
{
    printf("USAGE: %s <command>\n", bin);
    return SUCCESS;
}

static int handle_init(int const ac, char const **av)
{
    Elf *elf;
    symbol_t *sym = NULL;
    func_t func;

    if (init_elf(av, &elf))
        return FAIL;
    sym = get_symbol(&elf);
    if (sym == NULL)
        return FAIL;
    get_arg(&func, ac, av);
    trace(sym, &func);
    elf_end(elf);
    return SUCCESS;
}

int start(int const ac, char const **av)
{
    if (ac == 2 && !strcmp(av[1], "--help"))
        return display_help(av[0]);
    if (error_handling(ac))
        return ERROR;
    if (handle_init(ac, av))
        return ERROR;
    return SUCCESS;
}