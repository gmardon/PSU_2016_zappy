/*
** graph_plr_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/commands
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Thu Jun 29 02:46:55 2017 Aurelien
** Last update Sun Jul  2 23:02:33 2017 Aurelien
*/
#include "server.h"

int msz_cmd(t_server *serv, t_client *cl)
{
  if (cl)
    msz_evnt(serv);
  return (0);
}

int mct_cmd(t_server *serv, t_client *cl)
{
  if (cl)
    mct_evnt(serv);
  return (0);
}

int tna_cmd(t_server *serv, t_client *cl)
{
  if (cl)
    all_tna_evnt(serv);
  return (0);
}

int sgt_cmd(t_server *serv, t_client *cl)
{
  if (cl)
    sgt_evnt(serv);
  return (0);
}
