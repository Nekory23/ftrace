/*
** EPITECH PROJECT, 2021
** ftrace
** File description:
** trace
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include <sys/wait.h>
#include "ftrace.h"

static bool gest_perror(const char *error)
{
    perror(error);
    return true;
}

static bool start_trace(func_t *func)
{
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
        return (gest_perror("ptrace"));
    if (execvp(func->cmd, &func->arg[0]) == -1)
        return (gest_perror("execvp"));
    return false;
}

static void print_calls(symbol_t *list, mstack_t **stack, pid_t pid)
{
    unsigned ins = 0;
    struct user_regs_struct regs;

    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    ins = ptrace(PTRACE_PEEKTEXT, pid, regs.rip, NULL);
    if (((unsigned) 0xFF & ins) == 0xE8)
        find_call(pid, list, regs.rip, stack);
    else if (((unsigned) 0xFF & ins) == 0xC3)
        find_ret(*stack, ptrace(PTRACE_PEEKTEXT, pid, regs.rsp, 0) - 5);
    else
        print_syscall(regs);
}

static bool tracer(pid_t pid, symbol_t *list)
{
    int status = 0;
    mstack_t *stack;

    wait(&status);
    if (ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACEEXIT) == -1)
        return (gest_perror("ptrace"));
    while (!WIFEXITED(status)) {
        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        wait(&status);
        if (WIFEXITED(status))
			break;
        print_calls(list, &stack, pid);
    }
    return false;
}

int trace(symbol_t *list, func_t *func)
{
    pid_t pid = fork();

    if (pid == 0 && start_trace(func)) {
        return FAIL;
    } else if (pid > 0) {
        printf("Entering function main at %#lx\n", get_addr(list, "main"));
        tracer(pid, list);
        return FAIL;
    } else
        return SUCCESS;
}