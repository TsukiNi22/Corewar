/*
** EPITECH PROJECT, 2025
** init_global.c
** File description:
** Init option variable
*/

#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

int init_option(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    data->no_graphics = false;
    data->csfml = false;
    data->spe_dump = false;
    data->dump_cycle = -1;
    data->next_prog_number = -1;
    data->next_load_address = -1;
    data->window = NULL;
    return OK;
}
