/*
** EPITECH PROJECT, 2025
** ddump.c
** File description:
** set the option for ddump
*/

#include "macro.h"
#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>

int flag_ddump(main_data_t *data, UNUSED int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (data->spe_dump)
        err_system(NULL, OK, *argv,
        "Multiple definition (will overwrite the last)");
    data->spe_dump = true;
    return OK;
}
