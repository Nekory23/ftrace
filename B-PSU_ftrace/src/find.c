/*
** EPITECH PROJECT, 2021
** ftrace
** File description:
** finc
*/

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include "ftrace.h"

static int gest_perror(const char *error)
{
    perror(error);
    return FAIL;
}

int find_call(pid_t pid, symbol_t *list, unsigned long rip, mstack_t **stack)
{
    struct user_regs_struct regs;
    int status = 0;
    unsigned ins = 0;
    unsigned char sec;

    if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
        return (gest_perror("ptrace"));
    wait(&status);
    if (WIFEXITED(status))
        return FAIL;
    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1)
        return (gest_perror("ptrace"));
    ins = ptrace(PTRACE_PEEKTEXT, pid, regs.rip, NULL);
    sec = ((unsigned)0xFF00 & ins) >> 8;
    if (sec == 0x48)
        print_enter(regs.rip, list, rip, stack);
    return SUCCESS;
}

void find_ret(mstack_t *stack, unsigned long addr)
{
    mstack_t *tmp = stack;

    while (tmp != NULL) {
        if (tmp->addr == addr) {
            printf("Leaving function %s\n", tmp->name);
            break;
        }
        tmp = tmp->next;
    }
}