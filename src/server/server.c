/*
** server.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 22:51:50 2017 Aurelien
** Last update Sun Jul  2 23:36:00 2017 Aurelien
*/
#include "server.h"

t_client	*create_client(int socket, struct sockaddr_in in)
{
  t_client	*client;

  client = my_malloc(sizeof(t_client) * 2);
  client->fd = socket;
  set_non_blocking(client->fd);

  client->in = in;
  client->team_id = -1;
  client->state = CLIENT_STATE_CONNECTED;
  client->player = NULL;
  return (client);
}

t_server	*create_server(t_configuration *config)
{
  t_server	*server;
  int		i;

  i = -1;
  server = get_server_socket(config->port);
  server->client_list = NULL;
  server->configuration = config;
  while (config->teams[++i]);
  server->max_clients = config->client_per_team * i;
  server->max_id = 1;
  FD_ZERO(&server->master);
  FD_SET(server->fd, &server->master);
  server->game = init_game(config);
  return (server);
}

void	handle_io(t_client *client, t_server *server)
{
  char	*buffer;
  int	rc;

  buffer = my_malloc(BUFFER_SIZE);
  memset(buffer, 0, BUFFER_SIZE);
  rc = recv(client->fd, buffer, BUFFER_SIZE, 0);
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
  if (buffer[rc - 1] == '\n')
    buffer[rc - 1] = 0;
  printf("< %s\n", buffer);
  handle_client_message(buffer, client, server);
}

void		handle_new_client(t_server *server, int *max)
{
  t_client	*client;

  client = accept_client(server);
  FD_SET(client->fd, &server->master);
  if (client->fd > *max)
    *max = client->fd;

  if (clients_length(server->client_list) >= server->max_clients)
    {
      send_message(client, "MAX USER REACHED\n");
      close_client(client, server);
      return;
    }
  else
    add_client(server, client);
  printf("New client connected from <%s:%d>\n",
	 get_client_addr(client->in), get_client_port(client->in));
  send_message(client, "WELCOME\n");
}

void			start_server(t_server *server)
{
  int			max;
  fd_set		read_fds;
  t_clist		*tmp;
  struct timeval	tv = {1, 0};

  max = server->fd;
  printf("start on port %d, waiting for connections...\n",
	 server->configuration->port);
  while (check_game_finish(server))
    {
      read_fds = server->master;
      if (select(max + 1, &read_fds, NULL, NULL, &tv) == -1)
	my_error("select", -1);
      if (FD_ISSET(server->fd, &read_fds))
	handle_new_client(server, &max);
      tmp = server->client_list;
      while (tmp != NULL)
	{
	  if (FD_ISSET(tmp->client->fd, &read_fds))
	    handle_io(tmp->client, server);
	  tmp = tmp->next;
	}
      game_funct(server);
    }
}
