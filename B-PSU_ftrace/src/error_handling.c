/*
** EPITECH PROJECT, 2021
** strace
** File description:
** error_handling
*/

#include <stdio.h>
#include "ftrace.h"

bool error_handling(int const ac)
{
    if (ac < 2) {
        fprintf(stderr, "./ftrace: must have an argument\n");
        fprintf(stderr, "Try './ftrace --help' for more information.\n");
        return true;
    }
    return false;
}