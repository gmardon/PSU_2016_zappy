
/*
** map_info.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/graph_protocol
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Tue Jun 27 19:56:29 2017 Aurelien
** Last update Sun Jul  2 23:10:45 2017 Aurelien
*/
#include "server.h"

int	bct_evnt(t_server *serv, int x, int y)
{
  char	*ret;
  char	*tmp;

  if ((ret = malloc(sizeof(char) * 111)) == NULL)
    return (1);
  if ((tmp = get_all_ress(&(serv->game->map[x][y].ress))) == NULL)
    return (1);
  sprintf(ret, "bct %d %d %s\n", x, y, tmp);
  add_resp(serv->game, ret, GRAPHIC);
  free(tmp);
  free(ret);
  return (0);
}

int	mct_evnt(t_server *serv)
{
  int	x;
  int	y;

  x = y = 0;
  while (y < serv->game->height)
    {
      x = 0;
      while (x < serv->game->width)
        {
	  bct_evnt(serv, x, y);
	  x++;
        }
      y++;
    }
  return (0);
}

int	msz_evnt(t_server *serv)
{
  char	*ret;

  if ((ret = malloc(sizeof(char) * 111)) == NULL)
    return (1);
  sprintf(ret, "msz %d %d\n", serv->game->width,
	  serv->game->height);
  add_resp(serv->game, ret, GRAPHIC);
  free(ret);
  return (0);
}

int	pie_evnt(t_server *serv, t_player *plr, int r)
{
  char	*ret;

  if ((ret = malloc(sizeof(char) * 111)) == NULL)
    return (1);
  sprintf(ret, "pie %d %d %d\n", plr->pos.x,
	  plr->pos.y, r);
  add_resp(serv->game, ret, GRAPHIC);
  free(ret);
  return (0);
}
