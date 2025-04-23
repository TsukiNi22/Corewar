/*
** EPITECH PROJECT, 2025
** sti.c
** File description:
** Execute the sti op command
*/

#include "op.h"
#include "corewar.h"
#include "error.h"

int op_sti(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned char param = 0;
    unsigned int arg[2] = {0};
    int size[2] = {0};
    int reg = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[10].type[0] & get_param(param, 1)) == 0
        || (op_tab[10].type[1] & get_param(param, 2)) == 0
        || (op_tab[10].type[2] & get_param(param, 3)) == 0)
        return OK;
    reg = data->memory[(process->index_to_exe + 1 + 1) % MEM_SIZE];
    if (reg == 0 || reg > REG_NUMBER)
        return OK;
    for (int i = 0; i < 2; i++) {
        size[i] = 1 * (get_param(param, i + 1 + 1) == T_REG) +
        2 * (get_param(param, i + 1 + 1) == T_IND) +
        4 * (get_param(param, i + 1 + 1) == T_DIR);
        for (int j = 0; j < size[i]; j++)
            arg[i] += data->memory[(process->index_to_exe + 1 +
            size[0] * (i == 1) + j) % MEM_SIZE] << (8 * (size[i] - (1 + j)));
        if (size[i] == 1) {
            if (arg[i] == 0 || arg[i] > REG_NUMBER)
                return OK;
            arg[i] = process->registers[arg[i]];
        }
    }
    for (int i = 0; i < REG_SIZE; i++)
        data->memory[(process->index_to_exe + (arg[0] + arg[1])
        % IDX_MOD + i) % MEM_SIZE] = (process->registers[reg - 1]
        >> (8 * (REG_SIZE - (1 + i)))) & 0xFF;
    process->index_to_exe += 1 + 1 + size[0] + size[1] + 1;
    return OK;
}
