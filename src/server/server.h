#ifndef _SERVER_H_
#define _SERVER_H_ 
#include "zappy.h"
typedef struct s_server
{
	int fd;
	struct sockaddr_in in;
    int pid;
}						t_server;

typedef struct s_client
{
	int fd;
	struct sockaddr_in in;
}						t_client;

char *get_client_addr(struct sockaddr_in client);
int get_client_port(struct sockaddr_in client);

void handle_client(t_client *client);
#endif