/*
** EPITECH PROJECT, 2025
** render_memory.c
** File description:
** render the memory
*/

#include "write.h"
#include "memory.h"
#include "my_string.h"
#include "corewar.h"
#include "error.h"
#include <stdlib.h>

static int set_value(char *value, unsigned char o)
{
    char hexa[16] = "0123456789ABCDEF";

    if (!value)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    value[0] = hexa[(o / 16) % 16];
    value[1] = hexa[o % 16];
    return OK;
}

static sfColor lighten_color(sfColor c, float f)
{
    return sfColor_fromRGB(
        c.r + (255 - c.r) * f,
        c.g + (255 - c.g) * f,
        c.b + (255 - c.b) * f
    );
}

static bool is_cursor(array_t *champions, int index)
{
    champion_t *champion = NULL;
    process_t *process = NULL;
    bool is = false;

    if (!champions)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; !is && i < champions->len; i++) {
        champion = (champion_t *) champions->data[i];
        for (size_t j = 0; !is && j < champion->process->len; j++) {
            process = champion->process->data[j];
            is = (process->index_to_exe == index);
        }
    }
    return is;
}

static sfColor get_color(main_data_t *data, int index, int apartenance)
{
    champion_t *champion = NULL;
    int i = KO;

    if (is_cursor(data->champions, index))
        return sfRed;
    for (size_t j = 0; i == KO && j < data->champions->len; j++) {
        champion = data->champions->data[j];
        if (champion->prog_number == apartenance)
            i = j;
    }
    if (i == 0)
        return sfColor_fromRGB(0, 200, 100);
    if (i == 1)
        return sfColor_fromRGB(255, 175, 100);
    if (i == 2)
        return sfColor_fromRGB(0, 0, 150);
    if (i == 3)
        return sfColor_fromRGB(200, 0, 200);
    return sfWhite;
}

static int set_text(main_data_t *data, sfText **text, char *value)
{
    if (!data || !text || !value)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    *text = sfText_create();
    if (!*text)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    sfText_setString(*text, value);
    sfText_setFont(*text, data->font);
    sfText_setCharacterSize(*text, 13);
    return OK;
}

int render_memory(main_data_t *data)
{
    sfText *text = NULL;
    char *value = NULL;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (my_malloc_c(&value, 3) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    for (int i = 0; i < MEM_SIZE; i++) {
        if (set_value(value, data->memory[i]) == KO
            || set_text(data, &text, value) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        sfText_setPosition(text, (sfVector2f) {75 / 2 + 2.5 + 15.825 *
        (i % LINE_OCTET), 300 - (75 / 2) + 10 * (i / LINE_OCTET)});
        sfText_setColor(text, lighten_color(
        get_color(data, i, data->apartenance[i]), .1));
        sfRenderWindow_drawText(data->window, text, NULL);
        sfText_destroy(text);
    }
    free(value);
    return OK;
}
