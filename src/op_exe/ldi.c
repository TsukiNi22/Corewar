/*
** EPITECH PROJECT, 2025
** ldi.c
** File description:
** Execute the ldi op commldi
*/

#include "macro.h"
#include "op.h"
#include "corewar.h"
#include "error.h"

static int set_var(main_data_t *data, process_t *process,
    uint16_t arg[4], int size[2])
{
    unsigned char param = 0;

    if (!data || !process || !arg || !size)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    for (int i = 0; i < 2; i++) {
        size[i] = 1 * (get_param(param, i + 1) == T_REG) +
        -2 * (get_param(param, i + 1) == T_IND) +
        2 * (get_param(param, i + 1) == T_DIR);
        for (int j = 0; j < ABS(size[i]); j++)
            arg[i] += data->memory[(process->index_to_exe + 1 +
            size[0] * (i == 1) + j) % MEM_SIZE] << (8 * (ABS(size[i])
            - (1 + j)));
    }
    return OK;
}

static int set_memmory(main_data_t *data, process_t *process,
    uint16_t arg[4], int size[2])
{
    if (!data || !process || !arg || !size)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (size[0] == 2) {
        for (int j = 0; j < REG_SIZE; j++)
            arg[2] += data->memory[(process->index_to_exe + arg[0] % IDX_MOD)
            % MEM_SIZE] << (8 * (REG_SIZE - (1 + j)));
    }
    if (size[0] == 1) {
        if (arg[0] == 0 || arg[0] > REG_NUMBER)
            return OK;
        arg[2] += process->registers[arg[0] - 1];
    }
    if (size[0] == 2)
        arg[2] += arg[0];
    arg[2] += arg[1];
    for (int j = 0; j < REG_SIZE; j++)
        arg[3] += data->memory[(process->index_to_exe + (arg[2] + arg[1])
        % IDX_MOD) % MEM_SIZE] << (8 * (REG_SIZE - (1 + j)));
    return OK;
}

static int set_end(main_data_t *data, process_t *process,
    uint16_t arg[4], int size[2])
{
    int reg = 0;

    if (!data || !process || !size)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    reg = data->memory[(process->index_to_exe + 1 + ABS(size[0]) + ABS(size[1]) + 1)
    % MEM_SIZE];
    if (reg == 0 || reg > REG_NUMBER)
        return OK;
    process->registers[reg - 1] = arg[3];
    process->index_to_exe += 1 + ABS(size[0]) + ABS(size[1]) + 1 + 1;
    process->carry = (process->registers[reg - 1] == 0);
    return OK;
}

int op_ldi(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned char param = 0;
    uint16_t arg[4] = {0};
    int size[2] = {0};

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[13].type[0] & get_param(param, 1)) == 0
        || (op_tab[13].type[1] & get_param(param, 2)) == 0
        || (op_tab[13].type[2] & get_param(param, 3)) == 0)
        return OK;
    if (set_var(data, process, arg, size) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (set_memmory(data, process, arg, size) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return set_end(data, process, arg, size);
}
