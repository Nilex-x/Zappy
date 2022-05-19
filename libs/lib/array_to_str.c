/*
** EPITECH PROJECT, 2022
** array_to_str.c
** File description:
** array_to_str
*/

#include "lib.h"

int get_size_array(char **array)
{
    int len = 0;

    for (int i = 0; array[i]; i++)
        len += strlen(array[i]);
    return (len);
}

char *array_to_str(char **array)
{
    int index = 0;
    char *str = NULL;

    if (array == NULL)
        return (NULL);
    str = malloc(sizeof(char) * (get_size_array(array) + 1));
    if (!str)
        return (NULL);
    for (int i = 0; array[i]; i++) {
        for (int y = 0; array[i][y]; y++, index++) {
            str[index] = array[i][y];
        }
    }
    str[index] = '\0';
    return (str);
}

char *array_to_str_separator(char **array, char separator)
{
    int index = 0;
    char *str = NULL;

    if (array == NULL)
        return (NULL);
    str = malloc(sizeof(char) * (get_size_array(array) + \
                                strlen_array(array) + 1));
    if (!str)
        return (NULL);
    for (int i = 0; array[i]; i++, index++) {
        for (int y = 0; array[i][y]; y++, index++)
            str[index] = array[i][y];
        if (array[i + 1])
            str[index] = separator;
        else
            str[index] = '\0';
    }
    free_array(array);
    return (str);
}
