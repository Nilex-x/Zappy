/*
** EPITECH PROJECT, 2022
** clear_str.c
** File description:
** clear_str
*/

#include <stdlib.h>
#include <stdio.h>

char *clear_str(char *str)
{
    if (!str)
        return NULL;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\"')
            str[i] = ' ';
        if (str[i] == '\n' || str[i] == '\t')
            str[i] = '\0';
    }
    return (str);
}
