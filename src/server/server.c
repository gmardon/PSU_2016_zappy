#include "server.h"

void set_non_blocking(int socket)
{
	int opts;

	opts = fcntl(socket, F_GETFL);
	if (opts < 0)
		my_error("fcntl(F_GETFL)", EXIT_FAILURE);
	opts = (opts | O_NONBLOCK);
	if (fcntl(socket, F_SETFL, opts) < 0)
		my_error("fcntl(F_SETFL)", EXIT_FAILURE);
	return;
}

t_client *alloc_new_client(int socket, struct sockaddr_in in, t_server *server)
{
	int opt;
	t_client *client;

	opt = 1;
	client = my_malloc(sizeof(t_client));
	client->fd = socket;
	set_non_blocking(client->fd);

	client->in = in;
	client->team_id = -1;
	//client->server = server;
	return (client);
}

t_client *accept_client(t_server *server)
{
	t_client *client;
	socklen_t length;
	int socket;
	struct sockaddr_in in;

	length = sizeof(in);
	if ((socket = accept(server->fd, (struct sockaddr *)&in, &length)) == -1)
		my_error("Can't accept one client connection", -1);
	else
	{
		if (!(client = alloc_new_client(socket, in, server)))
			return;
			
		handle_client(client);
		return (client);
	}
}

t_server *get_server_socket(int port)
{
	t_server *server;
	int opt;

	opt = TRUE;
	server = (t_server *)my_malloc(sizeof(struct s_server));
	if ((server->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		my_error("Can't create socket", -1);
	server->in.sin_family = AF_INET;
	server->in.sin_addr.s_addr = INADDR_ANY;
	server->in.sin_port = htons(port);
	bzero(&(server->in.sin_zero), 8);
	if ((setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))) < 0)
		my_error("Can't allow multiple connection on socket", -1);
	if ((bind(server->fd, (struct sockaddr *)&server->in, sizeof(server->in))) < 0)
		my_error("Can't bind socket", -1);
	if ((listen(server->fd, 10)) == -1)
		my_error("Can't listen the socket", -1);
	set_non_blocking(server->fd);
	return (server);
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
		{
			FD_CLR(client->fd, &server->master);
			close_client(client);
		}
		return;
	}
	
	if (rc == 0)
	{
		FD_CLR(client->fd, &server->master);
		close_client(client);
		return;
	}
	len = rc;
	printf("< %s", buffer);
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
		// cannot connect
		send_message(client, "MAX USER REACHED\n");
		close_client(client);
	}
	else
	{
		server->clients[index] = *client;
	}
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
	}
}