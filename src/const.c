/*
** EPITECH PROJECT, 2025
** const.c
** File description:
** Global const
*/

#include "corewar.h"
#include <stddef.h>

char const *flags[] = {
    "-h",
    "-d",
    "-n",
    "-a",
    '\0',
};

char const *full_flags[] = {
    "--help",
    "-dump",
    "--number",
    "--address",
    NULL,
};

int (* const flag_functions[])(main_data_t *, int const, char const *[]) = {
    &flag_null, // h
    &flag_dump, // d
    &flag_number, // n
    &flag_address, // a
};


int (* const op_cmd[])(main_data_t *, champion_t *, process_t *) = {
    &op_live,
    &op_ld,
    &op_st,
    &op_add,
    &op_sub,
    &op_and,
    &op_or,
    &op_xor,
    &op_zjmp,
    &op_ldi,
    &op_sti,
    &op_fork,
    &op_lld,
    &op_lldi,
    &op_lfork,
    &op_aff,
};
