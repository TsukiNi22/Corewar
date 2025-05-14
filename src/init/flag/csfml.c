/*
** EPITECH PROJECT, 2025
** csfml.c
** File description:
** set the option for csfml
*/

#include "macro.h"
#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>

int flag_csfml(main_data_t *data, UNUSED int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (data->csfml)
        err_system(NULL, OK, *argv,
        "Multiple definition (will overwrite the last)");
    data->csfml = true;
    return OK;
}
