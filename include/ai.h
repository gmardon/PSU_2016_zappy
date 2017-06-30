/*
** ai.h for  in /home/julienN/PSU_2016_zappy/include
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:30:03 2017 Julien Nabti
** Last update Fri Jun 30 17:30:03 2017 Julien Nabti
*/


#ifndef _AI_H_
#define _AI_H_ 
#include "zappy.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
#include <pthread.h>

struct  s_opt;

typedef struct s_opt    t_opt;

struct  s_opt
{
    int     port;
    char    *hostname;
    char    *team;
};

int          X_MAX;
int          Y_MAX;
const int    tab[7][8];
char         read_buffer[512];
char         stones[7][10];

struct  s_client;
struct  s_cmd;
struct  s_rscs;

typedef struct s_cmd    t_cmd;
typedef struct s_rscs   t_rscs;
typedef int             t_fd;

typedef struct s_client
{
    t_fd                fd;
    t_opt               *options;
    struct sockaddr_in	server_addr;
    int                 end;
} t_client;

struct  s_cmd
{
    char   *key;
    int    (*fptr)(t_client *, char *);
};

struct  s_rscs
{
    char   *key;
    void   (*fptr)(t_client *);
};

struct s_players{
  int rd;
  char *invent;
  char *seen;
  t_client *client;
  char *team;
  int lvl;
  int direction;
  int X;
  int Y;

  int food;
  int linemate;
  int deraumere;
  int sibur;
  int mendiane;
  int phiras;
  int thystame;
};

struct s_map{
  int eat;
  int nbr_player;
  int egg;

  int linemate;
  int deraumere;
  int sibur;
  int mendiane;
  int phiras;
  int thystame;
};

int             retrieve_options(t_client *, int, char **);
void            destroy_client(t_client **);
t_client *init_client();
int             launch_client(t_client *);

const struct s_cmd   cmd_tab[12];

void send_go(t_client *);
void send_right(t_client *);
void send_left(t_client *);
void send_see(t_client *);
void send_stuff(t_client *);
void send_take(t_client *, char *);
void send_lay(t_client *, char *);
void send_expulse(t_client *);
void send_broadcast(t_client *, char *);
void send_incantation(t_client *);
void send_fork(t_client *);
void send_connect(t_client *);
void send_dead(t_client *);
int ia(t_client *);
int go_obj(struct s_players * player, char *seen, char *obj);
int find_obj(char *seen, char *obj);
void receve_see(struct s_players * player);
void receve_stuff(struct s_players * player);
int find_inv(char * inventaire, int obj);

void    take_food(t_client * client);
void    take_linemate(t_client * client);
void    take_deraumere(t_client * client);
void    take_sibur(t_client * client);
void    take_mendiane(t_client * client);
void    take_phiras(t_client * client);
void    take_thystame(t_client * client);

int     listen_cmp(t_client *client);

typedef struct s_configuration
{
    int				port;
    char*			name;
    char*			machine;
}				t_configuration;

t_configuration *parse_args(int argc, char *argv[]);

void init_player(struct s_players *player, char *team, t_client * client);
void init_map(struct s_map * map);
char *choose_stone(struct s_players * player, char *seen, char * inv);
int go(struct s_players * player);
int all_stone(struct s_players * player);
void inventaire(struct s_players * player, char * inventaire);
int find_inv(char * inventaire, int obj);
void lay_all(struct s_players * player);
int nbr_player(char *seen);
void aff_map(struct s_map * map);
void sync_map(struct s_map * map, struct s_players * players);
void clear_map(struct s_map * map);
void move_player(struct s_players * players, int direction);
void turn_left(struct s_players * players);
void move(struct s_players * players);
void turn_right(struct s_players * players);
void take(t_client *, char *);
void eat(struct s_map * map, struct s_players * players);
void create_player(struct s_players * players, int x, int y, int team);
char * stuff(struct s_players * players);
char * see(struct s_map * map, struct s_players * player);
#endif
