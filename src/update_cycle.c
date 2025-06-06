/*
** EPITECH PROJECT, 2025
** update_cycle.c
** File description:
** Update the cycle value
*/

#include "array.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

static int update_champion(champion_t *champion)
{
    process_t *process = NULL;

    if (!champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < champion->process->len; i++) {
        process = champion->process->data[i];
        process->cycle_since_action++;
    }
    return OK;
}

static int check_live(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < data->champions->len; i++) {
        if (((champion_t *) data->champions->data[i])->alive == false)
            data->live_status[i] = false;
        ((champion_t *) data->champions->data[i])->alive = false;
    }
    return OK;
}

int update_cycle(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < data->champions->len; i++) {
        if (update_champion(data->champions->data[i]) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    data->total_cycle++;
    data->actual_cycle++;
    if (data->nbr_live >= NBR_LIVE) {
        data->nbr_live = 0;
        data->cycle_to_die -= CYCLE_DELTA;
    }
    if (data->actual_cycle >= data->cycle_to_die) {
        if (check_live(data) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        data->actual_cycle = 0;
    }
    return OK;
}
