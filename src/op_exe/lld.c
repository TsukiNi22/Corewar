/*
** EPITECH PROJECT, 2025
** lld.c
** File description:
** Execute the lld op command
*/

#include "corewar.h"
#include "error.h"

int op_lld(main_data_t *data, champion_t *champion, process_t *process)
{
    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
