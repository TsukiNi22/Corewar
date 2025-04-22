/*
** EPITECH PROJECT, 2025
** dump.c
** File description:
** Sho the memory content
*/

#include "op.h"
#include "write.h"
#include "corewar.h"
#include "error.h"

int dump_memory(unsigned char memory[MEM_SIZE])
{
    int res = OK;

    if (!memory)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i != 0 && i % 32 == 0)
            res += my_putchar(STDOUT, '\n');
        if (memory[i] < 16)
            res += my_putchar(STDOUT, '0');
        if (memory[i] == 0)
            res += my_putchar(STDOUT, '0');
        res += my_putnbr_base(STDOUT, memory[i], "0123456789ABCDEF");
    }
    res += my_putchar(STDOUT, '\n');
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
