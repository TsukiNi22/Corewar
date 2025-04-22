/*
** EPITECH PROJECT, 2025
** exe_memory.c
** File description:
** Exe the memory stored
*/

#include "corewar.h"
#include "error.h"
#include <stddef.h>

static int exe_process(champion_t *champion, process_t *process)
{
    if (!champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    return OK;
}

static int exe_champion(champion_t *champion)
{
    if (!champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < champion->process->len; i++) {
        if (exe_process(champion, champion->process->data[i]) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}

int exe_memory(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < data->champions->len; i++) {
        if (exe_champion(data->champions->data[i]) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}
