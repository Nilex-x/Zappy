/*
** EPITECH PROJECT, 2022
** strcatdup.c
** File description:
** str_cat_dup
*/

#include <stdlib.h>
#include <string.h>

char *strcatdup(char *src, char *to_add, char *between)
{
    char *new_str = NULL;

    new_str = malloc(sizeof(char) * (strlen(src) + strlen(between) + \
                    strlen(to_add) + 1));
    strcpy(new_str, src);
    if (between)
        strcat(new_str, between);
    strcat(new_str, to_add);
    return (new_str);
}
