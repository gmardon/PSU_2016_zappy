#include "server.h"

t_client *alloc_new_client(int socket, struct sockaddr_in in)
{
	t_client	*client;

    client = my_malloc(sizeof(t_client));
	client->fd = socket;
	client->in = in;
	return (client);
}

void accept_client(t_server *server)
{
	t_client *client;
	socklen_t length;
	int socket;
	struct sockaddr_in in;
	pid_t child_pid;

	length = sizeof(in);
	if ((socket = accept(server->fd, (struct sockaddr*)&in, &length)) == -1)
		my_error("Can't accept one client connection", -1);
	else
	{
		if (!(client = alloc_new_client(socket, in)))
			return ;

		child_pid = fork();
		if (child_pid == 0) {
            server->pid = getpid();
			handle_client(client);
        }
	}
}

t_server *get_socket(int port)
{
	t_server	*server;
	int			opt;

	opt = TRUE;
	server = (t_server*)my_malloc(sizeof(struct s_server));
	if ((server->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		my_error("Can't create socket", -1);
	server->in.sin_family = AF_INET;
	server->in.sin_addr.s_addr = INADDR_ANY;
	server->in.sin_port = htons(port);
	if ((setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))) < 0)
		my_error("Can't allow multiple connection on socket", -1);
	if ((bind(server->fd, (struct sockaddr *)&server->in, sizeof(server->in))) < 0)
		my_error("Can't bind socket", -1);
	if ((listen(server->fd, 3)) == -1)
		my_error("Can't listen the socket", -1);
	return (server);
}

void init_server(int port)
{
	t_server *server;

	if (port > 0 && port <= 65535)
	{
		server = get_socket(port);
		printf("start on port %d, waiting for connections...\n", port);
		while (TRUE)
			accept_client(server);
	}
	else
		printf("Give me a real port..\n");
}