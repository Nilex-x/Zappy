/*
** EPITECH PROJECT, 2022
** zappy.h
** File description:
** zappy
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_
    #include "map_handler.h"

    #define bool unsigned int
    #define true 1
    #define false 0

typedef struct map_s map_t;

typedef enum directions {
    NORTH,
    EAST,
    SOUTH,
    WEST
} direction_t;

typedef struct trantorians_s {
    bool is_alive;
    unsigned int life_left;
    int *inventory;
    direction_t direction;
    struct tile_s *tile;
    struct trantorians_s *next;
} trantorians_t;

typedef struct team_s {
    char *name;
    int player_max;
    int nb_player;
    struct team_s *next;
} team_t;

typedef struct zappy_data_s {
    int width;
    int height;
    int freq;
    int max_teams_player;
    team_t *teams;
    map_t *map;
} zappy_data_t;

typedef struct server_s server_t;

/**
 * @brief Get the list of team's name
 *
 * @param info Server's data struct
 * @param argc Number of argument
 * @param name_list List of team's name
 * @param index index to start
 * @return int
 */
int get_name_team(server_t *info, char **name_list, int index);

/**
 * @brief Manage flags of prog
 *
 * @param info Server data struct
 * @param argc Number of argument
 * @param argv List of argument
 * @return int
 */
int handle_flags(server_t *info, int argc, char **argv);

/**
 * @brief Create a team struct
 *
 * @param name Name of new team
 * @param data Data server struct
 * @return team_t*
 */
team_t *create_team(char *name, zappy_data_t *data);

/**
 * @brief Free teams list
 *
 * @param teams Teams list to free
 */
void free_teams(team_t *teams);

#endif /* !ZAPPY_H_ */
