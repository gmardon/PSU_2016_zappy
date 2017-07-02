/*
** map_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jun 25 23:14:25 2017 Aurelien
** Last update Sun Jul  2 23:06:30 2017 Aurelien
*/
#include "server.h"

void get_init_pos(t_server *serv, t_position *pos,
		  t_direction *dir, int lvl)
{
  pos->y += dir->y * lvl;
  pos->x += dir->x * lvl;
  check_pos(serv->game, pos);
  if (dir->x != 0)
    {
      dir->y = dir->x;
      dir->x = 0;
    }
  else if (dir->y != 0)
    {
      dir->x = (dir->y * -1);
      dir->y = 0;
    }
  pos->x += dir->x * lvl;
  pos->y += dir->y * lvl;
  check_pos(serv->game, pos);
}

char	*get_next_ress(t_ressources *ress)
{
  char	*tmp;

  tmp = NULL;
  if (ress->linemate > 0 && (ress->linemate -= 1) >= 0)
    tmp = strdup("linemate");
  else if (ress->deraumere > 0 && (ress->deraumere -= 1) >= 0)
    tmp = strdup("deraumere");
  else if (ress->sibur > 0 && (ress->sibur -= 1) >= 0)
    tmp = strdup("sibur");
  else if (ress->mendiane > 0 && (ress->mendiane -= 1) >= 0)
    tmp = strdup("mendiane");
  else if (ress->phiras > 0 && (ress->phiras -= 1) >= 0)
    tmp = strdup("phiras");
  else if (ress->thystame > 0 && (ress->thystame -= 1) >= 0)
    tmp = strdup("thystame");
  else if (ress->food > 0 && (ress->food -= 1) >= 0)
    tmp = strdup("food");
  return (tmp);
}

char		*my_strcat(char *a, char *b, int *len)
{
  ssize_t	i;
  ssize_t	j;

  i  = j = -1;
  while (a[++i] != '\0');
  while (b[++j] != '\0');
  a = realloc(a, sizeof(char) * (i + j + 22));
  if (len != NULL)
    *len = i + j + 22;
  strcat(a, b);
  return (a);
}
