/*
** game.h for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Wed Jun 21 23:08:45 2017 Aurelien
** Last update Wed Jun 21 21:09:14 2017 Aurelien
*/
#ifndef GAME_H
# define GAME_H

typedef struct s_ressources
{
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int food;
} t_ressources;

typedef struct s_tile
{
    t_ressources ress;
    // perso ref?
} t_tile;

typedef struct s_perso
{
    // info
    // name or id ??
    int team;
    int lvl;
    int x;
    int y;
    t_ressources ress;
    int time_left;
} t_perso;

typedef struct s_game
{
    t_tile **map; // map[x][y] to get the tile
    t_perso **perso;
    int width; // x
    int height; // y
    // time gest ?
} t_game;

/*
** do the cmd and/or executge 1 cycle of time only if 1 time unit has elapsed
*/
int do_game(t_game *game, char *cmd);

/*
** malloc & init the t_game struct
** return NULL on error
*/
t_game *init_game(int width, int height, int clientsNb);
void init_tile_tab(t_game *game, int i);
t_ressources init_ress(); // maybe generate ressources here ?

#endif
