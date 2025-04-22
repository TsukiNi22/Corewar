/*
** EPITECH PROJECT, 2025
** exe_memory.c
** File description:
** Exe the memory stored
*/

#include "corewar.h"
#include "error.h"

int exe_memory(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
