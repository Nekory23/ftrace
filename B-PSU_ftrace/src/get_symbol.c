/*
** EPITECH PROJECT, 2021
** ftrace
** File description:
** get_symbol
*/

#include <stdio.h>
#include "ftrace.h"

static symbol_t *handle_symbol(Elf **elf, data_t *data)
{
    symbol_t *list = NULL;
    int size = data->shdr->sh_size / data->shdr->sh_entsize;

    data->data = elf_getdata(data->scn, NULL);
    data->symtab = (Elf64_Sym *) data->data->d_buf;
    for (int i = 0, st_type = 0; i != size; ++i) {
        st_type = ELF64_ST_TYPE(data->symtab[i].st_info);
        if (st_type == STT_FUNC || st_type == STT_NOTYPE) {
            list = handle_list(list, data, elf, i);
            if (list == NULL)
                return NULL;
        }
    }
    return list;
}

symbol_t *get_symbol(Elf **elf)
{
    data_t data;

    while ((data.scn = elf_nextscn(*elf, data.scn)) != NULL) {
        data.shdr = elf64_getshdr(data.scn);
        if (!data.shdr)
            return NULL;
        if (data.shdr->sh_type == SHT_SYMTAB)
            return handle_symbol(elf, &data);
    }
    fprintf(stderr, "Error: no symbol found.\n");
    return NULL;
}