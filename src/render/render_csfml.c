/*
** EPITECH PROJECT, 2025
** render_csfml.c
** File description:
** Render the csfml graphics
*/

#include "corewar.h"
#include "error.h"
#include <SFML/Graphics.h>

int render_csfml(main_data_t *data)
{
    sfEvent event = {0};

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    while (sfRenderWindow_pollEvent(data->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(data->window);
        if (event.type == sfEvtKeyPressed && event.key.code == 16)
            sfRenderWindow_close(data->window);
    }
    sfRenderWindow_clear(data->window, sfBlack);
    if (render_box(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (render_memory(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfRenderWindow_display(data->window);
    return OK;
}
