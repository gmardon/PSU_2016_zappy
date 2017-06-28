#include "server.h"

t_client *create_client(int socket, struct sockaddr_in in)
{
	t_client *client;

	client = my_malloc(sizeof(t_client));
	client->fd = socket;
	set_non_blocking(client->fd);

	client->in = in;
	client->team_id = -1;
	client->state = CLIENT_STATE_CONNECTED;
	client->player = NULL;
	return (client);
}

t_server *create_server(t_configuration *config)
{
	t_server *server;

	server = get_server_socket(config->port);
	server->configuration = config;
	server->max_clients = config->client_per_team * 2;
	server->max_id = 0;
	FD_ZERO(&server->master);
	FD_SET(server->fd, &server->master);
	server->game = init_game(config);
	return (server);
}

void handle_io(t_client *client, t_server *server) 
{
	char *buffer;
	int rc;
	int bytes_available;
	int len;

	buffer = my_malloc(BUFFER_SIZE);
	memset(buffer, 0, BUFFER_SIZE);
	printf("handle io with fd: %d\n", client->fd);
	rc = recv(client->fd, buffer, sizeof(buffer), 0);
	if (rc < 0)
	{
		if (errno != EWOULDBLOCK)
			close_client(client, server);
		return;
	}
	if (rc == 0)
	{
		close_client(client, server);
		return;
	}
	len = rc;
	printf("< %s", buffer);
	if (buffer[rc - 1] == '\n')
		buffer[rc - 1] = 0;
	handle_client_message(buffer, client, server);
}

void handle_new_client(t_server *server, int *max) 
{
	int index;
	t_client *client;
	t_clist *tmp;

	client = accept_client(server);
	FD_SET(client->fd, &server->master);
	if (client->fd > *max)
		*max = client->fd;

	if (clients_length(server->client_list) >= server->max_clients) 
	{
		send_message(client, "MAX USER REACHED\n");
		close_client(client);
		return;
	}
	else
		add_client(server, client);

	printf("New client connected from <%s:%d> with id %i\n", get_client_addr(client->in), get_client_port(client->in));
    send_message(client, "WELCOME\n");
}

void start_server(t_server *server)
{
	int max;
	int index;
	fd_set read_fds;
	t_client *client;
	t_clist *tmp;
	struct timeval tv = {1, 0};

	max = server->fd;
	printf("start on port %d, waiting for connections...\n", server->configuration->port);
	while (TRUE)
	{
		read_fds = server->master;
		if (select(max + 1, &read_fds, NULL, NULL, &tv) == -1)
			my_error("select", -1);
		if (FD_ISSET(server->fd, &read_fds))
			handle_new_client(server, &max);
		index = 0;
		
		tmp = server->client_list;
		while (tmp != NULL)
		{
			if (FD_ISSET(tmp->client->fd, &read_fds))
				handle_io(tmp->client, server);
			tmp = tmp->next;
		}
		if (calc_elapsed((1000000 / server->game->freq)))
        	do_one_cycle(server);
	}
}