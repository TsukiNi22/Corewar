/*
** EPITECH PROJECT, 2025
** exe_memory.c
** File description:
** Exe the memory stored
*/

#include "op.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>

static int exe_process(main_data_t *data,
    champion_t *champion, process_t *process)
{
    unsigned char value = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (process->cycle_delay > process->cycle_since_action)
        return OK;
    value = data->memory[process->index_to_exe];
    if (value >= MIN_OP && value <= MAX_OP) {
        if (op_cmd[value - 1](data, champion, process) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        process->cycle_delay = op_tab[value - 1].nbr_cycles;
        process->cycle_since_action = 0;
        process->index_to_exe = process->index_to_exe % MEM_SIZE;
    } else
        process->index_to_exe++;
    return OK;
}

static int exe_champion(main_data_t *data, champion_t *champion)
{
    if (!data || !champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < champion->process->len; i++) {
        if (exe_process(data, champion, champion->process->data[i]) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}

int exe_memory(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < data->champions->len; i++) {
        if (!((champion_t *) data->champions->data[i])->alive)
            continue;
        if (exe_champion(data, data->champions->data[i]) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}
