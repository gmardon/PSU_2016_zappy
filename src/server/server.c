#include "server.h"

#define BUFF_SIZE 1024

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
	FD_ZERO(&server->master);
	FD_SET(server->fd, &server->master);
	server->game = init_game(config);

	server->client_list = my_malloc(sizeof(t_clist ));
	server->client_list->next = my_malloc(sizeof(t_clist));
	server->client_list->client = my_malloc(sizeof(t_client));
	server->client_list->client->fd = 0;
	
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
	if (buffer[rc - 1] == '\n')
		buffer[rc - 1] = 0;
	printf("< %s", buffer);
	//	handle_client_message(buffer, client, server);
}

void handle_new_client(t_server *server, int *max) 
{
	int index;
	t_client *client;
	t_clist *tmp;

	client = accept_client(server);

	//	FD_SET(client->fd, &server->master);//?
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

	printf("New client connected from <%s:%d>\n", get_client_addr(client->in), get_client_port(client->in));
    send_message(client, "WELCOME\n");
}



void	cleanup_server(t_server *server)
{
  if (server->client_list != NULL)
    {
      t_clist *clr;
      while (server->client_list != NULL)
	{
	  clr = server->client_list;
	  server->client_list = server->client_list->next;
	  free(clr);
	}
      free(server->client_list);
    }
  if (server->configuration != NULL)
    free(server->configuration);
  if (server->game != NULL)
    free(server->game);

}

void start_server(t_server *server)
{
	int max;
	int index;
	fd_set read_fds;
	fd_set write_fds;
	fd_set except_fds;
	//	t_client *client;
	t_clist *tmp;
	struct timeval tv = {1, 0};
	int	i;
	char	*buff;
	
		      
	server->max_clients = server->fd;
	buff = my_malloc(BUFF_SIZE * sizeof(char));
	printf("[*] Starting server routine on port %d...\n", server->configuration->port);
	while (TRUE)
	{
	  tmp = server->client_list;
	  i = -1;
	  FD_ZERO(&read_fds);
	  FD_ZERO(&write_fds);
	  FD_ZERO(&except_fds);
	  FD_SET(server->fd, &read_fds);
	  FD_SET(STDIN_FILENO, &read_fds);
	  while (tmp != NULL && ++i < server->max_clients)
	    {
	      if (tmp->client->fd > 0)
		{
		  FD_SET(tmp->client->fd, &read_fds);
		  FD_SET(tmp->client->fd, &write_fds);
		  FD_SET(tmp->client->fd, &except_fds);
		}
	      if (tmp->client->fd > server->max_clients)
		server->max_clients = tmp->client->fd;
	      tmp = tmp->next;
	    }

	  
	  /* read_fds = server->master; */
	  if (select(max + 1, &read_fds, &write_fds, &except_fds, &tv) == -1)
	    my_error("[!] Select failed", -1);

	  tmp = server->client_list;
	  i = -1;
	  if (FD_ISSET(server->fd, &read_fds))
	    {
	      printf("[*] Adding new client ...\n");
	      handle_new_client(server, &max);
	    }
	  if (FD_ISSET(STDIN_FILENO, &read_fds))
	    {
	      fgets(buff, BUFF_SIZE, STDIN_FILENO);
	      switch (buff[0])
		{
		case 'e' :
		  printf ("[*} Exit ...\n");
		  cleanup_server(server);
		  exit (1);
		case 'c' :
		  printf("[*] Clients nb : %d\n", server->max_clients);
		}
	    }
	  while (tmp != NULL && ++i < server->max_clients)
	    {

	      if (FD_ISSET(tmp->client->fd, &read_fds))
		{
		  /* handle_io(tmp->client, server); */
		  int	ret;

		  if ((ret = read(tmp->client->fd, buff, BUFF_SIZE)) == 0)
		    {
		      printf("[*} Client disconnected [%s : %d] ...\n",
			     get_client_addr(tmp->client->in), get_client_port(tmp->client->in));
		      close_client(tmp->client->fd);
		    }
		  else
		    {
		      buff[ret] = 0;
		      printf("[*] Message recieved : [%s] ...\n", buff);
		    }
		}
	      if (FD_ISSET(tmp->client->fd, &write_fds))
		{
		  buff = strdup("Zappy\n");
		  if (write(tmp->client->fd, buff, strlen(buff) != strlen(buff)))
		    my_error("[!] Error while sending greeting msg\n", -1);
		}
	      if (FD_ISSET(tmp->client->fd, &except_fds))
		{
		  printf("[!] An error ocurred on socket %d, killing connection ...");
		  close_client(tmp->client, server);
		  printf(" Done.\n");
		}
	      tmp = tmp->next;
	    }
	  if (calc_elapsed((1000000 / server->game->freq)))
	    do_one_cycle(server);
	}
}
