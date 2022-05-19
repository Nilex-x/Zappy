/*
** EPITECH PROJECT, 2022
** remove_to_last_char.c
** File description:
** remove_to_last_char
*/

#include "lib.h"

char *remove_to_last_char(char *str, char to_find)
{
    char *result = NULL;
    int len = strlen(str) - 1;

    for (int i = len; i >= 0; i--) {
        if (str[i] == to_find) {
            str[i] = '\0';
            result = strdup(str);
            break;
        } else {
            str[i] = '\0';
        }
    }
    return (result);
}
