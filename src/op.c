/*
** EPITECH PROJECT, 2025
** op.c
** File description:
** You know, I don t think there are good or bad descriptions,
** for me, life is all about functions...
*/

#include "op.h"

const op_t op_tab[] = {
    {1, {T_DIR}, 10},
    {2, {T_DIR | T_IND, T_REG}, 5},
    {2, {T_REG, T_IND | T_REG}, 5},
    {3, {T_REG, T_REG, T_REG}, 10},
    {3, {T_REG, T_REG, T_REG}, 10},
    {3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6},
    {3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6},
    {3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6},
    {1, {T_DIR}, 20},
    {3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25},
    {3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25},
    {1, {T_DIR}, 800},
    {2, {T_DIR | T_IND, T_REG}, 10},
    {3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50},
    {1, {T_DIR}, 1000},
    {1, {T_REG}, 2},
    {0}
};
