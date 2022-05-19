/*
** EPITECH PROJECT, 2022
** remove_part_of_array.c
** File description:
** remove_part_of_array
*/

#include "lib.h"

char **remove_part_of_array(char **array, int last_index)
{
    char **new_array = NULL;
    int len = 0;

    if (!array)
        return NULL;
    len = strlen_array(array);
    new_array = malloc(sizeof(char *) * (last_index + 1));
    if (!new_array)
        return NULL;
    for (int i = 0; i < len; i++) {
        if (i < last_index)
            new_array[i] = strdup(array[i]);
    }
    new_array[last_index] = NULL;
    free_array(array);
    return new_array;
}
