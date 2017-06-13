#ifndef _SERVER_H_
#define _SERVER_H_ 
#include "zappy.h"

typedef struct s_client
{
	int fd;
	struct sockaddr_in in;
    int team_id;
}						t_client;

typedef struct s_configuration
{
    int				port;
    int				world_height;
    int				world_width;
    //LinkedList(string)		*teamNames;
    int				initial_client_per_team;
    double			temporal_delay;
    int				seed;
    char*           team1_name;
    char*           team2_name;
}				t_configuration;

typedef struct s_server
{
	int fd;
	struct sockaddr_in in;
    int pid;
    t_configuration *configuration;
}						t_server;

t_configuration *parse_args(int argc, char *argv[]);
char *get_client_addr(struct sockaddr_in client);
int get_client_port(struct sockaddr_in client);
t_server *create_server(t_configuration *config);
void handle_client(t_server *server, t_client *client);
#endif