/*
** EPITECH PROJECT, 2022
** zappy.h
** File description:
** zappy
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #define bool unsigned int
    #define true 1
    #define false 0

typedef struct map_s map_t;
typedef struct client_s client_t;

typedef enum directions {
    NORTH,
    EAST,
    SOUTH,
    WEST
} direction_t;

typedef struct trantorians_s {
    int lvl;
    bool is_alive;
    int inventory[8];
    direction_t direction;
    unsigned int life_left;
    client_t *client;
    struct tile_s *tile;
    struct trantorians_s *next;
} trantorians_t;

typedef struct trantorians_list_s {
    trantorians_t *trant;
    struct trantorians_list_s *next;
} trantorians_list_t;

typedef struct team_s {
    char *name;
    int player_max;
    int nb_player;
    trantorians_list_t *list;
    struct team_s *next;
} team_t;

typedef struct zappy_data_s {
    int width;
    int height;
    int freq;
    int max_teams_player;
    team_t *teams;
    trantorians_t *trants;
    map_t *map;
} zappy_data_t;

typedef struct server_s server_t;

/*
** @brief Get the list of team's name
**
** @param info Server's data struct
** @param argc Number of argument
** @param name_list List of team's name
** @param index index to start
** @return int
*/
int get_name_team(server_t *info, char **name_list, int index);

/*
** @brief Manage flags of prog
**
** @param info Server data struct
** @param argc Number of argument
** @param argv List of argument
** @return int
*/
int handle_flags(server_t *info, int argc, char **argv);

/*
** @brief sort commands
**
** @param client Client who do command
** @param data Data struct
** @param cmd Commands
** @return int
*/
int sort_command(client_t *client, zappy_data_t *data, char *cmd);

/*
** @brief Create a add trantoriant struct
**
** @param cli Client who do command
** @param data Data server struct
** @return trantorians_t*
*/
trantorians_t *create_add_trantoriant(client_t *cli, zappy_data_t *data);

/*
** @brief Get the team by name string
**
** @param name name string
** @param data Data server struct
** @return team_t*
*/
team_t *get_team_by_name(char *name, zappy_data_t *data);

/*
** @brief Add trantorians in team
**
** @param trant Trantorians to add
** @param team Team added trantorians
** @return team_t*
*/
team_t *add_trantoriant_to_team(trantorians_t *trant, team_t *team);

/*
** @brief Create a team struct
**
** @param name Name of new team
** @param data Data server struct
** @return team_t*
*/
team_t *create_team(char *name, zappy_data_t *data);

/*
** @brief Free teams list
**
** @param teams Teams list to free
*/
void free_teams(team_t *teams);

/*
** @brief Moves the trantorian in the direction he is looking.
** 
** @param trant The trantorian who's moving.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if movement was done, 1 if cancelled.
*/
int forward(trantorians_t *trant, char **arg, zappy_data_t *data);

/*
** @brief Turns the trantorian left.
** 
** @param trant The trantorian who's moving.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if movement was done, 1 if cancelled.
*/
int left(trantorians_t *trant, char **arg, zappy_data_t *data);

/*
** @brief Turns the trantorian right.
** 
** @param trant The trantorian who's moving.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if movement was done, 1 if cancelled.
*/
int right(trantorians_t *trant, char **arg, zappy_data_t *data);

/*
** @brief Gets information 
** 
** @param trant The trantorian who's moving.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if movement was done, 1 if cancelled.
*/
int look(trantorians_t *trant, char **arg, zappy_data_t *data);

/*
** @brief send map size to the gui
** 
** @param client the gui
** @param args
** @param data 
** @return int 
*/
int gui_map_size(client_t *client, char **args, zappy_data_t *data);

/*
** @brief send tile content to the gui
** 
** @param client the gui
** @param args wanted tile
** @param data 
** @return int 
*/
int gui_tile_content(client_t *client, char **args, zappy_data_t *data);

/*
** @brief send information of each tile of the map to the gui
** 
** @param client the gui
** @param args 
** @param data 
** @return int 
*/
int gui_map_content(client_t *client, char **args, zappy_data_t *data);

/*
** @brief send the different teams names to the gui
** 
** @param client the gui
** @param args 
** @param data 
** @return int 
*/
int gui_teams_name(client_t *client, char **args, zappy_data_t *data);

#endif /* !ZAPPY_H_ */
