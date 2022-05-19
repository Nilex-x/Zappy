/*
** EPITECH PROJECT, 2022
** free_array.c
** File description:
** free_array
*/

#include <stdlib.h>

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
    return;
}
