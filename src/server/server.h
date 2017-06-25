#ifndef _SERVER_H_
#define _SERVER_H_ 
#include "zappy.h"
#define CLIENT_STATE_CONNECTED 1
#define CLIENT_STATE_TEAM_SELECTED 2

typedef struct		s_position
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

typedef struct s_client
{
	int fd;
	struct sockaddr_in in;
    int team_id;
    int state;
    int id;
    t_position position;
}						t_client;

typedef struct s_server
{
	int fd;
	struct sockaddr_in in;
    int sock;
    fd_set master;
    int max_clients;
    t_client *clients;
    t_configuration *configuration;
}						t_server;

t_configuration *parse_args(int argc, char *argv[]);
char *get_client_addr(struct sockaddr_in client);
int get_client_port(struct sockaddr_in client);
t_server *create_server(t_configuration *config);
void handle_client(t_client *client);
void start_server(t_server *server);
t_server *get_server_socket(int port);
t_client *accept_client(t_server *server);
t_client *alloc_new_client(int socket, struct sockaddr_in in, t_server *server);
#endif