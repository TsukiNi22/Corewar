/*
** EPITECH PROJECT, 2025
** number.c
** File description:
** set the option for number
*/

#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>

int flag_number(main_data_t *data, int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (argc == 1)
        return err_system(data, KO, *argv, "Insufficient argument");
    if (!my_str_is(argv[1], "0123456789"))
        return err_system(data, KO, argv[1], "Can only be composed of [0-9]");
    if (data->next_prog_number != -1)
        err_system(NULL, OK, *argv,
        "Multiple definition (will overwrite the last)");
    data->next_prog_number = my_atoi((char *) argv[1]);
    return OK;
}
