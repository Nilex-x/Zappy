/*
** EPITECH PROJECT, 2022
** client.h
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <sys/select.h>

    #define WRITE 0
    #define READ 1

typedef struct info_s
{
    int socket;
    int read_write;
    char *buff;
    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;
} info_t;

/*
** @brief Initialize client.
** 
** @param socket The client's socket.
*/
int init_info(int socket);

/*
** @brief Create a socket connected to the server.
** 
** @param ip Server ip
** @param port Server port
** @return Client's socket
*/
int create_client(char *ip, int port);

/*
** @brief Get server msg.
** 
** @param socket Client's socket
*/
char *read_server(int socket);

/*
** @brief Write to server.
** 
** @param socket client's socket
** @param send msg to send
*/
int write_server(int socket, char *send);

#endif /* !CLIENT_H_ */
