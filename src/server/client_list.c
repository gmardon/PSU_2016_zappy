/*
** client_list.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Mon Jun 26 16:58:18 2017 Aurelien
** Last update Sun Jul  2 22:40:25 2017 Aurelien
*/
#include "server.h"

int		add_client(t_server *server, t_client *client)
{
  t_clist	*tmp;
  t_clist	*new;

  tmp = server->client_list;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  if ((new = malloc(sizeof(t_clist))) == NULL)
    return (1);
  new->client = client;
  new->next = NULL;
  if (tmp == NULL)
    server->client_list = new;
  else
    tmp->next = new;
  server->max_clients++;
  return (0);
}

int		del_client(t_server *server, int fd)
{
  t_clist	*tmp;
  t_clist	*old;

  tmp = server->client_list;
  old = NULL;
  while (tmp != NULL)
    {
      if (tmp->client->fd == fd)
	break;
      old = tmp;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return (0);
  if (old == NULL)
    server->client_list = tmp->next;
  else
    old->next = tmp->next;
  free_client(tmp->client);
  free(tmp);
  server->max_clients--;
  return (1);
}

int free_client(t_client *client)
{
  if (client->player != NULL)
    del_player(client->player);
  free(client);
  return (0);
}

int		clients_length(t_clist *client_list)
{
  t_clist	*tmp;
  int		i;

  i = 0;
  tmp = client_list;
  while (tmp != NULL)
    {
      tmp = tmp->next;
      i++;
    }
  return (i);
}

t_client	*get_cl_by_id(t_server *serv, int id)
{
  t_clist	*tmp;
  t_client	*ret;

  ret = NULL;
  tmp = serv->client_list;
  while (tmp != NULL)
    {
      if (tmp->client->player != NULL && tmp->client->player->id == id)
        {
	  ret = tmp->client;
	  break;
        }
      tmp = tmp->next;
    }
  return (ret);
}
