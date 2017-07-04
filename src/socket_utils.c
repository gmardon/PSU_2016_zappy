/*
** socket_utils.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 23:16:30 2017 Aurelien
** Last update Tue Jul  4 11:31:55 2017 Julien Nabti
*/
#include "zappy.h"

void	set_non_blocking(int socket)
{
  int	opts;

  opts = fcntl(socket, F_GETFL);
  if (opts < 0)
    my_error("fcntl(F_GETFL)", EXIT_FAILURE);
  opts = (opts | O_NONBLOCK);
  if (fcntl(socket, F_SETFL, opts) < 0)
    my_error("fcntl(F_SETFL)", EXIT_FAILURE);
  return;
}
