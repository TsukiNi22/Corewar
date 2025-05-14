/*
** EPITECH PROJECT, 2025
** const.c
** File description:
** Global const
*/

#include "write.h"
#include "corewar.h"
#include <stddef.h>

int const color_champions[] = {
    B_GREEN,
    B_YELLOW,
    B_BLUE,
    B_MAGENTA,
};

char const *flags[] = {
    "-h",
    "-d",
    "-D",
    "-n",
    "-a",
    "-ng",
    "-c",
    '\0',
};

char const *full_flags[] = {
    "--help",
    "-dump",
    "-Dump",
    "--number",
    "--address",
    "--no-graphics",
    "-csfml",
    NULL,
};

int (* const flag_functions[])(main_data_t *, int const, char const *[]) = {
    &flag_null, // h
    &flag_dump, // d
    &flag_ddump, // D
    &flag_number, // n
    &flag_address, // a
    &flag_graphics, // ng
    &flag_csfml, // c
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
