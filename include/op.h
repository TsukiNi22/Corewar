/*
** EPITECH PROJECT, 2025
** op.h
** File description:
** Header for the op
*/

#ifndef OP_H
    #define OP_H

    //----------------------------------------------------------------//
    /* DEFINE */

    /* sample */
    #define MEM_SIZE (6 * 1024)
    #define IDX_MOD 512 /* modulo of the index < */

    /* regs */
    #define REG_NUMBER 16 /* r1 <--> rx */

    /* ID for type */
    #define T_REG 1 /* register */
    #define T_DIR 2 /* direct  (ld  #1,r1  put 1 into r1) */
    #define T_IND 4 /* indirect always relative */
    #define T_LAB 8 /* LABEL */

    /* global info */
    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3

    /* live */
    #define CYCLE_TO_DIE 1536 /* number of cycle before beig declared dead */
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40

//----------------------------------------------------------------//
/* TYPEDEF */

typedef char args_type_t;

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
} op_t;

typedef struct header_s {
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
} header_t;

//----------------------------------------------------------------//
/* EXTERN */

extern op_t op_tab[];

#endif /* OP_H */
