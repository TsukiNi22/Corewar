/*
** EPITECH PROJECT, 2025
** init_argument.c
** File description:
** Init the argument option
*/

#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stdbool.h>

static bool is_flag(char const *str, int *index)
{
    if (!index)
        return err_prog(PTR_ERR, false, ERR_INFO);
    for (int i = 0; flags[i]; i++) {
        if (my_strcmp(flags[i], str) == 0
            || my_strcmp(full_flags[i], str) == 0) {
            *index = i;
            return true;
        }
    }
    return false;
}

static int flag(main_data_t *data,
    int const argc, char const *argv[],
    int *i)
{
    int index = 0;

    if (!data || !argv || !i)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (!is_flag(argv[*i], &index))
        return err_system(data, KO, argv[*i], "Unrecognized option");
    if (flag_functions[index](data, argc - *i, &(argv[*i])) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    (*i)++;
    return OK;
}

int init_argument(main_data_t *data, int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 1; i < argc; i++) {
        if (my_strcmp(argv[i], flags[0]) == 0
            || my_strcmp(argv[i], full_flags[0]) == 0) {
            data->help = true;
            return flag_help();
        }
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' && add_champions(data, argv[i]) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (argv[i][0] == '-' && flag(data, argc, argv, &i) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}
