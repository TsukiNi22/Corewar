/*
** EPITECH PROJECT, 2025
** zjmp.c
** File description:
** Execute the zjmp op command
*/

#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

int op_zjmp(main_data_t *data, champion_t *champion, process_t *process)
{
    int16_t arg = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (!process->carry)
        return OK;
    for (int i = 0; i < 2; i++)
        arg += data->memory[(process->index_to_exe + i + 1) % MEM_SIZE]
        << (8 * (2 - (1 + i)));
    process->index_to_exe += arg % IDX_MOD;
    return OK;
}
