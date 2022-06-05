/*
** EPITECH PROJECT, 2022
** manage_init.c
** File description:
** manage_init
*/

#include "server.h"

void init_buff_client(client_t *node)
{
    node->buff_read = malloc(sizeof(buffer_t));
    if (!node->buff_read)
        return;
    init_buffer(node->buff_read, LENGTH_COMMAND);
}

void handle_command(server_t *info, client_t *cli)
{
    char *value = NULL;
    value = read_to_buffer(cli->buff_read, '\n', LENGTH_COMMAND);
    if (!value || value[0] == '\n') {
        free(value);
        return;
    }
    printf("value client [%s]\n", value);
    free(value);
}
