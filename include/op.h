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

    /* regs */
    #define REG_NUMBER 16 /* r1 <--> rx */

    /* size (in bytes) */
    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE DIR_SIZE

    /* ID for type */
    #define T_REG 1 /* register */
    #define T_DIR 2 /* direct  (ld  #1,r1  put 1 into r1) */
    #define T_IND 4 /* indirect always relative */
    #define T_LAB 8 /* LABEL */

    /* global info */
    #define MEM_SIZE (6 * 1024)
    #define IDX_MOD 512 /* modulo of the index < */
    #define MAX_ARGS_NUMBER 4
    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3

    /* live */
    #define CYCLE_TO_DIE 1536 /* number of cycle before declared dead */
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40

//----------------------------------------------------------------//
/* TYPEDEF */

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    char type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
} op_t;

//----------------------------------------------------------------//
/* EXTERN */

extern const op_t op_tab[];

#endif /* OP_H */
