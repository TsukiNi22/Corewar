/*
** EPITECH PROJECT, 2025
** number.c
** File description:
** set the option for number
*/

#include "corewar.h"
#include "error.h"

int flag_number(main_data_t *data, int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
