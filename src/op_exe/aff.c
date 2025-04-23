/*
** EPITECH PROJECT, 2025
** aff.c
** File description:
** Execute the aff op command
*/

#include "write.h"
#include "corewar.h"
#include "error.h"

int op_aff(main_data_t *data, champion_t *champion, process_t *process)
{
    unsigned char param = 0;
    int reg = 0;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    param = data->memory[(process->index_to_exe + 1) % MEM_SIZE];
    if ((op_tab[15].type[0] & get_param(param, 1)) == 0)
        return OK;
    reg = data->memory[(process->index_to_exe + 1 + 1) % MEM_SIZE];
    if (reg == 0 || reg > REG_NUMBER)
        return OK;
    if (my_putchar(STDOUT, process->registers[reg - 1] % 256) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    process->index_to_exe += 1 + 1 + 1;
    return OK;
}
