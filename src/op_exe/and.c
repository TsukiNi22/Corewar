/*
** EPITECH PROJECT, 2025
** and.c
** File description:
** Execute the and op command
*/

#include "corewar.h"
#include "error.h"

int op_and(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE])
{
    if (!champion || !process || !memory)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
