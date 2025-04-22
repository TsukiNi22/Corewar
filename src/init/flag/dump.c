/*
** EPITECH PROJECT, 2025
** dump.c
** File description:
** set the option for dump
*/

#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>

int flag_dump(main_data_t *data, int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (argc == 1)
        return err_system(data, KO, *argv, "Insufficient argument");
    if (!my_str_is(argv[1], "0123456789"))
        return err_system(data, KO, argv[1], "Can only be composed of [0-9]");
    if (data->dump_cycle != -1)
        err_system(NULL, OK, *argv,
        "Multiple definition (will overwrite the last)");
    data->dump_cycle = my_atoi((char *) argv[1]);
    return OK;
}
