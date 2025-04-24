/*
** EPITECH PROJECT, 2025
** or.c
** File description:
** Execute the or op common
*/

#include "op.h"
#include "corewar.h"
#include "error.h"

static int first(main_data_t *data, process_t *process,
    unsigned int var[5], int i)
{
    unsigned int read_val = 0;

    if (!data || !process || !var)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (var[3 + i] == 1) {
        if (var[i] == 0 || var[i] > REG_NUMBER)
            return 2;
        var[2] = process->registers[var[i] - 1];
    }
    if (var[3 + i] == 2) {
        for (int k = 0; k < REG_SIZE; k++)
            read_val += data->memory[(process->index_to_exe + k + var[i]
            % IDX_MOD) % MEM_SIZE] << (8 * (REG_SIZE - (1 + k)));
        var[2] = read_val;
    }
    if (var[3 + i] == 4)
        var[2] = var[i];
    return OK;
}

static int second(main_data_t *data, process_t *process,
    unsigned int var[5], int i)
{
    unsigned int read_val = 0;

    if (!data || !process || !var)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (var[3 + i] == 1) {
        if (var[i] == 0 || var[i] > REG_NUMBER)
            return 2;
        var[2] |= process->registers[var[i] - 1];
    }
    if (var[3 + i] == 2) {
        for (int k = 0; k < REG_SIZE; k++)
            read_val += data->memory[(process->index_to_exe + k +
            var[i] % IDX_MOD) % MEM_SIZE] << (8 * (REG_SIZE - (1 + k)));
        var[2] |= read_val;
    }
    if (var[3 + i] == 4)
        var[2] |= var[i];
    return OK;
}

static int setup_var(main_data_t *data, process_t *process,
    unsigned int var[5], int i)
{
    unsigned char param = 0;

    if (!data || !process || !var)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    var[3 + i] = 1 * (get_param(param, i + 1) == T_REG) +
    2 * (get_param(param, i + 1) == T_IND) +
    4 * (get_param(param, i + 1) == T_DIR);
    for (unsigned int j = 0; j < var[3 + i]; j++)
        var[i] += data->memory[(process->index_to_exe + 1 +
        var[3] * (i == 1) + j) % MEM_SIZE] << (8 * (var[3 + i] - (1 + j)));
    return OK;
}

static int check(main_data_t *data, process_t *process)
{
    unsigned char param = 0;

    if (!data || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[5].type[0] & get_param(param, 1)) == 0
        || (op_tab[5].type[1] & get_param(param, 2)) == 0
        || (op_tab[5].type[2] & get_param(param, 3)) == 0)
        return 2;
    return OK;
}

static int set_end(main_data_t *data, process_t *process,
    unsigned int var[5])
{
    int reg = 0;

    if (!data || !process || !var)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    reg = data->memory[(process->index_to_exe + 1 + var[3] + var[4] + 1)
    % MEM_SIZE];
    if (reg == 0 || reg > REG_NUMBER)
        return OK;
    process->registers[reg - 1] = var[2];
    process->index_to_exe += 1 + var[3] + var[4] + 1 + 1;
    process->carry = (process->registers[reg - 1] == 0);
    return OK;
}

int op_or(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned int var[5] = {0};
    int res = OK;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    res = check(data, process);
    if (res == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    for (int i = 0; res != 2 && i < 2; i++) {
        if (setup_var(data, process, var, i) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (i == 0)
            res = first(data, process, var, i);
        else
            res = second(data, process, var, i);
        if (res == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return KO * (res != 2 && set_end(data, process, var) == KO);
}
