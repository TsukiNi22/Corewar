/*
** EPITECH PROJECT, 2025
** render_info.c
** File description:
** render the info
*/

#include "write.h"
#include "memory.h"
#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stdlib.h>

static int destroy(sfText *text, char *value, char *str)
{
    if (!text || !value || !str)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    sfText_destroy(text);
    free(value);
    free(str);
    return OK;
}

static int display_total(main_data_t *data)
{
    sfText *text = NULL;
    char *str = NULL;
    char *value = NULL;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    text = sfText_create();
    value = my_itoa(data->total_cycle);
    if (!text || !value || my_malloc_c(&str, 16 + 10 + 1) == KO
        || !my_strcat(str, "Total Cycles -> ") || !my_strcat(str, value))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfText_setString(text, str);
    sfText_setFont(text, data->font);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text, (sfVector2f) {250, 175 + 40});
    sfText_setColor(text, sfWhite);
    sfRenderWindow_drawText(data->window, text, NULL);
    return destroy(text, value, str);
}

static int setup_str(char **str, char *text, char *values[2])
{
    if (!str || !text || !values)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (my_malloc_c(str, my_strlen(text) + 10 + 1 + 10 + 1) == KO
        || !my_strcat(*str, text) || !my_strcat(*str, values[0])
        || !my_strcat(*str, "/") || !my_strcat(*str, values[1]))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}

static int display_death(main_data_t *data)
{
    sfText *text = NULL;
    char *values[2] = {NULL};
    char *str = NULL;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    text = sfText_create();
    values[0] = my_itoa(data->actual_cycle);
    values[1] = my_itoa(data->cycle_to_die);
    if (!text || !values[0] || !values[1]
        || setup_str(&str, "Cycles to die -> ", values) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfText_setString(text, str);
    sfText_setFont(text, data->font);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text, (sfVector2f) {650, 175 + 40});
    sfText_setColor(text, sfWhite);
    sfRenderWindow_drawText(data->window, text, NULL);
    free(values[0]);
    return destroy(text, values[1], str);
}

static int display_live(main_data_t *data)
{
    sfText *text = NULL;
    char *values[2] = {NULL};
    char *str = NULL;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    text = sfText_create();
    values[0] = my_itoa(data->nbr_live);
    values[1] = my_itoa(NBR_LIVE);
    if (!text || !values[0] || !values[1]
        || setup_str(&str, "Live number -> ", values) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfText_setString(text, str);
    sfText_setFont(text, data->font);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text, (sfVector2f) {1150, 175 + 40});
    sfText_setColor(text, sfWhite);
    sfRenderWindow_drawText(data->window, text, NULL);
    free(values[0]);
    return destroy(text, values[1], str);
}

int render_info(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (display_total(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (display_death(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (display_live(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
