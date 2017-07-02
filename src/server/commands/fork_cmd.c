/*
** fork_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/commands
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 04:00:44 2017 Aurelien
** Last update Sun Jul  2 23:01:57 2017 Aurelien
*/
#include "server.h"

int fork_cmd(t_server *serv, t_client *cl)
{
  add_egg(serv, cl->player->pos, cl);
  add_resp(serv->game, "ok\n", cl->player->id);
  return (0);
}

int	connect_nbr_cmd(t_server *serv, t_client *cl)
{
  char	*resp;
  int	nb;

  nb = get_conn_nbr(serv, cl->team_id);
  resp = my_malloc(sizeof(char) * 33);
  sprintf(resp, "%d\n", nb);
  add_resp(serv->game, resp, cl->player->id);
  free(resp);
  return (0);
}

t_egg_list	*get_egg_by_team(t_server *serv, int team_id)
{
  t_egg_list	*tmp;

  tmp = serv->game->egg;
  while (tmp != NULL)
    {
      if (tmp->team_id == team_id)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

int		add_egg(t_server *serv,
			t_position pos,
			t_client *cl)
{
  static int	egg_id = 1;
  t_egg_list	*tmp;
  t_egg_list	*new;

  tmp = serv->game->egg;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  if ((new = malloc(sizeof(t_egg_list))) == NULL)
    return (1);
  new->id = egg_id;
  new->team_id = cl->team_id;
  new->plr_id = cl->player->id;
  new->pos = pos;
  new->hatch_time = 600;
  new->next = NULL;
  if (tmp == NULL)
    serv->game->egg = new;
  else
    tmp->next = new;
  egg_id++;
  serv->max_clients += 1;
  enw_evnt(serv, new);
  return (0);
}

int		del_egg(t_server* serv, t_egg_list *egg)
{
  t_egg_list	*tmp;
  t_egg_list	*old;

  tmp = serv->game->egg;
  old = NULL;
  while (tmp != NULL)
    {
      if (tmp == egg)
	break;
      old = tmp;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return (0);
  if (old == NULL)
    serv->game->egg = tmp->next;
  else
    old->next = tmp->next;
  free(tmp);
  serv->max_clients -= 1;
  return (0);
}
