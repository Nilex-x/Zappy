/*
** EPITECH PROJECT, 2022
** server.h
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #define  _GNU_SOURCE
    #include "lib.h"
    #include "map_handler.h"
    #include "zappy.h"

    #include <string.h>
    #include <sys/select.h>

    #define NB_LISTEN 32
    #define LENGTH_COMMAND 512

typedef enum client_status {
    WRITE,
    READ,
    EXECPT
} status_e;

typedef struct data_send_s {
    char *data;
    struct data_send_s *next;
} data_send_t;

typedef struct client_s {
    int socket;
    int status;
    bool isQuit;
    data_send_t *data_send;
    buffer_t *buff_read;
    trantorians_t *trant;
    char *team_name;
    struct client_s *next;
    struct client_s *prev;
} client_t;

typedef struct server_s
{
    int port;
    int fd_server;
    int max_fd;
    fd_set wfds;
    fd_set rfds;
    fd_set efds;
    client_t *list_client;
    zappy_data_t *data;
}server_t;

typedef struct cmd_s {
    char *cmd;
    int (*fct)(client_t *client, char** args, zappy_data_t *data);
    size_t time;
} cmd_t;

int create_socket(server_t *info);
int read_client(server_t *info, client_t *client);
char *get_client_command(server_t *info, client_t *client);
void remove_client(server_t *info, int client);
int handler_connection(server_t *info);
void init_client(server_t *info);
void clear_list(server_t *info);
client_t *add_client(server_t *info, int client);
client_t *find_client(server_t *info, int client);
void free_client(client_t *client);
void accept_connect(server_t *info);
void write_client(server_t *info, int s_client);
void close_server(server_t *info);
void init_buff_client(client_t *node);
void handle_command(server_t *info, client_t *client);
void init_data(server_t *info);

data_send_t *add_send(data_send_t *data_send, char *data);
char *get_next_data_to_send(data_send_t **data_send);
size_t get_size_data_to_send(data_send_t *data_send);
void free_data_send(data_send_t *data_send);

#endif /* !SERVER_H_ */
