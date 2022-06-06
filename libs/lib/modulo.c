/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** modulo
*/

#include "lib.h"

int modulo(int a, int b)
{
    if ((a % b) < 0)
        return (a % b + b);
    return (a % b);
}
