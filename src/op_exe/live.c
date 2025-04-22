/*
** EPITECH PROJECT, 2025
** live.c
** File description:
** Execute the live op command
*/

#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

int op_live(main_data_t *data, champion_t *champion, process_t *process)
{
    size_t index = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (index = 0; data->champions->data[i] != champion; index++);
    data->live_status[index] = true;
    data->nbr_live++;
    return OK;
}
