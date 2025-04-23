/*
** EPITECH PROJECT, 2025
** or.c
** File description:
** Execute the or op commor
*/

#include "op.h"
#include "corewar.h"
#include "error.h"

int op_or(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned char param = 0;
    unsigned int arg[2] = {0};
    unsigned int val = 0;
    int size[2] = {0};
    int reg = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[6].type[0] & get_param(param, 1)) == 0
        || (op_tab[6].type[1] & get_param(param, 2)) == 0
        || (op_tab[6].type[2] & get_param(param, 3)) == 0)
        return OK;
    for (int i = 0; i < 2; i++) {
        size[i] = 1 * (get_param(param, i + 1) == T_REG) +
        2 * (get_param(param, i + 1) == T_IND) +
        4 * (get_param(param, i + 1) == T_DIR);
        for (int j = 0; j < size[i]; j++)
            arg[i] += data->memory[(process->index_to_exe + 1 +
            size[0] * (i == 1) + j) % MEM_SIZE] << (8 * (size[i] - (1 + j)));
        if (i == 0) {
            if (size[i] == 1) {
                if (reg == 0 || reg > REG_NUMBER)
                    return OK;
                val = process->registers[arg[i] - 1];
            } else
                val = arg[i];
        } else {
            if (size[i] == 1) {
                if (reg == 0 || reg > REG_NUMBER)
                    return OK;
                val |= process->registers[arg[i] - 1];
            } else
                val |= arg[i];
        }
    }
    reg = data->memory[(process->index_to_exe + 1 + size[0] + size[1] + 1) % MEM_SIZE];
    if (reg == 0 || reg > REG_NUMBER)
        return OK;
    process->registers[reg - 1] = val;
    process->index_to_exe += 1 + size[0] + size[1] + 1 + 1;
    process->carry = (process->registers[reg - 1] == 0);
    return OK;
}
