/*
** EPITECH PROJECT, 2025
** sub.c
** File description:
** Execute the sub op command
*/

#include "corewar.h"
#include "error.h"

int op_sub(main_data_t *data, champion_t *champion, process_t *process)
{
    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
