/*
** EPITECH PROJECT, 2025
** render_csfml.c
** File description:
** Render the csfml graphics
*/

#include "memory.h"
#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <stddef.h>

static int render_champion_text(main_data_t *data, champion_t *champion, size_t i)
{
    sfRectangleShape *alive = NULL;
    sfText *text = NULL;
    char *name = NULL;
    char *str = NULL;
    char *process = NULL;
    char *id = NULL;

    if (!data || (i < data->champions->len && !champion))
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    if (i >= data->champions->len) {
        text = sfText_create();
        if (!text)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        sfText_setString(text, "None");
        sfText_setFont(text, data->font);
        sfText_setCharacterSize(text, 50);
        sfText_setPosition(text,
        (sfVector2f) {32.5 * (i + 1) + ((WIDTH - 32.5 * 5) / 4) * (i + .5) - 55
        , 25 + 150 / 2 - 35});
        sfText_setColor(text, sfWhite);
        sfRenderWindow_drawText(data->window, text, NULL);
        sfText_destroy(text);
        return OK;
    }

    text = sfText_create();
    if (!text || my_malloc_c(&name, 8 + PROG_NAME_LENGTH + 1) == KO
        || !my_strcat(name, "Name -> ") || !my_strcat(name, champion->name))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfText_setString(text, name);
    sfText_setFont(text, data->font);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text,
    (sfVector2f) {32.5 * (i + 1) + ((WIDTH - 32.5 * 5) / 4) * i + 10, 25 + 10});
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(data->window, text, NULL);
    sfText_destroy(text);
    free(name);
    
    text = sfText_create();
    id = my_itoa(champion->prog_number);
    if (!text || !id || my_malloc_c(&str, 5 + 10 + 1) == KO
        || !my_strcat(str, "Id -> ") || !my_strcat(str, id))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfText_setString(text, str);
    sfText_setFont(text, data->font);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text,
    (sfVector2f) {32.5 * (i + 1) + ((WIDTH - 32.5 * 5) / 4) * i + 10, 25 + 40});
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(data->window, text, NULL);
    sfText_destroy(text);
    free(id);
    free(str);

    text = sfText_create();
    process = my_itoa(champion->process->len);
    if (!text || !process || my_malloc_c(&str, 11 + 10 + 1) == KO
        || !my_strcat(str, "Process -> ") || !my_strcat(str, process))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfText_setString(text, str);
    sfText_setFont(text, data->font);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text,
    (sfVector2f) {32.5 * (i + 1) + ((WIDTH - 32.5 * 5) / 4) * i + 10, 25 + 70});
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(data->window, text, NULL);
    sfText_destroy(text);
    free(process);
    free(str);

    text = sfText_create();
    sfText_setString(text, "Alive ->");
    sfText_setFont(text, data->font);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text,
    (sfVector2f) {32.5 * (i + 1) + ((WIDTH - 32.5 * 5) / 4) * i + 10, 25 + 100});
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(data->window, text, NULL);
    sfText_destroy(text);

    alive = sfRectangleShape_create();
    if (!alive)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfRectangleShape_setSize(alive, (sfVector2f){30, 30});
    if (champion->alive)
        sfRectangleShape_setFillColor(alive, sfGreen);
    else
        sfRectangleShape_setFillColor(alive, sfRed);
    sfRectangleShape_setPosition(alive,
    (sfVector2f) {32.5 * (i + 1) + ((WIDTH - 32.5 * 5) / 4) * i + 125, 25 + 100});
    sfRenderWindow_drawRectangleShape(data->window, alive, NULL);
    sfRectangleShape_destroy(alive);
    return OK;
}

static int render_box(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < 4; i++) {
        sfRenderWindow_drawRectangleShape(data->window,
        data->champion_box[i], NULL);
        if (render_champion_text(data, data->champions->data[i], i) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    sfRenderWindow_drawRectangleShape(data->window,
    data->memory_box, NULL);
    return OK;
}

int render_csfml(main_data_t *data)
{
    sfEvent event = {0};

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    while (sfRenderWindow_pollEvent(data->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(data->window);
    }
    sfRenderWindow_clear(data->window, sfBlack);
    if (render_box(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfRenderWindow_display(data->window);
    return OK;
}
