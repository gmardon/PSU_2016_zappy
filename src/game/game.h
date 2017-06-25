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



typedef struct s_game
{
    t_tile **map; // map[x][y] to get the tile
    t_plist *player_list;
    int width; // x
    int height; // y
    int freq;
    t_rlist *resp; // response : to be checked after do_game
} t_game;
// void add_event(t_game *game, char *evnt); // add at the back
// char *pop_event(t_game *game); // retrun & del the first evnt (the oldest)

int new_player(t_game *game, char *team_name, int id);
int del_player(t_game *game, int player_id);

int add_resp(t_game *game, char *resp, int player_id); // add at the back
int del_resp(t_game *game, t_rlist *node);

int do_one_cycle(t_game *game);
int calc_elapsed(double unit);

t_player *get_player(t_game *game, int id); // ret player by id srch
t_plist *get_player_node(t_game *game, int id);

// ALL CMD
// NEED fct_table of all cmd
typedef int (*cmd_fct)(t_game *game, t_player *player);

typedef struct s_cmd
{
    char *str;
    cmd_fct fct;
    int cycle;
} t_cmd;

/*
** do the cmd and/or executge 1 cycle of time only if 1 time unit has elapsed
*/
int do_game(t_game *game, char *cmd, int id);

/*
** set cycle for the next action, ret > 0 if not found/error
*/
int cast_cmd(t_game *game, char *cmd, int id);

/*
** execute the action casted & generate a resp & graph evnt
*/
int do_cmd(t_game *game, t_player *player);

/*
** malloc & init the t_game struct
** return NULL on error
*/
t_game *init_game(int width, int height, int clientsNb);
void init_tile_tab(t_game *game, int i);
t_ressources init_ress(); // maybe generate ressources here ?

#endif
