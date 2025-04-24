/*
** EPITECH PROJECT, 2025
** lld.c
** File description:
** Execute the lld op command
*/

#include "op.h"
#include "corewar.h"
#include "error.h"

static int setup_arg(main_data_t *data, process_t *process,
    int *size, unsigned int *arg_1)
{
    unsigned char param = 0;

    if (!data || !process || !size || !arg_1)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    *size = 2 + 2 * (get_param(param, 1) == T_DIR);
    for (int i = 0; i < *size; i++)
        *arg_1 += data->memory[(process->index_to_exe + 1 + i + 1) % MEM_SIZE]
        << (8 * (*size - (1 + i)));
    return OK;
}

static int set_end(main_data_t *data, process_t *process,
    int size, unsigned int arg_1)
{
    int reg = 0;

    if (!data || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    reg = data->memory[(process->index_to_exe + 1 + size + 1) % MEM_SIZE];
    if (reg == 0 || reg > REG_NUMBER)
        return OK;
    process->registers[reg - 1] = 0;
    if (size == 2) {
        for (int i = 0; i < REG_SIZE; i++)
            process->registers[reg - 1] += data->memory[process->index_to_exe +
            i + arg_1] << (8 * (REG_SIZE - (1 + i)));
    } else
        process->registers[reg - 1] = arg_1;
    process->index_to_exe += 1 + size + 1 + 1;
    process->carry = (process->registers[reg - 1] == 0);
    return OK;
}

int op_lld(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned char param = 0;
    unsigned int arg_1 = 0;
    int size = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[1].type[0] & get_param(param, 1)) == 0
        || (op_tab[1].type[1] & get_param(param, 2)) == 0)
        return OK;
    if (setup_arg(data, process, &size, &arg_1) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return set_end(data, process, size, arg_1);
}
