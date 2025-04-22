/*
** EPITECH PROJECT, 2025
** init_global.c
** File description:
** Init global variable
*/

#include "op.h"
#include "array.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

int init_global(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < MAX_CHAMPIONS; i++)
        data->live_status[i] = false;
    data->nbr_live = 0;
    data->total_cycle = 0;
    data->actual_cycle = 0;
    data->cycle_to_die = CYCLE_TO_DIE;
    for (int i = 0; i < MEM_SIZE; i++)
        data->memory[i] = 0;
    data->champions = new_array();
    if (!data->champions)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
