/*
** EPITECH PROJECT, 2025
** dump.c
** File description:
** set the option for dump
*/

#include "corewar.h"
#include "error.h"

int flag_dump(main_data_t *data, int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (argc == 1)
        return err_system(data, KO, *argv, "Insufficient argument");
    return OK;
}
