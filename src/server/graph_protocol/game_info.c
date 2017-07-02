/*
** game_info.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/graph_protocol
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Tue Jun 27 20:11:21 2017 Aurelien
** Last update Sun Jul  2 23:10:01 2017 Aurelien
*/
#include "server.h"

int		all_pnw_evnt(t_server *serv)
{
  t_clist	*tmp;

  tmp = serv->client_list;
  while (tmp != NULL)
    {
      if (tmp->client->player != NULL)
	pnw_evnt(serv, tmp->client->player);
      tmp = tmp->next;
    }
  return (0);
}

int	pnw_evnt(t_server *serv, t_player *plr)
{
  char	*ret;
  char	*team;
  int	orient;

  team = get_team_by_id(serv, plr->team_id);
  ret = malloc(sizeof(char) * (strlen(team) + 111));
  if (plr->dir.y < 0)
    orient = 1;
  else if (plr->dir.y > 0)
    orient = 3;
  else if (plr->dir.x > 0)
    orient = 2;
  else
    orient = 4;
  sprintf(ret, "pnw %d %d %d %d %d %s\n",
	  plr->id, plr->pos.x, plr->pos.y, orient, plr->lvl,
	  team);
  return (0);
}

int	all_tna_evnt(t_server *serv)
{
  char	*ret;
  char	*tmp;
  int	i;

  i = 0;
  while (serv->configuration->teams[i])
    {
      tmp = serv->configuration->teams[i];
      ret = my_malloc(sizeof(char) * strlen(tmp) + 111);
      sprintf(ret, "tna %s\n", tmp);
      add_resp(serv->game, ret, GRAPHIC);
      free(ret);
      i++;
    }
  return (0);
}

int	sgt_evnt(t_server *serv)
{
  char	*ret;

  if ((ret = malloc(sizeof(char) * 22)) == NULL)
    return (1);
  sprintf(ret, "sgt %d\n", serv->game->freq);
  add_resp(serv->game, ret, GRAPHIC);
  free(ret);
  return (0);
}

int sst_evnt(t_server *serv, int freq)
{
  if (freq < 1)
    return (2);
  serv->game->freq = freq;
  return (sgt_evnt(serv));
}
