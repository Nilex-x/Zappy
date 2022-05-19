/*
** EPITECH PROJECT, 2022
** manage_buffer.c
** File description:
** manage_buffer
*/

#include "lib.h"

void init_buffer(buffer_t *buff, int length_command)
{
    for (int i = 0; i < length_command; i++)
        buff->buffer[i] = '\0';
    buff->rdonly = buff->buffer;
    buff->wronly = buff->buffer;
}

int find_end_of_line(buffer_t *buff, char end_of_line, int length_max)
{
    int count = 0;
    char *temp = buff->rdonly;

    for (; temp[0] != '\0'; temp++) {
        if ((temp - buff->buffer) == length_max)
            temp = buff->buffer;
        if (temp[0] == end_of_line)
            return (count);
        count++;
    }
    return (-1);
}

char *read_to_buffer(buffer_t *buff, char end_of_line, int length_max)
{
    int len = find_end_of_line(buff, '\n', length_max);
    char *value = NULL;
    int i = 0;

    if (len == -1)
        return NULL;
    value = malloc(sizeof(char) * (len + 2));
    if (!value)
        return (NULL);
    for (; buff->rdonly[0] != end_of_line && i < length_max; i++) {
        if ((buff->rdonly - buff->buffer) == length_max)
            buff->rdonly = buff->buffer;
        value[i] = buff->rdonly[0];
        buff->rdonly[0] = '\0';
        value[i + 1] = '\n';
        buff->rdonly++,
    }
    value[i + 1] = '\0';
    buff->rdonly++;
    return (value);
}

void add_to_write(buffer_t *buff, char *value, int length_max)
{
    if (!value)
        return;
    for (int i = 0; value[i]; i++, buff->wronly++) {
        if ((buff->wronly - buff->buffer) == length_max)
            buff->wronly = buff->buffer;
        buff->wronly[0] = value[i];
    }
}
