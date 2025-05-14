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
    #include <SFML/Graphics.h> // csfml type

    //----------------------------------------------------------------//
    /* DEFINE */

    /* csfml */
    #define TITLE "Corewar の Graphics"
    #define FONT "/usr/share/fonts/liberation-mono/LiberationMono-Regular.ttf"
    #define WIDTH 1600
    #define HEIGHT 950
    #define LINE_OCTET 96

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

    /* intern var */
    bool carry;
    reg_t registers[REG_NUMBER];
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
    array_t *process;

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
    int apartenance[MEM_SIZE]; // st, sti

    /* champions list */
    array_t *champions;

    /* live status */
    bool live_status[MAX_CHAMPIONS];
    int nbr_live;
    int total_cycle;
    int actual_cycle;
    int cycle_to_die;

    /* option */
    bool no_graphics;
    bool csfml;
    bool spe_dump;
    int dump_cycle;
    int next_prog_number;
    int next_load_address;

    /* option csfml */
    sfRenderWindow *window;
    sfFont *font;
    sfRectangleShape *champion_box[4];
    sfRectangleShape *memory_box;

    /* ouput */
    bool help;
    bool err_sys;
} main_data_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* corewar */
int corewar(int const argc, char const *argv[], char const *env[],
    main_data_t *data); // Error: KO
int setup(main_data_t *data); // Error: KO
int dump_memory(unsigned char memory[MEM_SIZE]); // Error: KO
int dump_custom(array_t *champions, unsigned char memory[MEM_SIZE],
    int apartenance[MEM_SIZE]); // Error: KO
int update_cycle(main_data_t *data); // Error: KO
int exe_memory(main_data_t *data); // Error: KO
int get_param(unsigned char value, int arg_nb); // Error: none

/* op_cmd */ // Error: KO
int op_live(main_data_t *data, champion_t *champion, process_t *process);
int op_ld(main_data_t *data, champion_t *champion, process_t *process);
int op_st(main_data_t *data, champion_t *champion, process_t *process);
int op_add(main_data_t *data, champion_t *champion, process_t *process);
int op_sub(main_data_t *data, champion_t *champion, process_t *process);
int op_and(main_data_t *data, champion_t *champion, process_t *process);
int op_or(main_data_t *data, champion_t *champion, process_t *process);
int op_xor(main_data_t *data, champion_t *champion, process_t *process);
int op_zjmp(main_data_t *data, champion_t *champion, process_t *process);
int op_ldi(main_data_t *data, champion_t *champion, process_t *process);
int op_sti(main_data_t *data, champion_t *champion, process_t *process);
int op_fork(main_data_t *data, champion_t *champion, process_t *process);
int op_lld(main_data_t *data, champion_t *champion, process_t *process);
int op_lldi(main_data_t *data, champion_t *champion, process_t *process);
int op_lfork(main_data_t *data, champion_t *champion, process_t *process);
int op_aff(main_data_t *data, champion_t *champion, process_t *process);

/* init_data */
int init_data(main_data_t *data); // Error: KO
int init_global(main_data_t *data); // Error: KO
int init_option(main_data_t *data); // Error: KO
int init_csfml(main_data_t *data, char const *env[]); // Error: KO
int init_process(champion_t *champion, int index); // Error: KO

/* option */
int render_csfml(main_data_t *data); // Error: KO
int render_memory(main_data_t *data); // Error: KO

/* init_argument */
int init_argument(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int add_champions(main_data_t *data, char const *file); // Error: KO
int flag_help(void); // Error: KO
int flag_null(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_dump(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_ddump(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_number(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_address(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_graphics(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO
int flag_csfml(main_data_t *data,
    int const argc, char const *argv[]); // Error: KO

/* exit */
int free_data(main_data_t *data); // Error: EPITECH_ERR

//----------------------------------------------------------------//
/* GLOBAL_CONST */

/* flag */
extern int const color_champions[];
extern char const *flags[];
extern char const *full_flags[];
extern int (* const flag_functions[])(main_data_t *,
    int const, char const *[]);

/* op command */
extern int (* const op_cmd[])(main_data_t *, champion_t *, process_t *);

#endif /* COREWAR_H */
