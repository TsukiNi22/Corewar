/*
** EPITECH PROJECT, 2025
** init_csfml.c
** File description:
** init the csfml option
*/

#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <SFML/Graphics.h>
#include <stddef.h>
#include <stdbool.h>

static int check_env_display(main_data_t *data, char const *env[])
{
    bool display = false;

    if (!data || !env)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; !display && env[i]; i++) {
        if (my_strcmp(env[i], "DISPLAY=:1") == 0)
            display = true;
    }
    if (!display)
        return err_system(data, KO, "env", "Can't found the environement "
        "variable 'DISPLAY' with the value ':1'");
    return OK;
}

int init_csfml(main_data_t *data, char const *env[])
{
    sfVideoMode mode = {800, 600, 32};

    if (!data || !env)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (check_env_display(data, env) == KO)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    data->window = sfRenderWindow_create(mode, TITLE, sfClose, NULL);
    if (!data->window)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
