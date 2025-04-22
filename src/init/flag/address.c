/*
** EPITECH PROJECT, 2025
** address.c
** File description:
** set the option for address
*/

#include "corewar.h"
#include "error.h"

int flag_address(main_data_t *data, int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
