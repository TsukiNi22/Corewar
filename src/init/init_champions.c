/*
** EPITECH PROJECT, 2025
** init_champions.c
** File description:
** Init the champions struct
*/

#include "op.h"
#include "array.h"
#include "corewar.h"
#include "error.h"
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>

static bool already_used(array_t *champions, int n)
{
    if (!champions)
        return err_prog(PTR_ERR, true, ERR_INFO);
    for (size_t i = 0; i < champions->len; i++) {
        if (((champion_t *) champions->data[i])->prog_number == n)
            return true;
    }
    return false;
}

static int get_number(array_t *champions)
{
    bool changed = true;
    int n = 1;

    if (!champions)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    while (changed) {
        changed = false;
        for (size_t i = 0; i < champions->len && !changed; i++) {
            changed = (((champion_t *) champions->data[i])->prog_number == n);
            n += changed;
        }
        if (n == INT_MAX)
            return KO;
    }
    return n;
}

static int init_champions(main_data_t *data, champion_t *champion)
{
    if (!data || !champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    champion->name[PROG_NAME_LENGTH] = '\0';
    champion->comment[COMMENT_LENGTH] = '\0';
    champion->cycle_delay = 0;
    champion->cycle_since_action = 0;
    if (data->next_prog_number != -1
        && already_used(data->champions, data->next_prog_number))
        return err_system(data, KO, "champion",
        "Can't use the same number to define tow champion");
    if (data->next_prog_number != -1)
        champion->prog_number = data->next_prog_number;
    else
        champion->prog_number = get_number(data->champions);
    champion->load_address = data->next_load_address;
    data->next_prog_number = -1;
    data->next_load_address = -1;
    for (int i = 0; i < REG_NUMBER; i++)
        champion->registers[i] = 0;
    return OK;
}

int add_champions(main_data_t *data, char const *file)
{
    champion_t *champion = NULL;

    if (!data || !file)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    champion = malloc(sizeof(champion_t));
    if (!champion)
        return err_prog(MALLOC_ERR, KO, ERR_INFO);
    champion->file = file;
    if (init_champions(data, champion) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (add_array(data->champions, champion) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
