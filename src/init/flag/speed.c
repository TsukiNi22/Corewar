/*
** EPITECH PROJECT, 2025
** speed.c
** File description:
** set the option for speed
*/

#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>

int flag_speed(main_data_t *data, int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (argc == 1)
        return err_system(data, KO, *argv, "Insufficient argument");
    if (!my_str_is(argv[1], "0123456789"))
        return err_system(data, KO, argv[1], "Can only be composed of [0-9]");
    data->speed = my_atoi((char *) argv[1]);
    if (data->speed == 0)
        return err_system(data, KO, argv[1], "Can only be superior to 0");
    return OK;
}
