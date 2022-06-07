/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** manage_data_send
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

data_send_t *add_send(data_send_t *data_send, char *data)
{
    data_send_t *new = NULL;
    data_send_t *curr = data_send;

    if (!data)
        return curr;
    new = malloc(sizeof(data_send_t));
    if (!new)
        return curr;
    new->data = strdup(data);
    new->next = NULL;
    if (!data_send)
        return new;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
    return data_send;
}

char *get_next_data_to_send(data_send_t **data_send)
{
    char *data = NULL;
    data_send_t *curr = *data_send;

    if (!*data_send)
        return NULL;
    data = (*data_send)->data;
    *data_send = (*data_send)->next;
    free(curr);
    return data;
}

size_t get_size_data_to_send(data_send_t *data_send)
{
    size_t size = 0;

    while (data_send) {
        size++;
        data_send = data_send->next;
    }
    return size;
}
