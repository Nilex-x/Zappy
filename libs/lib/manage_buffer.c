/*
** EPITECH PROJECT, 2022
** manage_buffer.c
** File description:
** manage_buffer
*/

#include "lib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

    if ((temp - buff->buffer) + 1 >= length_max)
        temp = buff->buffer;
    while (temp[0] != '\0') {
        if (temp[0] == end_of_line)
            return (count);
        count++;
        if (((temp - buff->buffer) + 1) >= length_max)
            temp = buff->buffer;
        else
            temp++;
    }
    return (0);
}

char *read_to_buffer(buffer_t *buff, char end_of_line, int length_max)
{
    int len = find_end_of_line(buff, '\n', length_max);
    char *value = NULL;
    int i = 0;

    value = malloc(sizeof(char) * (len + 2));
    if (len == 0 || !value)
        return NULL;
    if ((buff->rdonly - buff->buffer) + 1 >= length_max) {
        fprintf(stderr, "ZEBI\n");
        buff->rdonly = buff->buffer;
    }
    for (; buff->rdonly[0] != end_of_line && i <= length_max; i++) {
        value[i] = buff->rdonly[0];
        value[i + 1] = '\0';
        buff->rdonly[0] = '\0';
        if (((buff->rdonly - buff->buffer) + 1) >= length_max)
            buff->rdonly = buff->buffer;
        else
            buff->rdonly++;
    }
    buff->rdonly++;
    return (value);
}

void add_to_write(buffer_t *buff, char *value, int length_max)
{
    if (!value)
        return;
    if ((buff->wronly - buff->buffer) + 1 >= length_max)
        buff->wronly = buff->buffer;
    for (int i = 0; value[i]; i++) {
        buff->wronly[0] = value[i];
        if ((buff->wronly - buff->buffer) + 1 >= length_max)
            buff->wronly = buff->buffer;
        else
            buff->wronly++;
    }
}
