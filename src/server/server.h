#ifndef _SERVER_H_
#define _SERVER_H_ 
#include "zappy.h"
# define ALL_CLIENT -1
# define GRAPHIC -2
# define CLIENT_STATE_CONNECTED 1
# define CLIENT_STATE_TEAM_SELECTED 2

typedef struct s_position
{
  int			x;
  int			y;
}			t_position;

typedef struct s_configuration
{
    int				port;
    int				world_height;
    int				world_width;
    int				client_per_team;
    double			temporal_delay;
    int				seed;
    char*           team1_name;
    char*           team2_name;
}				t_configuration;

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
    // player ref?
} t_tile;


typedef struct s_player
{
    // info
    // name or id ??
    int id;
    int team_id;
    int lvl;
    int x;
    int y;
    //t_position position;
    // direction
    t_ressources ress;
    int time_left;
    int act_time_left; // temp restant de l'action
    char *action;
} t_player;

/*
** chained list for player
*/
typedef struct s_plist
{
    t_player player;
    struct s_plist *next;
} t_plist;

/*
** liste chainée pr les reponse client
*/
typedef struct s_rlist
{
    int id;
    char *msg;
    struct s_rlist *next;
} t_rlist;

typedef struct s_client
{
	int fd;
	struct sockaddr_in in;
    int team_id;
    int state;
    t_player *player;
}						t_client;

typedef struct s_game
{
    t_tile **map; // map[x][y] to get the tile
    t_plist *player_list;
    int width; // x
    int height; // y
    int freq;
    t_rlist *resp; // response : to be checked after do_game
} t_game;

typedef struct s_server
{
	int fd;
	struct sockaddr_in in;
    int sock;
    fd_set master;
    int max_clients;
    t_client *clients;
    t_configuration *configuration;
    t_game *game;
}						t_server;

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
int handle_cmd(t_server *server, t_client *client, char *cmd);

/*
** execute the action casted & generate a resp & graph evnt
*/
int do_cmd(t_game *game, t_player *player);

/*
** malloc & init the t_game struct
** return NULL on error
*/
t_game *init_game(t_configuration *configuration);
void init_tile_tab(t_game *game, int i);
t_ressources init_ress(); // maybe generate ressources here ?
void handle_select_team(char *team_name, t_client *client, t_server *server);
void handle_client_message(char *message, t_client *client, t_server *server);
void handle_new_client(t_server *server, int *max);
t_configuration *parse_args(int argc, char *argv[]);
char *get_client_addr(struct sockaddr_in client);
int get_client_port(struct sockaddr_in client);
t_server *create_server(t_configuration *config);
void handle_client(t_client *client);
void start_server(t_server *server);
t_server *get_server_socket(int port);
t_client *accept_client(t_server *server);
t_client *alloc_new_client(int socket, struct sockaddr_in in, t_server *server);
t_configuration *parse_args(int argc, char *argv[]);

int forward_cmd(t_game *game, t_player *perso);
int right_cmd(t_game *game, t_player *perso);
int left_cmd(t_game *game, t_player *perso);
int look_cmd(t_game *game, t_player *perso);
int inventory_cmd(t_game *game, t_player *perso);
int connect_nbr_cmd(t_game *game, t_player *perso); // ??
int fork_cmd(t_game *game, t_player *perso);
int eject_cmd(t_game *game, t_player *perso);
int take_cmd(t_game *game, t_player *perso);
int set_cmd(t_game *game, t_player *perso);
int incant_cmd(t_game *game, t_player *perso);

#endif