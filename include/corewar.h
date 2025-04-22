/*
** EPITECH PROJECT, 2025
** corewar.h
** File description:
** Corewar header
*/

#ifndef COREWAR_H
    #define COREWAR_H

    //----------------------------------------------------------------//
    /* INCLUDE */

    /* define */
    #include <op.h> // define const

    /* type */
    #include <array.h> // array_t
    #include <stdbool.h> // boolean
    #include <stdint.h> // intx_t

//----------------------------------------------------------------//
/* TYPEDEF */

/* Setup of the size of the reg */
#if REG_SIZE == 1
typedef int8_t reg_t;
#elif REG_SIZE == 2
typedef int16_t reg_t;
#elif REG_SIZE == 4
typedef int32_t reg_t;
#elif REG_SIZE == 8
typedef int64_t reg_t;
#else
    #error "Unsupported REG_SIZE"
#endif

/* champions status */
typedef struct process_s {
    /* status */
    int index_to_exe;
    int cycle_delay;
    int cycle_since_action;
} process_t;

/* champions */
typedef struct champion_s {
    /* file */
    char const *file;

    /* info */
    char name[PROG_NAME_LENGTH + 1];
    char comment[COMMENT_LENGTH + 1];
    int size;

    /* status */
    array_t *process;

    /* reg */
    reg_t registers[REG_NUMBER];

    /* option */
    int prog_number;
    int load_address;
} champion_t;

/* data */
typedef struct main_data_s {
    /* global info */
    char const *exe_name;

    /* memory */
    char memory[MEM_SIZE];

    /* champions list */
    array_t *champions;

    /* live status */
    bool live_status[MAX_CHAMPIONS];
    int nbr_live;
    int total_cycle;
    int actual_cycle;
    int cycle_to_die;

    /* option */
    int dump_cycle;
    int next_prog_number;
    int next_load_address;

    /* ouput */
    bool help;
    bool err_sys;
} main_data_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* corewar */ // Error: KO
int corewar(int const argc, char const *argv[], main_data_t *data);

/* init_data */
int init_data(main_data_t *data); // Error: KO
int init_global(main_data_t *data); // Error: KO
int init_option(main_data_t *data); // Error: KO
int init_process(champion_t *champion, int index); // Error: KO

/* init_argument */
int init_argument(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int add_champions(main_data_t *data, char const *file); // Error: KO
int flag_help(void); // Error: KO
int flag_null(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_dump(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_number(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_address(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO

/* exit */
int free_data(main_data_t *data); // Error: EPITECH_ERR

//----------------------------------------------------------------//
/* GLOBAL_CONST */

/* flag */
extern char const *flags[];
extern char const *full_flags[];
extern int (* const flag_functions[])(main_data_t *,
    int const, char const *[]);

#endif /* COREWAR_H */
