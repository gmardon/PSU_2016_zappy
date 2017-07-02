/*
** obj_info.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/graph_protocol
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 21:40:21 2017 Aurelien
** Last update Sun Jul  2 23:11:54 2017 Aurelien
*/
#include "server.h"

int	 pgt_evnt(t_server *serv, t_player *plr, char *str)
{
  char	*ret;

  ret = my_malloc(sizeof(char) * 69);
  sprintf(ret, "pgt %d %d\n", plr->id,
	  get_ress_num(str));
  add_resp(serv->game, ret, GRAPHIC);
  free(ret);
  return (0);
}

int	pdr_evnt(t_server *serv, t_player *plr, char *str)
{
  char	*ret;

  ret = my_malloc(sizeof(char) * 69);
  sprintf(ret, "pdr %d %d\n", plr->id,
	  get_ress_num(str));
  add_resp(serv->game, ret, GRAPHIC);
  free(ret);
  return (0);
}

int take_evnt(t_server *serv, t_player *plr, char *str)
{
  pgt_evnt(serv, plr, str);
  pin_evnt(serv, plr);
  bct_evnt(serv, plr->pos.x, plr->pos.y);
  return (0);
}

int set_evnt(t_server *serv, t_player *plr, char *str)
{
  pdr_evnt(serv, plr, str);
  pin_evnt(serv, plr);
  bct_evnt(serv, plr->pos.x, plr->pos.y);
  return (0);
}

int get_ress_num(char *str)
{
  if (strstr(str, "linemate") != NULL)
    return (1);
  else if (strstr(str, "deraumere") != NULL)
    return (2);
  else if (strstr(str, "sibur") != NULL)
    return (3);
  else if (strstr(str, "mendiane") != NULL)
    return (4);
  else if (strstr(str, "phiras") != NULL)
    return (5);
  else if (strstr(str, "thystame") != NULL)
    return (6);
  else if (strstr(str, "food") != NULL)
    return (0);
  return (7);
}
