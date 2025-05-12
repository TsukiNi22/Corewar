/*
** EPITECH PROJECT, 2025
** graphics_while
** File description:
** the while for the graphics corewar
*/

#include "corewar.h"
#include "error.h"
#include "write.h"
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

/*
** EPITECH PROJECT, 2025
** dump.c
** File description:
** Sho the memory content
*/

#include "op.h"
#include "array.h"
#include "write.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

static int const color_champions[] = {
    B_GREEN,
    B_YELLOW,
    B_BLUE,
    B_MAGENTA,
};

int my_back_color(back_color_t back)
{
    int res = OK;

    printw("\x1B");
    printw("[");
    printw("%d", back);
    printw("m");
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
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

static int set_color_byte(array_t *champions, int i, int apartenance)
{
    size_t index = 0;

    if (!champions)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (is_cursor(champions, i))
        return my_back_color(B_RED);
    if (apartenance == KO)
        return OK;
    for (index = 0; ((champion_t *) champions->data[index])->prog_number
        != apartenance; index++);
    return my_back_color(color_champions[index]);
}

int dump_custom_graphics(array_t *champions, unsigned char memory[MEM_SIZE],
    int apartenance[MEM_SIZE])
{
    int res = OK;

    if (!champions || !memory || !apartenance)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i != 0 && i % 64 == 0)
            printw("\n");
        if (set_color_byte(champions, i, apartenance[i]) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (memory[i] < 16)
            printw("0");
        if (memory[i] == 0)
            printw("0");
        printw("%d", memory[i]);
        printw(" ");
    }
    printw("\n");
    return KO * (res != OK);
}

int while_cond(main_data_t *data)
{
    if (!data)
        return KO;
    clear();
    dump_custom_graphics(data->champions, data->memory, data->apartenance);
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
