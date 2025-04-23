/*
** EPITECH PROJECT, 2025
** live.c
** File description:
** Execute the live op command
*/

#include "write.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

int op_live(main_data_t *data, champion_t *champion, process_t *process)
{
    int res = OK;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    champion->alive = true;
    data->nbr_live++;
    process->index_to_exe += 4 + 1;
    res += my_putstr(STDOUT, "The player ");
    res += my_putnbr(STDOUT, champion->prog_number);
    res += my_putchar(STDOUT, '(');
    res += my_putstr(STDOUT, champion->name);
    res += my_putstr(STDOUT, ")is alive.\n");
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
