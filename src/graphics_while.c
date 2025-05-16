/*
** EPITECH PROJECT, 2025
** graphics_while
** File description:
** the while for the graphics corewar
*/

#include "corewar.h"
#include "array.h"
#include "op.h"
#include "error.h"
#include "write.h"
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

int my_back_color(back_color_t back)
{
    int bg = back - 40;
    int pair_id = 10 + bg;

    init_pair(pair_id, COLOR_WHITE, bg);
    attron(COLOR_PAIR(pair_id));
    return pair_id;
}

static bool is_cursor(array_t *champions, int index)
{
    champion_t *champion = NULL;
    process_t *process = NULL;
    bool is = false;

    if (!champions)
        return false;
    for (size_t i = 0; !is && i < champions->len; i++) {
        champion = (champion_t *) champions->data[i];
        for (size_t j = 0; !is && j < champion->process->len; j++) {
            process = (process_t *) champion->process->data[j];
            is = (process->index_to_exe == index);
        }
    }
    return is;
}

static int set_color_byte(array_t *champions, int i, int apartenance)
{
    size_t index = 0;

    if (!champions)
        return -1;
    if (is_cursor(champions, i))
        return my_back_color(B_RED);
    if (apartenance == KO)
        return -1;
    for (index = 0; index < champions->len &&
        ((champion_t *)champions->data[index])->prog_number
        != apartenance; index++);
    if (index >= champions->len)
        return -1;
    return my_back_color(color_champions[index % 4]);
}

int dump_custom_graphics(array_t *champions,
    unsigned char memory[MEM_SIZE], int apartenance[MEM_SIZE])
{
    int pair_id = 0;
    int i = 0;

    if (!champions || !memory || !apartenance)
        return KO;
    for (i = 0; i < MEM_SIZE; i++) {
        if (i != 0 && i % 64 == 0)
            printw("\n");
        pair_id = set_color_byte(champions, i, apartenance[i]);
        printw("%02x ", memory[i]);
        if (pair_id >= 0)
            attroff(COLOR_PAIR(pair_id));
    }
    printw("\n");
    return OK;
}

int while_cond(main_data_t *data)
{
    if (!data)
        return KO;
    clear();
    printw("Total cycle -> %-10d Cycle to die: %4d/%4d "
    "\t\tLive number: %2d/%d\n",
    data->total_cycle,
    data->actual_cycle, data->cycle_to_die,
    data->nbr_live, NBR_LIVE);
    dump_custom_graphics(data->champions, data->memory, data->apartenance);
    refresh();
    data->getch = getch();
    usleep(5000);
    return OK;
}

int display_graphics(main_data_t *data)
{
    if (!data)
        return KO;
    data->alive = 0;
    initscr();
    curs_set(FALSE);
    start_color();
    use_default_colors();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    return OK;
}
