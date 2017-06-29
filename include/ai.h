#ifndef _AI_H_
#define _AI_H_ 
#include "zappy.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>

struct  s_opt;

typedef struct s_opt    t_opt;

struct  s_opt
{
    int     port;
    char    *hostname;
    char    *team;
};

extern int          X_MAX;
extern int          Y_MAX;
extern const int    tab[7][8];
extern char         read_buffer[512];
extern char         stones[7][10];

int ia(struct s_client *);
int go_obj(struct s_players * player, char *seen, char *obj);
int find_obj(char *seen, char *obj);
void receve_see(struct s_players * player);
void receve_stuff(struct s_players * player);
int find_inv(char * inventaire, int obj);

void    take_food(struct s_client * client);
void    take_linemate(struct s_client * client);
void    take_deraumere(struct s_client * client);
void    take_sibur(struct s_client * client);
void    take_mendiane(struct s_client * client);
void    take_phiras(struct s_client * client);
void    take_thystame(struct s_client * client);

int     listen_cmp(struct s_client *client);

struct  s_client;
struct  s_cmd;
struct  s_rscs;

typedef struct s_client t_client;
typedef struct s_cmd    t_cmd;
typedef struct s_rscs   t_rscs;
typedef int             t_fd;

struct s_client
{
    t_fd                fd;
    t_opt               *options;
    struct sockaddr_in	server_addr;
    int                 end;
};

struct  s_cmd
{
    char   *key;
    int    (*fptr)(struct s_client *, char *);
};

struct  s_rscs
{
    char   *key;
    void   (*fptr)(struct s_client *);
};

struct s_players{
  int rd;
  char *invent;
  char *seen;
  struct s_client *client;
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

int             retrieve_options(struct s_client *,
                                 int, char **);
void            destroy_client(struct s_client **);
struct s_client *init_client();
int             launch_client(struct s_client *);

extern const struct s_cmd   cmd_tab[12];

void send_go(struct s_client *);
void send_right(struct s_client *);
void send_left(struct s_client *);
void send_see(struct s_client *);
void send_stuff(struct s_client *);
void send_take(struct s_client *, char *);
void send_lay(struct s_client *, char *);
void send_expulse(struct s_client *);
void send_broadcast(struct s_client *, char *);
void send_incantation(struct s_client *);
void send_fork(struct s_client *);
void send_connect(struct s_client *);
void send_dead(struct s_client *);

typedef struct s_configuration
{
    int				port;
    char*			name;
    char*			machine;
}				t_configuration;

t_configuration *parse_args(int argc, char *argv[]);

void init_player(struct s_players *player, char *team,
struct s_client * client);
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

void move_player(struct s_players * players, int direction, int player);
void turn_left(struct s_players * players);
void move(struct s_players * players);
void turn_right(struct s_players * players);

void take(struct s_client *, char *);
void eat(struct s_map * map, struct s_players * players);
void create_player(struct s_players * players, int x, int y, int team);
char * stuff(struct s_players * players);
char * see(struct s_map * map, struct s_players * player);
#endif