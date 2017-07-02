/*
** client.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 22:42:32 2017 Aurelien
** Last update Sun Jul  2 22:43:30 2017 Aurelien
*/
#include "server.h"

void		send_message(t_client *client, char *msg, ...)
{
  char		*content;
  int		len;
  va_list	args;

  content = my_malloc(40960);
  if (client->fd)
    {
      va_start(args, msg);
      len = vsprintf(content, strdup(msg), args);
      printf("> %s", content);
      write(client->fd, content, len);
      va_end(args);
    }
}

void close_client(t_client *client, t_server *server)
{
  if (client->fd > 0)
    {
      FD_CLR(client->fd, &server->master);
      close(client->fd);
    }
  client->fd = 0;
  printf("Client disconnected <%s:%d>\n",
	 get_client_addr(client->in), get_client_port(client->in));
}

int	check_del_cl(t_server *serv)
{
  int	count;

  count = 0;
  while (del_client(serv, 0))
    count++;
  return (count);
}
