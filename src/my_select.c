#include "zappy.h"

int my_select(int fd_max, fd_set *fd_read, fd_set *fd_write)
{
  struct timeval	tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  if (select(fd_max + 1, fd_read, fd_write, NULL, &tv) == -1)
    my_error("select failed", -1);
  return (0);
}