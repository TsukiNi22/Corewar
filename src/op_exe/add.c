/*
** EPITECH PROJECT, 2025
** add.c
** File description:
** Execute the add op command
*/

#include "op.h"
#include "corewar.h"
#include "error.h"

int op_add(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned char param = 0;
    int reg[3] = {0};

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[3].type[0] & get_param(param, 1)) == 0
        || (op_tab[3].type[1] & get_param(param, 2)) == 0
        || (op_tab[3].type[2] & get_param(param, 3)) == 0)
        return OK;
    for (int i = 0; i < 3; i++) {
        reg[i] = data->memory[(process->index_to_exe + 1 + i + 1) % MEM_SIZE];
        if (reg[i] == 0 || reg[i] > REG_NUMBER)
            return OK;
    }
    process->registers[reg[2] - 1] =
    process->registers[reg[0] - 1] + process->registers[reg[1] - 1];
    process->index_to_exe += 1 + 3 + 1;
    process->carry = (process->registers[reg[2] - 1] == 0);
    return OK;
}
