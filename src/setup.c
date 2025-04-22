/*
** EPITECH PROJECT, 2025
** setup.c
** File description:
** Setup the memory / start point
*/

#include "op.h"
#include "corewar.h"
#include "error.h"
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>

static int setup_index_champion(main_data_t *data)
{
    champion_t *champion = NULL;
    int index = 0;
    int diff = 0;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    diff = MEM_SIZE / data->champions->len;
    for (size_t i = 0; i < data->champions->len; i++) {
        champion = data->champions->data[i];
        if (champion->load_address == KO)
            champion->load_address = index % MEM_SIZE;
        index += diff;
    }
    return OK;
}

static int set_prog(main_data_t *data, char const *file,
    size_t size, int load_address)
{
    unsigned char buffer[size];
    int fd = 0;

    if (!data || !file)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    fd = open(file, O_RDONLY);
    if (fd == KO)
        return err_prog(OP_FILE_ERR, KO, ERR_INFO);
    lseek(fd, 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4, SEEK_SET);
    if (read(fd, buffer, size) != (int) size)
        return err_prog(READ_FILE_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < size; i++)
        data->memory[load_address + i] = buffer[i];
    close(fd);
    return OK;
}

static int setup_memory(main_data_t *data)
{
    champion_t *champion = NULL;

    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (size_t i = 0; i < data->champions->len; i++) {
        champion = data->champions->data[i];
        if (set_prog(data, champion->file, champion->size,
            champion->load_address) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}

int setup(main_data_t *data)
{
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (setup_index_champion(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (setup_memory(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
