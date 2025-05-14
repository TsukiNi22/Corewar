/*
** EPITECH PROJECT, 2025
** corewar.c
** File description:
** Corewar
*/

#include "op.h"
#include "write.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>
#include <ncurses.h>

static bool is_end(bool live_status[MAX_CHAMPIONS], size_t len)
{
    bool alive = false;

    if (!live_status)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < len; i++) {
        if (alive && live_status[i])
            return false;
        alive = (alive || live_status[i]);
    }
    return true;
}

static int put_info(main_data_t *data)
{
    champion_t *champion = NULL;
    int res = OK;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < data->champions->len; i++) {
        champion = data->champions->data[i];
        res += my_putstr(STDOUT, "Process number of n°");
        res += my_putnbr(STDOUT, champion->prog_number);
        res += my_putstr(STDOUT, ": ");
        res += my_putnbr(STDOUT, champion->process->len);
        res += my_putchar(STDOUT, '\n');
    }
    res += my_putstr(STDOUT, "Number of cycle: ");
    res += my_putnbr(STDOUT, data->total_cycle);
    res += my_putchar(STDOUT, '\n');
    res += my_putstr(STDOUT, "Deat cycle: ");
    res += my_putnbr(STDOUT, data->cycle_to_die);
    res += my_putchar(STDOUT, '\n');
    return KO * (res != OK);
}

static int dump(main_data_t *data)
{
    int res = OK;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (data->spe_dump) {
        res += dump_custom(data->champions, data->memory, data->apartenance);
        res += put_info(data);
        if (res != OK)
            return err_prog(PTR_ERR, KO, ERR_INFO);
    }
    if (!data->spe_dump)
        return dump_memory(data->memory);
    return OK;
}

static int who_as_won(main_data_t *data)
{
    champion_t *champion = NULL;
    int alive = KO;
    int res = OK;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; alive == KO && i < data->champions->len; i++)
        alive = i - (i + 1) * !data->live_status[i];
    if (alive == KO)
        return my_putstr(STDOUT, "It's a tie, no player has won.\n");
    champion = data->champions->data[alive];
    res += my_putstr(STDOUT, "The player ");
    res += my_putnbr(STDOUT, champion->prog_number);
    res += my_putchar(STDOUT, '(');
    res += my_putstr(STDOUT, champion->name);
    res += my_putstr(STDOUT, ")has won.\n");
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}

static int loop(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    noecho();
    nodelay(stdscr, TRUE);
    while (!is_end(data->live_status, data->champions->len)) {
        if (data->dump_cycle != KO && data->total_cycle >= data->dump_cycle)
            return dump(data);
        if (exe_memory(data) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (update_cycle(data) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (while_cond(data) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (data->getch == 'q' || data->getch == 'Q' || data->alive == 1)
            break;
    }
    endwin();
    if (data->dump_cycle != KO && dump(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return who_as_won(data);
}

int corewar(int const argc, char const *argv[], main_data_t *data)
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (init_data(data) == KO)
        return err_custom("Data initialisation error", FATAL_ERR, ERR_INFO);
    if (init_argument(data, argc, argv) == KO)
        return err_custom("Argument initialisation error", KO, ERR_INFO);
    if (data->help)
        return OK;
    if (setup(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (display_graphics(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (loop(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
