/*
** EPITECH PROJECT, 2025
** sti.c
** File description:
** Execute the sti op command
*/

#include "macro.h"
#include "op.h"
#include "corewar.h"
#include "error.h"

static int set_size(main_data_t *data, process_t *process,
    uint16_t arg[3], int size[2])
{
    unsigned char param = 0;

    if (!data || !process || !arg || !size)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    size[arg[2]] = 1 * (get_param(param, arg[2] + 1 + 1) == T_REG) +
    -2 * (get_param(param, arg[2] + 1 + 1) == T_IND) +
    2 * (get_param(param, arg[2] + 1 + 1) == T_DIR);
    return OK;
}

static int set_var(main_data_t *data, process_t *process,
    uint16_t arg[3], int size[2])
{
    uint16_t read_val = 0;

    if (!data || !process || !arg || !size)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int j = 0; j < ABS(size[arg[2]]); j++)
        arg[arg[2]] += data->memory[(process->index_to_exe + 1 + 2 +
        ABS(size[0]) * (arg[2] == 1) + j) % MEM_SIZE]
        << (8 * (ABS(size[arg[2]]) - (1 + j)));
    if (size[arg[2]] == -2) {
        for (int j = 0; j < REG_SIZE; j++)
            read_val = data->memory[(process->index_to_exe + arg[arg[2]]
            % IDX_MOD) % MEM_SIZE] << (8 * (REG_SIZE - (1 + j)));
        arg[arg[2]] = read_val;
    }
    if (size[arg[2]] == 1) {
        if (arg[arg[2]] == 0 || arg[arg[2]] > REG_NUMBER)
            return OK;
        arg[arg[2]] = process->registers[arg[arg[2]] - 1];
    }
    return OK;
}

static int set_end(main_data_t *data, void *ptrs[2],
    uint16_t arg[3], int size[2])
{
    int reg = 0;

    if (!data || !ptrs || !arg || !size)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    reg = data->memory[(((process_t *) ptrs[1])->index_to_exe + 1 + 1)
    % MEM_SIZE];
    if (reg == 0 || reg > REG_NUMBER)
        return OK;
    for (int i = 0; i < REG_SIZE; i++) {
        data->memory[(((process_t *) ptrs[1])->index_to_exe + (arg[0] + arg[1])
        % IDX_MOD + i) % MEM_SIZE] =
        (((process_t *) ptrs[1])->registers[reg - 1]
        >> (8 * (REG_SIZE - (1 + i)))) & 0xFF;
        data->apartenance[(((process_t *) ptrs[1])->index_to_exe +
        (arg[0] + arg[1]) % IDX_MOD + i) % MEM_SIZE] =
        ((champion_t *) ptrs[0])->prog_number;
    }
    ((process_t *) ptrs[1])->index_to_exe += 1 + 1 +
    ABS(size[0]) + ABS(size[1]) + 1;
    return OK;
}

int op_sti(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned char param = 0;
    uint16_t arg[3] = {0};
    int size[2] = {0};

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[10].type[0] & get_param(param, 1)) == 0
        || (op_tab[10].type[1] & get_param(param, 2)) == 0
        || (op_tab[10].type[2] & get_param(param, 3)) == 0)
        return OK;
    for (arg[2] = 0; arg[2] < 2; arg[2]++) {
        if (set_size(data, process, arg, size) == KO)
            return err_prog(PTR_ERR, KO, ERR_INFO);
        if (set_var(data, process, arg, size) == KO)
            return err_prog(PTR_ERR, KO, ERR_INFO);
    }
    return set_end(data, (void *[2]){champion, process}, arg, size);
}
