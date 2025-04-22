/*
** EPITECH PROJECT, 2025
** corewar.c
** File description:
** Corewar
*/

#include "corewar.h"
#include "error.h"

int corewar(int const argc, char const *argv[], main_data_t *data)
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (init_data(data) == KO)
        return err_custom("Data initialisation error", FATAL_ERR, ERR_INFO);
    if (init_argument(data, argc, argv) == KO)
        return err_custom("Argument initialisation error", KO, ERR_INFO);
    if (data->help)
        return OK;
    if (setup(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (dump_memory(data->memory) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
