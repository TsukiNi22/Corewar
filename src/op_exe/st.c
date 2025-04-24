/*
** EPITECH PROJECT, 2025
** st.c
** File description:
** Execute the st op command
*/

#include "op.h"
#include "corewar.h"
#include "error.h"

static int setup_var(main_data_t *data, process_t *process,
    int var[2], unsigned int *arg)
{
    unsigned char param = 0;

    if (!data || !process || !var || !arg)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    var[0] = 1 * !(get_param(param, 2) == T_IND)
    + 2 * (get_param(param, 2) == T_IND);
    for (int i = 0; i < var[0]; i++)
        *arg += data->memory[(process->index_to_exe + 1 + 1 + i + 1)
        % MEM_SIZE]
        << (8 * (var[0] - (1 + i)));
    var[1] = data->memory[(process->index_to_exe + 1 + 1) % MEM_SIZE];
    return OK;
}

static int set_register(process_t *process,
    int arg, int reg)
{
    if (!process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    process->registers[reg - 1] = process->registers[arg - 1];
    return OK;
}

static int s_me(main_data_t *data, void *ptrs[2],
    int arg, int reg)
{
    if (!data || !ptrs)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < REG_SIZE; i++) {
        data->memory[(((process_t *) ptrs[1])->index_to_exe +
        arg % IDX_MOD + i) % MEM_SIZE] = (((process_t *) ptrs[1])->registers[reg - 1]
        >> (8 * (REG_SIZE - (1 + i)))) & 0xFF;
        data->apartenance[(((process_t *) ptrs[1])->index_to_exe +
        arg % IDX_MOD + i) % MEM_SIZE] = ((champion_t *) ptrs[0])->prog_number;
    }
    return OK;
}

int op_st(main_data_t *data, champion_t *chp, process_t *proc)
{
    unsigned char param = 0;
    unsigned int arg = 0;
    int var[2] = {0};

    if (!data || !chp || !proc)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(proc->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[2].type[0] & get_param(param, 1)) == 0
        || (op_tab[2].type[1] & get_param(param, 2)) == 0)
        return OK;
    if (setup_var(data, proc, var, &arg) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if ((var[1] == 0 || var[1] > REG_NUMBER) ||
        (var[0] == 1 && (arg == 0 || arg > REG_NUMBER)))
        return OK;
    if ((var[0] == 1 && set_register(proc, arg, var[1]) == KO) ||
        (var[0] != 1 && s_me(data, (void *[2]){chp, proc}, arg, var[1]) == KO))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    proc->index_to_exe += 1 + 1 + var[0] + 1;
    return OK;
}
