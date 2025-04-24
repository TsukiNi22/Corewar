/*
** EPITECH PROJECT, 2025
** lfork.c
** File description:
** Execute the lfork op command
*/

#include "corewar.h"
#include "error.h"

int op_lfork(main_data_t *data, champion_t *champion, process_t *process)
{
    uint16_t arg = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < 2; i++)
        arg += data->memory[(process->index_to_exe + i + 1) % MEM_SIZE]
        << (8 * (2 - (1 + i)));
    if (init_process(champion, process->index_to_exe + arg) == KO)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    ((process_t *) champion->process->data[champion->process->len
    - 1])->cycle_delay = 800;
    process->index_to_exe += 2 + 1;
    return OK;
}
