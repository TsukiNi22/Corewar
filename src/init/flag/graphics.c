/*
** EPITECH PROJECT, 2025
** graphics.c
** File description:
** set the option for graphics
*/

#include "macro.h"
#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>

int flag_graphics(main_data_t *data, UNUSED int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (data->no_graphics)
        err_system(NULL, OK, *argv,
        "Multiple definition (will overwrite the last)");
    data->no_graphics = true;
    return OK;
}
