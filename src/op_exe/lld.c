/*
** EPITECH PROJECT, 2025
** lld.c
** File description:
** Execute the lld op command
*/

#include "corewar.h"
#include "error.h"

int op_lld(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE])
{
    if (!champion || !process || !memory)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
