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

static sfColor lighten_color(sfColor c, float f) {
    return sfColor_fromRGB(
        c.r + (255 - c.r) * f,
        c.g + (255 - c.g) * f,
        c.b + (255 - c.b) * f
    );
}

static sfColor get_color(int i, bool champion)
{
    if (!champion)
        return sfColor_fromRGB(5, 5, 5);
    if (i == 0)
        return sfColor_fromRGB(0, 200, 100);
    if (i == 1)
        return sfColor_fromRGB(255, 175, 100);
    if (i == 2)
        return sfColor_fromRGB(0, 0, 150);
    return sfColor_fromRGB(200, 0, 200);
}

static int init_champion_box(main_data_t *data)
{
   if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < 4; i++) {
        data->champion_box[i] = sfRectangleShape_create();
        if (!data->champion_box[i])
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        sfRectangleShape_setSize(data->champion_box[i],
        (sfVector2f) {(WIDTH - 32.5 * 5) / 4, 150});
        sfRectangleShape_setFillColor(data->champion_box[i],
        lighten_color(get_color(i, i < data->champions->len), .1));
        sfRectangleShape_setPosition(data->champion_box[i],
        (sfVector2f) {32.5 * (i + 1) + ((WIDTH - 32.5 * 5) / 4) * i, 25});
    }
    return OK;
}

int init_memory_box(main_data_t *data)
{
   if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    data->memory_box = sfRectangleShape_create();
    if (!data->memory_box)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfRectangleShape_setSize(data->memory_box,
    (sfVector2f) {WIDTH - 75, HEIGHT - 300});
    sfRectangleShape_setFillColor(data->memory_box,
    sfColor_fromRGB(40, 40, 40));
    sfRectangleShape_setPosition(data->memory_box,
    (sfVector2f) {75 / 2, 300 - (75 / 2)});
    return OK;
}

static int init_box(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (init_champion_box(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (init_memory_box(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}

int init_csfml(main_data_t *data, char const *env[])
{
    sfVideoMode mode = {WIDTH, HEIGHT, 32};

    if (!data || !env)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (check_env_display(data, env) == KO)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    data->window = sfRenderWindow_create(mode, TITLE, sfClose, NULL);
    if (!data->window)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    data->font = sfFont_createFromFile(FONT);
    if (!data->font)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (init_box(data) == KO)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
