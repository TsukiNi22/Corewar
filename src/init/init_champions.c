/*
** EPITECH PROJECT, 2025
** init_champions.c
** File description:
** Init the champions struct
*/

#include "op.h"
#include "array.h"
#include "corewar.h"
#include "error.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>

static bool already_used(array_t *champions, int n)
{
    if (!champions)
        return err_prog(PTR_ERR, true, ERR_INFO);
    for (size_t i = 0; i < champions->len; i++) {
        if (((champion_t *) champions->data[i])->prog_number == n)
            return true;
    }
    return false;
}

static int get_number(array_t *champions)
{
    bool changed = true;
    int n = 1;

    if (!champions)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    while (changed) {
        changed = false;
        for (size_t i = 0; i < champions->len && !changed; i++) {
            changed = (((champion_t *) champions->data[i])->prog_number == n);
            n += changed;
        }
        if (n == INT_MAX)
            return KO;
    }
    return n;
}

static int init_champions(main_data_t *data, champion_t *champion)
{
    if (!data || !champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    champion->name[PROG_NAME_LENGTH] = '\0';
    champion->comment[COMMENT_LENGTH] = '\0';
    champion->cycle_delay = 0;
    champion->cycle_since_action = 0;
    if (data->next_prog_number != -1
        && already_used(data->champions, data->next_prog_number))
        return err_system(data, KO, "champion",
        "Can't use the same number to define tow champion");
    if (data->next_prog_number != -1)
        champion->prog_number = data->next_prog_number;
    else
        champion->prog_number = get_number(data->champions);
    champion->load_address = data->next_load_address;
    data->next_prog_number = -1;
    data->next_load_address = -1;
    for (int i = 0; i < REG_NUMBER; i++)
        champion->registers[i] = 0;
    return OK;
}

static int check_file(main_data_t *data, char const *file)
{
    struct stat st = {0};
    unsigned char buffer[4] = {0};
    int fd = 0;

    if (!data || !file)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (lstat(file, &st) == KO)
        return err_system(data, KO, file, "Insufficient permission or Error");
    if (!S_ISREG(st.st_mode))
        return err_system(data, KO, file, "This definitly not a regular file");
    fd = open(file, O_RDONLY);
    if (fd == KO)
        return err_system(data, KO, file, "Can't read the given file");
    if (read(fd, buffer, 4) != 4)
        return err_prog(READ_FILE_ERR, KO, ERR_INFO);
    if (COREWAR_EXEC_MAGIC !=
        ((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3]))
        return err_system(data, KO, file, "Invalid magic number");
    close(fd);
    return OK;
}

int add_champions(main_data_t *data, char const *file)
{
    champion_t *champion = NULL;

    if (!data || !file)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (data->champions->len == MAX_CHAMPIONS)
        return err_system(data, KO, data->exe_name,
        "Too many champions are given");
    if (check_file(data, file) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    champion = malloc(sizeof(champion_t));
    if (!champion)
        return err_prog(MALLOC_ERR, KO, ERR_INFO);
    champion->file = file;
    if (init_champions(data, champion) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (add_array(data->champions, champion) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
