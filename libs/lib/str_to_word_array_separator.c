/*
** EPITECH PROJECT, 2022
** str_to_word_array_separator.c
** File description:
** str_to_word_array_separator
*/

#include "lib.h"
#include <stdlib.h>
#include <string.h>

char *my_strncpy_n(char *dest, char *str, int index, int n);

int count_arg_separator(char *str, char separator)
{
    int count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == separator)
            count++;
    }
    return (count);
}

int count_word_length_separator(char *str, int index, char separator)
{
    int size = 0;

    while (str[index] && str[index] != separator) {
        size++;
        index++;
    }
    return (size);
}

char **str_to_word_array_separator(char *str, char separator)
{
    int word_length = 0;
    int i = 0;
    int j = 0;
    char **array = NULL;

    if (!str)
        return (NULL);
    array = malloc(sizeof(char *) * (count_arg_separator(str, separator) + 2));
    if (!array)
        return (NULL);
    for (; i < (int) strlen(str); i = i + word_length + 1, j++) {
        word_length = count_word_length_separator(str, i, separator);
        array[j] = malloc(sizeof(char) * (word_length + 1));
        array[j] = my_strncpy_n(array[j], str, i, word_length);
    }
    array[j - 1][strlen(array[j - 1])] = '\0';
    array[j] = NULL;
    return (array);
}
