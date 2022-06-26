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
    #include <sys/time.h>

    #define NB_LISTEN 32
    #define LENGTH_COMMAND 1024

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
    bool is_quit;
    bool is_gui;
    data_send_t *data_send;
    buffer_t *buff_read;
    trantorians_t *trant;
    egg_t *egg;
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
    struct timespec time_ref;
    struct timespec time_left;
    client_t *list_client;
    zappy_data_t *data;
}server_t;

struct data_incant {
    int ressources_required[6];
    int trant_nb_required;
};

typedef struct cmd_s {
    char *cmd;
    int (*fct)(client_t *client, char **args, zappy_data_t *data);
    char **args;
    size_t time;
    bool gui;
} cmd_t;

/*
** @brief Create a socket of server
**
** @param info Info server struct
** @return int
*/
int create_socket(server_t *info);

/*
** @brief Read client in socket
**
** @param info Info server struct
** @param client Client who need read socket
** @return int
*/
int read_client(server_t *info, client_t *client);

/*
** @brief Get the client command string
**
** @param info Info server struct
** @param client Client who do command
** @return char *
*/
char *get_client_command(server_t *info, client_t *client);

/*
** @brief Remove client in list and close socket
**
** @param info Info server struct
** @param client Client to remove and close
*/
void remove_client(server_t *info, int client);

/*
** @brief Manage connection client
**
** @param info Info server struct
*/
void handler_connection(server_t *info);

/*
** @brief Initialize client in loist
**
** @param info Info server struct
*/
void init_client(server_t *info);

/*
** @brief Clear list of select
**
** @param info Info server struct
*/
void clear_list(server_t *info);

/*
** @brief Add client to list
**
** @param info Info server struct
** @param client Client socket
** @return client_t *
*/
client_t *add_client(server_t *info, int client);

/*
** @brief Find client by socket
**
** @param info Info server struct
** @param client Client socket to find
** @return client_t *
*/
client_t *find_client(server_t *info, int client);

/*
** @brief Free client
**
** @param client
*/
void accept_connect(server_t *info);

/*
** @brief Accept connection client
**
** @param info Info server struct
** @param s_client Client socket to request connection
*/
void write_client(server_t *info, int s_client);

/*
** @brief Close server and free all data
**
** @param info Info server struct
*/
void close_server(server_t *info);

/*
** @brief Initialize buffer circular of client
**
** @param node Client to initialize buffer
*/
void init_buff_client(client_t *node);

/*
** @brief Handler command of client
**
** @param info Info server struct
** @param client Client does the command
*/
void handle_command(server_t *info, client_t *client);

/*
** @brief Add message to send to client
**
** @param data_send Data_send struct
** @param data Message for client
** @return data_send_t *
*/
data_send_t *add_send(data_send_t *data_send, char *data);

/*
** @brief Get the next data to send string
**
** @param data_send Data_send struct
** @return char *
*/
char *get_next_data_to_send(data_send_t **data_send);

/*
** @brief Get the length data to send struct
**
** @param data_send Data_send struct
** @return size_t
*/
size_t get_size_data_to_send(data_send_t *data_send);

/*
** @brief Free data_send struct
**
** @param data_send Data_send to free
*/
void free_data_send(data_send_t *data_send);

/*
** @brief Initializa data struct
**
** @param info Info server struct
*/
void init_data_struct(server_t *info);

/*
** @brief Set the timespec value
**
** @param time Time to set
** @param freq Frequency
** @return struct timespec
*/
struct timespec set_timespec(long long int time, long long int freq);

/*
** @brief Substrate two timespec
**
** @param ts1 Timespec 1
** @param ts2 Timespec 2
** @return struct timespec
*/
struct timespec sub_timespec(struct timespec ts1, struct timespec ts2);

/*
** @brief Substracte all action
**
** @param info Info server struct
*/
void select_interupt(server_t *info);

/*
** @brief Get the shortest time of action
**
** @param info Info server struct
*/
void get_shortest_time(server_t *info);


#endif /* !SERVER_H_ */
