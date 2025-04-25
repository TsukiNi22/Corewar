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
    champion_t *index_champion = NULL;
    size_t index = 0;
    int arg = 0;
    int res = OK;

    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < DIR_SIZE; i++)
        arg += data->memory[(process->index_to_exe + i + 1) % MEM_SIZE]
        << (8 * (DIR_SIZE - (1 + i)));
    for (index = 0; index < data->champions->len
        && ((champion_t *) data->champions->data[index])->prog_number
        != arg; index++);
    if (index < data->champions->len) {
        index_champion = data->champions->data[index]; 
        index_champion->alive = true;
        data->nbr_live++;
        res += my_putstr(STDOUT, "The player ");
        res += my_putnbr(STDOUT, index_champion->prog_number);
        res += my_putchar(STDOUT, '(');
        res += my_putstr(STDOUT, index_champion->name);
        res += my_putstr(STDOUT, ")is alive.\n");
        if (res != OK)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    process->index_to_exe += DIR_SIZE + 1;
    return OK;
}
