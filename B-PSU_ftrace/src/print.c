/*
** EPITECH PROJECT, 2021
** ftrace
** File description:
** print
*/

#include <stdio.h>
#include "syscall_val.h"
#include "ftrace.h"

static void display_args(struct user_regs_struct reg)
{
    size_t regs[6] = {reg.rdi, reg.rsi, reg.rdx,
                        reg.rcx, reg.r8, reg.r9};
    size_t orig = reg.orig_rax;

    printf("Syscall %s(", entries[orig].name);
    for (int i = 0; i != entries[orig].nb_args; ++i) {
        printf("0x%lx", regs[i]);
        if (i != entries[orig].nb_args - 1)
            printf(", ");
    }
    printf(") = ");
    if (orig == EXIT || orig == 162) {
        printf("?\n");
        return;
    }
    printf("0x%llx\n", reg.rax);
}

void print_syscall(struct user_regs_struct regs)
{
    size_t orig = regs.orig_rax;

    if ((int)orig == -1)
        return;
    if (orig > NB_SYSCALL) {
        printf("Unknown\n");
        return;
    }
    display_args(regs);
    if (orig == EXIT) {
        printf("Leaving function main\n");
        printf("+++ exited with %lld +++\n", regs.rdi);
    }
}

void print_enter(unsigned long rip, symbol_t *list, unsigned long srip,
mstack_t **stack)
{
    symbol_t *tmp = list;

    while (tmp != NULL) {
        if (rip == tmp->addr && tmp->name[0] != '_') {
            printf("Entering function %s at %#lx\n", tmp->name, tmp->addr);
            *stack = handle_list_stack(*stack, srip, tmp->name);
            break;
        }
        tmp = tmp->next;
    }
}