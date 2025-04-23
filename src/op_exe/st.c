/*
** EPITECH PROJECT, 2025
** st.c
** File description:
** Execute the st op command
*/

#include "op.h"
#include "corewar.h"
#include "error.h"

int op_st(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned char param = 0;
    unsigned int arg = 0;
    int reg = 0;
    int size = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[2].type[0] & get_param(param, 1)) == 0
        || (op_tab[2].type[1] & get_param(param, 2)) == 0)
        return OK;
    reg = data->memory[(process->index_to_exe + 1 + 1) % MEM_SIZE];
    if (reg == 0 || reg > REG_NUMBER)
        return OK;
    size = 1 + 2 * (get_param(param, 1) == T_IND);
    for (int i = 0; i < size; i++)
        arg += data->memory[(process->index_to_exe + 1 + 1 + i + 1) % MEM_SIZE]
        << (8 * (size - (1 + i)));
    if (size == 1) {
        if (arg == 0 || arg > REG_NUMBER)
            return OK;
        process->registers[reg - 1] = process->registers[arg - 1];
    } else {
        for (int i = 0; i < REG_SIZE; i++)
            data->memory[(process->index_to_exe + arg % IDX_MOD + i)
            % MEM_SIZE] = (process->registers[reg - 1]
            >> (8 * (REG_SIZE - (1 + i)))) & 0xFF;
    }
    process->index_to_exe += 1 + 1 + size + 1;
    return OK;
}
