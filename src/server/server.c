#include "server.h"

t_client *create_client(int socket, struct sockaddr_in in)
{
	int opt;
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
	server->clients = calloc(server->max_clients + 1, sizeof(t_client) + 1);
	server->clients[server->max_clients + 1].fd = -1;
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

	client = accept_client(server);

	FD_SET(client->fd, &server->master);
	if (client->fd > *max)
		*max = client->fd;
	index = 0;
	while (server->clients[index].fd < 0 && index != server->max_clients)
		index++;
	if (index == server->max_clients)
	{
		send_message(client, "MAX USER REACHED\n");
		close_client(client);
		return;
	}
	else
		server->clients[index] = *client;

	printf("New client connected from <%s:%d>\n", get_client_addr(client->in), get_client_port(client->in));
    send_message(client, "WELCOME\n");
}

void start_server(t_server *server)
{
	int max;
	int index;
	fd_set read_fds;
	t_client *client;

	max = server->fd;
	printf("start on port %d, waiting for connections...\n", server->configuration->port);
	while (TRUE)
	{
		read_fds = server->master;
		if (select(max + 1, &read_fds, NULL, NULL, 0) == -1)
			my_error("select", -1);
		if (FD_ISSET(server->fd, &read_fds))
			handle_new_client(server, &max);
		index = 0;
		while (server->clients[index].fd > 0 && index != server->max_clients)
		{
			if (FD_ISSET(server->clients[index].fd, &read_fds))
				handle_io(&server->clients[index], server);
			index++;
		}
		if (calc_elapsed((1000000 / server->game->freq)))
        	do_one_cycle(server);
	}
}