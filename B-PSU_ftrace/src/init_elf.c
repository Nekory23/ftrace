/*
** EPITECH PROJECT, 2021
** ftrace
** File description:
** init_elf
*/

#include <gelf.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "ftrace.h"

static bool gest_error(const char *error, const char *perror_err)
{
    if (perror_err != NULL)
        perror(perror_err);
    fprintf(stderr, error);
    return true;
}

static bool read_elf(char const **av, Elf **elf, int fd)
{
    if (elf_version(EV_CURRENT) == EV_NONE)
        return (gest_error("Error: elf\n", NULL));
    *elf = elf_begin(fd, ELF_C_READ, NULL);
    if (*elf == NULL)
        return (gest_error("Error: elf\n", "elf_begin"));
    if (elf_kind(*elf) != ELF_K_ELF) {
        fprintf(stderr, "Error: %s isn't an elf file\n", av[1]);
        return true;
    }
    return false;
}

bool init_elf(char const **av, Elf **elf)
{
    int fd = open(av[1], O_RDONLY, NULL);

    if (fd < 0)
        return (gest_error("Error: open failed\n", "open"));
    if (read_elf(av, elf, fd) || gelf_getclass(*elf) != ELFCLASS64)
        return true;
    return false;
}