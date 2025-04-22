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
typedef uint8_t reg_t;
#elif REG_SIZE == 2
typedef uint16_t reg_t;
#elif REG_SIZE == 4
typedef uint32_t reg_t;
#elif REG_SIZE == 8
typedef uint64_t reg_t;
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
    bool alive;
    bool carry;
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
    unsigned char memory[MEM_SIZE];

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
int setup(main_data_t *data); // Error: KO
int dump_memory(unsigned char memory[MEM_SIZE]); // Error: KO
int update_cycle(main_data_t *data); // Error: KO
int exe_memory(main_data_t *data); // Error: KO

/* op_cmd */
int op_live(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_ld(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_st(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_add(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_sub(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_and(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_or(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_xor(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_zjmp(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_ldi(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_sti(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_fork(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_lld(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_lldi(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_lfork(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO
int op_aff(champion_t *champion, process_t *process,
    unsigned char memory[MEM_SIZE]); // Error: KO

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

/* op command */
extern int (* const op_cmd[])(champion_t *, process_t *, unsigned char [MEM_SIZE]);

#endif /* COREWAR_H */
