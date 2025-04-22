/*
** EPITECH PROJECT, 2025
** st.c
** File description:
** Execute the st op command
*/

#include "corewar.h"
#include "error.h"

int op_st(main_data_t *data, champion_t *champion, process_t *process)
{
    if (!data || !champion || !process)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return OK;
}
