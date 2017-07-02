/*
** my_select.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 23:15:52 2017 Aurelien
** Last update Sun Jul  2 23:16:16 2017 Aurelien
*/
#include "zappy.h"

int			my_select(int fd_max,
				  fd_set *fd_read,
				  fd_set *fd_write)
{
  struct timeval	tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  if (select(fd_max + 1, fd_read, fd_write, NULL, &tv) == -1)
    my_error("select failed", -1);
  return (0);
}
