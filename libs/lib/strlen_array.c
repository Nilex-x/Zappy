/*
** EPITECH PROJECT, 2022
** strlen_array.c
** File description:
** strlen_array
*/

#include <string.h>

int strlen_array(char **array)
{
    int count = 0;

    for (int i = 0; array[i]; i++)
        count += (int) strlen(array[i]);
    return (count);
}

int len_array(char **array)
{
    int count = 0;

    while (array[count])
        count++;
    return (count);
}
