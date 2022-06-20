/*
** EPITECH PROJECT, 2022
** zappy.h
** File description:
** zappy
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #include <unistd.h>
    #include <sys/time.h>

    #define bool unsigned int
    #define true 1
    #define false 0

typedef struct map_s map_t;
typedef struct client_s client_t;

typedef enum direction_s {
    NORTH,
    EAST,
    SOUTH,
    WEST
} direction_t;

typedef struct egg_s {
    int number;
    char *team_name;
    int time_until_hatch;
    struct tile_s *tile;
    struct egg_s *next;
} egg_t;

typedef struct trantorians_s {
    int lvl;
    bool is_alive;
    int inventory[8];
    char *team_name;
    direction_t direction;
    client_t *client;
    struct timespec timeleft;
    struct action_s *action;
    struct tile_s *tile;
    struct team_s *team;
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
    egg_t *eggs;
    map_t *map;
} zappy_data_t;

typedef struct action_s {
    int (*action)(client_t *cli, char **arg, zappy_data_t *data);
    struct timespec time_left;
    char **args;
    struct action_s *next;
} action_t;

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
trantorians_t *create_add_trantoriant(client_t *cli, zappy_data_t *data, char *team_name);

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

void remove_trantoriant(zappy_data_t *data, trantorians_t *torm);

void move_trantorian(map_t *map, trantorians_t *trant);

/*
** @brief Moves the trantorian in the direction he is looking.
**
** @param trant The trantorian who's moving.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if movement was done, 1 if cancelled.
*/
int forward(client_t *client, char **arg, zappy_data_t *data);

/*
** @brief Turns the trantorian left.
**
** @param trant The trantorian who's moving.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if movement was done, 1 if cancelled.
*/
int left(client_t *client, char **arg, zappy_data_t *data);

/*
** @brief Turns the trantorian right.
**
** @param trant The trantorian who's moving.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if movement was done, 1 if cancelled.
*/
int right(client_t *client, char **arg, zappy_data_t *data);

/*
** @brief Gets information
**
** @param trant The trantorian who's moving.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if movement was done, 1 if cancelled.
*/
int look(client_t *client, char **arg, zappy_data_t *data);

/*
** @brief Ejects all trantorians on his tile.
**
** @param trant The trantorian ejecting.
** @param arg NULL here.
** @param data Zappy's data structure.
** @return 0 if someone was ejected, 1 if no one.
*/
int eject(client_t *client, char **arg, zappy_data_t *data);

/*
** @brief Sends to the GUI the position of the player args[1]
**
** @param cli The client asking for the position.
** @param args The arguments of the function, here the player number.
** @param data Zappy's data structure.
** @return 0 if everything is okay, 1 if the player number is wrong.
*/
int gui_player_pos(client_t *cli, char **args, zappy_data_t *data);

/*
** @brief Sends to the GUI the level of the player args[1]
**
** @param cli The client asking for the level.
** @param args The arguments of the function, here the player number.
** @param data Zappy's data structure.
** @return 0 if everything is okay, 1 if the player number is wrong.
*/
int gui_player_lvl(client_t *cli, char **args, zappy_data_t *data);

/*
** @brief Sends to the GUI the inventory of the player args[1]
**
** @param cli The client asking for the inventory.
** @param args The arguments of the function, here the player number.
** @param data Zappy's data structure.
** @return 0 if everything is okay, 1 if the player number is wrong.
*/
int gui_player_inventory(client_t *cli, char **args, zappy_data_t *data);

/*
** @brief Sends to the GUI the time frequency of the game.
**
** @param cli The client asking for the frequency.
** @param args NULL here.
** @param data Zappy's data structure.
** @return 0 if everything is okay, 1 if not.
*/
int gui_time_unit_request(client_t *cli, char **args, zappy_data_t *data);

/*
** @brief Changing the time frequency of the game.
**
** @param cli The client asking for the change.
** @param args The arguments of the function, here the new frequency.
** @param data Zappy's data structure.
** @return 0 if everything is okay, 1 if the frequency is not good.
*/
int gui_time_unit_modif(client_t *cli, char **args, zappy_data_t *data);

/*
** @brief Pick an item from the tile.
**
** @param trant The trantorian
** @param args The picked item
** @param data
** @return int
*/
int pick_item(client_t *client, char **args, zappy_data_t *data);

/*
** @brief Puts an item on the ground.
**
** @param trant The trantorian
** @param args The dropped item
** @param data
** @return int
*/
int drop_item(client_t *client, char **args, zappy_data_t *data);

/*
** @brief sends a msg from a trantorian to all the trantorians with the direction it's comming from.
**
** @param trant the trantorian sending the msg
** @param args msg to send
** @param data
** @return int
*/
int broadcast(client_t *client, char **args, zappy_data_t *data);

int display_inventory(client_t *client, char **args, zappy_data_t *data);

int fork_command(client_t *client, char **args, zappy_data_t *data);

int team_unused_slot(client_t *client, char **args, zappy_data_t *data);

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

int gui_player_pos(client_t *cli, char **args, zappy_data_t *data);

int gui_player_lvl(client_t *cli, char **args, zappy_data_t *data);

int gui_player_inventory(client_t *cli, char **args, zappy_data_t *data);

int gui_time_unit_request(client_t *cli, char **args, zappy_data_t *data);

int gui_time_unit_modif(client_t *cli, char **args, zappy_data_t *data);

int incantation(client_t *cli, char **arg, zappy_data_t *data);

void new_player_connect(trantorians_t *t);

void gui_connect_new_player(client_t *gui, zappy_data_t *data);

void expulsion_message(trantorians_t *t);

void broadcast_message(trantorians_t *t, char **args);

void ressource_dropping(trantorians_t *t, int obj);

void ressource_collecting(trantorians_t *t, int obj);

void death_of_a_player(trantorians_t *t);

void end_of_game(team_t *team, zappy_data_t *data);

void message_from_server(client_t *cli, char *str);

void unknown_gui_command(client_t *cli);

void command_parameter(client_t *cli);

void start_of_incantation(tile_t *tile, int level);

void end_of_incantation(tile_t *tile, int level);

void egg_laying(trantorians_t *trant);

void egg_layed(trantorians_t *t, egg_t *egg);

void egg_hatching(egg_t *egg, tile_t *tile);

void player_connexion_for_egg(trantorians_t *t, egg_t *egg);

void death_hatched_egg(egg_t *egg, zappy_data_t *data);


#endif /* !ZAPPY_H_ */
