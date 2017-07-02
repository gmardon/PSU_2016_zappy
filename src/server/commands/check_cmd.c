/*
** check_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/commands
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Fri Jun 30 03:31:36 2017 Aurelien
** Last update Sun Jul  2 22:57:04 2017 Aurelien
*/
#include "server.h"

int		set_cmd_chk(t_server *serv,
			    t_player *plr,
			    char *cmd)
{
  t_ressources	*re;
  int		*obj;
  char		*str;

  re = &(plr->ress);
  if ((str = strstr(cmd, "Set")) == NULL)
    return (666);
  str += (uintptr_t) 4;
  while (*str == ' ')
    str += (uintptr_t) 1;
  if ((obj = get_ress_by_name(re, str)) == NULL || *obj <= 0)
    {
      add_resp(serv->game, "ko\n", plr->id);
      return (404);
    }
  return (0);
}

int		take_cmd_chk(t_server *serv, t_player *plr, char *cmd)
{
  t_ressources	*re;
  int		*obj;
  char		*str;

  re = &(serv->game->map[plr->pos.x][plr->pos.y].ress);
  if ((str = strstr(cmd, "Take")) == NULL)
    return (666);
  str += (uintptr_t) 4;
  while (*str == ' ')
    str += (uintptr_t) 1;
  if ((obj = get_ress_by_name(re, str)) == NULL || *obj <= 0)
    {
      add_resp(serv->game, "ko\n", plr->id);
      return (404);
    }
  return (0);
}

int death_cmd(t_server *serv, t_client *cl)
{
  close_client(cl, serv);
  return (0);
}

int death_cmd_chk(t_server *serv, t_player *plr, char *cmd)
{
  if (cmd)
    {
      add_resp(serv->game, "dead\n", plr->id);
      pdi_evnt(serv, plr);
    }
  return (0);
}
