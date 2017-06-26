/*
** player_info.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/graph_protocol
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Mon Jun 26 23:58:56 2017 Aurelien
** Last update Mon Jun 26 23:59:06 2017 Aurelien
*/
#include "server.h"

int ppo_evnt(t_server *serv, t_player *plr)
{
    char *ret;
    int orient;

    if ((ret = malloc(sizeof(char) * 111)) == NULL)
        return (1);
    if (plr->dir.y < 0)
        orient = 1;
    else if (plr->dir.y > 0)
        orient = 3;
    else if (plr->dir.x > 0)
        orient = 2;
    else
        orient = 4;
    sprintf(ret, "ppo #%d %d %d %d\n",
    plr->id, plr->pos.x, plr->pos.y, orient);
    add_resp(serv->game, ret, plr->id);
    free(ret);
    return (0);
}