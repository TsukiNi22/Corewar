/*
** EPITECH PROJECT, 2025
** param.c
** File description:
** Return the param type for x arg
*/

#include "op.h"

int get_param(unsigned char value, int arg_nb)
{
    int val = -1;

    if (arg_nb == 1)
        val = (value >> 6) & 0x3;
    if (arg_nb == 2)
        val = (value >> 4) & 0x3;
    if (arg_nb == 3)
        val = (value >> 2) & 0x3;
    if (arg_nb == 4)
        val = value & 0x3;
    if (val == 0x1)
        return T_REG;
    if (val == 0x2)
        return T_DIR;
    if (val == 0x3)
        return T_IND;
    return 0;
}
