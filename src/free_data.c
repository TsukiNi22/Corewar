/*
** EPITECH PROJECT, 2025
** free_data.c
** File description:
** Free data
*/

#include "array.h"
#include "corewar.h"
#include "error.h"
#include <stdlib.h>
#include <SFML/Graphics.h>

static int free_ptr(void *ptr)
{
    if (!ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    free(ptr);
    return OK;
}

static int free_champions(void *ptr)
{
    champion_t *champion = ptr;

    if (!ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (delete_array(&champion->process, &free_ptr) == KO)
        return err_prog(UNDEF_ERR, EPITECH_ERR, ERR_INFO);
    free(champion);
    return OK;
}

int free_csfml(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (data->window)
        sfRenderWindow_destroy(data->window);
    for (int i = 0; i < 4; i++) {
        if (data->champion_box[i])
            sfRectangleShape_destroy(data->champion_box[i]);
    }
    if (data->memory_box)
        sfRectangleShape_destroy(data->memory_box);
    if (data->font)
        sfFont_destroy(data->font);
    return OK;
}

int free_data(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, EPITECH_ERR, ERR_INFO);
    if (data->champions
        && delete_array(&data->champions, &free_champions) == KO)
        return err_prog(UNDEF_ERR, EPITECH_ERR, ERR_INFO);
    if (free_csfml(data) == KO)
        return err_prog(UNDEF_ERR, EPITECH_ERR, ERR_INFO);
    return OK;
}
