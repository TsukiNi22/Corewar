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
    int index_past = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (process->cycle_delay > process->cycle_since_action)
        return OK;
    value = data->memory[process->index_to_exe % MEM_SIZE];
    if (value >= MIN_OP && value <= MAX_OP) {
        index_past = process->index_to_exe;
        if (op_cmd[value - 1](data, champion, process) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        process->cycle_delay = op_tab[value - 1].nbr_cycles;
        process->cycle_since_action = 0;
        process->index_to_exe += (process->index_to_exe == index_past);
    } else
        process->index_to_exe++;
    process->index_to_exe = process->index_to_exe % MEM_SIZE;
    return OK;
}

static int exe_champion(main_data_t *data, champion_t *champion)
{
    process_t *process = NULL;

    if (!data || !champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < champion->process->len; i++) {
        process = champion->process->data[i];
        if (exe_process(data, champion, process) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}

int exe_memory(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < data->champions->len; i++) {
        if (!data->live_status[i])
            continue;
        if (exe_champion(data, data->champions->data[i]) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}
