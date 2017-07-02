#ifndef _SERVER_H_
#define _SERVER_H_ 
#include "zappy.h"
# define ALL_CLIENT -1
# define GRAPHIC -2
# define CLIENT_STATE_CONNECTED 1
# define CLIENT_STATE_TEAM_SELECTED 2
# define MAX_CLI 1023
# define MAX_RESS_TILE 5

typedef struct s_position
{
  int			x;
  int			y;
}			t_position;

typedef struct s_direction
{
  int			x;
  int			y;
}			t_direction;

typedef struct s_configuration
{
    int				port;
    int				world_height;
    int				world_width;
    int				client_per_team;
    double			frequency;
    int				seed;
    char**          teams;
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

/*
** liste chainée pr les actions du player
*/
typedef struct s_alist
{
    char *str;
    struct s_alist *next;
} t_alist;

typedef struct s_player
{
    // info
    // name or id ??
    int id;
    int team_id;
    int lvl;
    t_position pos;
    t_direction dir;
    t_ressources ress;
    int time_left;
    int act_time_left; // temp restant de l'action
    char *action;
    t_alist *action_list;
} t_player;

/*
** liste chainée pr les reponse client
*/
typedef struct s_rlist
{
    int id;
    char *msg;
    struct s_rlist *next;
} t_rlist;

/*
** chained list for client
*/

typedef struct s_client
{
	int fd;
	struct sockaddr_in in;
    int team_id;
    int state;
    t_player *player;
}						t_client;

typedef struct s_clist
{
    t_client *client;
    /* struct s_plist *next; */
  struct s_clist *next;
} t_clist;

typedef struct s_game
{
    t_tile **map; // map[x][y] to get the tile
    //t_clist *c_list;
    int width; // x
    int height; // y
    int freq;
    t_rlist *resp; // response : to be checked after do_cmd/handle_cmd/do_one_cycle
} t_game;

typedef struct s_server
{
	int fd;
	struct sockaddr_in in;
    // int sock;
    int max_id;
    fd_set master;
    int max_clients;
  //  t_client *clients;
    t_clist *client_list;
    t_configuration *configuration;
    t_game *game;
}						t_server;
t_player *new_player(t_server *serv, int id, int team_id);
void del_player(t_player *player);

int add_resp(t_game *game, char *resp, int player_id); // add at the back
int del_resp(t_game *game, t_rlist *node);
int send_all_resp(t_server* serv);

int add_action(t_player *plr, char *cmd);
char *pop_action(t_player *plr);

int set_next_action(t_server *serv, t_client *cl);
int do_one_cycle(t_server *serv);
int calc_elapsed(double unit);

//t_player *get_player(t_game *game, int id); // ret player by id srch
//t_plist *get_player_node(t_game *game, int id);

typedef int (*cmd_fct)(t_server *serv, t_client *cl);
typedef int (*cmd_chk_fct)(t_server *serv, t_player *plr, char *cmd);

typedef struct s_cmd
{
    char *str;
    cmd_fct fct;
    cmd_chk_fct check;
    int cycle;
} t_cmd;

typedef struct s_incant_req
{
    int lvl;
    int nb_plr;
    t_ressources ress;
} t_incant_req;

/*
** set cycle for the next action, ret > 0 if not found/error
*/
int handle_cmd(t_server *server, t_client *client, char *cmd);

/*
** execute the action casted & generate a resp & graph evnt
*/
int do_cmd(t_server *serv, t_client *cl);

void close_client(t_client *client, t_server *server);
t_direction give_rand_dir();
t_game *init_game(t_configuration *configuration);
int add_client(t_server *server, t_client *client);
int del_client(t_server *server, int fd);
int free_client(t_client *client);
int check_del_cl(t_server *serv);
int clients_length(t_clist *client_list);
void init_tile_tab(t_game *game, int i);
t_ressources init_ress(int gen);
int *get_ress_by_name(t_ressources *ress, char *name);
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
t_client *create_client(int socket, struct sockaddr_in in);
t_configuration *parse_args(int argc, char *argv[]);
void send_message(t_client *client, char *msg, ...);
void check_pos(t_game *game, t_position *pos);
t_client *get_cl_by_id(t_server *serv, int id);

int forward_cmd(t_server *serv, t_client *cl);
int right_cmd(t_server *serv, t_client *cl);
int left_cmd(t_server *serv, t_client *cl);
int look_cmd(t_server *serv, t_client *cl);
int inventory_cmd(t_server *serv, t_client *cl);
//int connect_nbr_cmd(t_server *serv, t_client *cl); // ??
//int fork_cmd(t_server *serv, t_client *cl);
int eject_cmd(t_server *serv, t_client *cl);
int take_cmd(t_server *serv, t_client *cl);
int set_cmd(t_server *serv, t_client *cl);
int incant_cmd(t_server *serv, t_client *cl);
int death_cmd(t_server *serv, t_client *cl);

int set_cmd_chk(t_server *serv, t_player *plr, char *cmd);
int take_cmd_chk(t_server *serv, t_player *plr, char *cmd);
int incant_cmd_chk(t_server *serv, t_player *plr, char *cmd);
int death_cmd_chk(t_server *serv, t_player *plr, char *cmd);

/*
** Graphic protocol
*/
int ppo_evnt(t_server *serv, t_player *plr);
int pin_evnt(t_server *serv, t_player *plr);
int plv_evnt(t_server *serv, t_player *plr);
int pex_evnt(t_server *serv, t_player *plr);
int bct_evnt(t_server *serv, int x, int y);
int mct_evnt(t_server *serv);
int msz_evnt(t_server *serv);
int sgt_evnt(t_server *serv);
int sst_evnt(t_server *serv, int freq);

char *get_one_line(t_server *serv, t_client *cl, int lvl);
char *get_one_tile(t_server *serv, t_position pos, int first);
char *get_tile_plr(t_server *serv, t_position pos, int first);
char *get_tile_ress(t_server *serv, t_position pos);
char *get_next_ress(t_ressources *ress);
void get_init_pos(t_server *serv, t_position *pos,
                    t_direction *dir, int lvl);
int incant_chk(t_server *serv, t_player *plr);
char *get_all_ress(t_ressources *ress);
int comp_ress(t_ressources need_ress, t_ressources map_ress);
int count_plr_pos_lvl(t_server *serv, t_player *plr);
int eject_dir_test(t_player *plr, t_player *tgt);
int do_eject(t_player *plr, t_player *tgt);

/*
** do strcat but count & realloc a if not large enough
*/
char *my_strcat(char *a, char *b, int *len);

#endif
