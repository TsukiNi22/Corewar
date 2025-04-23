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

static int get_info(champion_t *champion)
{
    unsigned char buffer[4] = {0};
    int fd = 0;

    if (!champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    fd = open(champion->file, O_RDONLY);
    if (fd == KO)
        return err_prog(OP_FILE_ERR, KO, ERR_INFO);
    lseek(fd, 4, SEEK_CUR);
    if (read(fd, champion->name, PROG_NAME_LENGTH + 1) != PROG_NAME_LENGTH + 1)
        return err_prog(READ_FILE_ERR, KO, ERR_INFO);
    lseek(fd, 3, SEEK_CUR);
    if (read(fd, buffer, 4) != 4)
        return err_prog(READ_FILE_ERR, KO, ERR_INFO);
    champion->size = (buffer[0] << 24)
    | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
    if (read(fd, champion->comment, COMMENT_LENGTH + 1) != COMMENT_LENGTH + 1)
        return err_prog(READ_FILE_ERR, KO, ERR_INFO);
    close(fd);
    return OK;
}

static int init_champions(main_data_t *data, champion_t *champion)
{
    if (!data || !champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (get_info(champion) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
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
    champion->alive = true;
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
        return err_system(data, KO, file, "Error can't check the given file");
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

int init_process(champion_t *champion, int index)
{
    process_t *process = NULL;

    if (!champion)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    process = malloc(sizeof(process_t));
    if (!process)
        return err_prog(MALLOC_ERR, KO, ERR_INFO);
    process->index_to_exe = index;
    process->cycle_delay = 0;
    process->cycle_since_action = 0;
    process->carry = false;
    for (int i = 0; i < REG_NUMBER; i++)
        process->registers[i] = 0;
    if (add_array(champion->process, process) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
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
    champion->process = new_array();
    if (!champion->process || init_process(champion, 0) == KO
        || init_champions(data, champion) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    if (add_array(data->champions, champion) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
