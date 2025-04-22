/*
** EPITECH PROJECT, 2025
** corewar.c
** File description:
** Corewar
*/

#include "op.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

static bool is_end(bool live_status[MAX_CHAMPIONS], size_t len)
{
    bool alive = false;

    if (!live_status)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < len; i++) {
        if (alive && live_status[i])
            return false;
        alive = (alive || live_status[i]);
    }
    return true;
}

static int loop(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    while (!is_end(data->live_status, data->champions->len)) {
        if (exe_memory(data) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (update_cycle(data) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (data->total_cycle >= data->dump_cycle)
            return OK;
    }
    return OK;
}

int corewar(int const argc, char const *argv[], main_data_t *data)
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (init_data(data) == KO)
        return err_custom("Data initialisation error", FATAL_ERR, ERR_INFO);
    if (init_argument(data, argc, argv) == KO)
        return err_custom("Argument initialisation error", KO, ERR_INFO);
    if (data->help)
        return OK;
    if (setup(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (loop(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
