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
    add_resp(serv->game, ret, GRAPHIC);
    free(ret);
    return (0);
}

int plv_evnt(t_server *serv, t_player *plr)
{
    char *ret;

    if ((ret = malloc(sizeof(char) * 111)) == NULL)
        return (1);
    sprintf(ret, "plv #%d %d\n",
    plr->id, plr->lvl);
    add_resp(serv->game, ret, GRAPHIC);
    free(ret);
    return (0);
}

int pin_evnt(t_server *serv, t_player *plr)
{
    char *ret;
    char *tmp;

    if ((ret = malloc(sizeof(char) * 111)) == NULL)
        return (1);
    if ((tmp = get_all_ress(&(plr->ress))) == NULL)
        return (1);
    sprintf(ret, "pin #%d %d %d %s\n",
    plr->id, plr->pos.x, plr->pos.y, tmp);
    add_resp(serv->game, ret, GRAPHIC);
    free(tmp);
    free(ret);
    return (0);
}

int pex_evnt(t_server *serv, t_player *plr)
{
    char *ret;
    
    if ((ret = malloc(sizeof(char) * 22)) == NULL)
        return (1);
    sprintf(ret, "pex #%d\n", plr->id);
    add_resp(serv->game, ret, GRAPHIC);
    return (0);
}

char *get_all_ress(t_ressources *ress)
{
    char *str;

    if ((str = malloc(sizeof(char) * 88)))
        return (NULL);
    sprintf(str, "%d %d %d %d %d %d %d",
    ress->linemate, ress->deraumere, ress->sibur,
    ress->mendiane, ress->phiras, ress->thystame, ress->food);
    return (str);
}