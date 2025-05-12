/*
** EPITECH PROJECT, 2025
** graphics_while
** File description:
** the while for the graphics corewar
*/

#include "corewar.h"
#include "error.h"
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int while_cond(main_data_t *data)
{
    if (!data)
        return KO;
    clear();
    printw("salut\n");
    refresh();
    data->getch = getch();
    return OK;
}

int display_graphics(main_data_t *data)
{
    if (!data)
        return KO;
    initscr();
    return OK;
}
