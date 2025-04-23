/*
** EPITECH PROJECT, 2025
** dump.c
** File description:
** Sho the memory content
*/

#include "op.h"
#include "array.h"
#include "write.h"
#include "corewar.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>

static bool is_cursor(array_t *champions, int index)
{
    champion_t *champion = NULL;
    process_t *process = NULL;
    bool is = false;

    if (!champions)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; !is && i < champions->len; i++) {
        champion = (champion_t *) champions->data[i];
        for (size_t j = 0; !is && j < champion->process->len; j++) {
            process = champion->process->data[j];
            is = (process->index_to_exe == index);
        }
    }
    return is;
}

int dump_custom(array_t *champions, unsigned char memory[MEM_SIZE])
{
    int res = OK;

    if (!champions || !memory)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i != 0 && i % 64 == 0)
            res += my_putchar(STDOUT, '\n');
        if (is_cursor(champions, i))
            res += back_color(STDOUT, B_RED);
        if (memory[i] < 16)
            res += my_putchar(STDOUT, '0');
        if (memory[i] == 0)
            res += my_putchar(STDOUT, '0');
        res += my_putnbr_base(STDOUT, memory[i], "0123456789ABCDEF");
        res += reset_ouput(STDOUT);
        res += my_putchar(STDOUT, ' ');
    }
    res += my_putchar(STDOUT, '\n');
    return KO * (res != OK);
}

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
