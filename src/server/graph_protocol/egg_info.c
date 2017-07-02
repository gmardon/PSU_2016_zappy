/*
** egg_info.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/graph_protocol
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Sun Jul  2 20:59:27 2017 Aurelien
** Last update Sun Jul  2 20:59:34 2017 Aurelien
*/
#include "server.h"

int all_enw_evnt(t_server *serv)
{
    t_egg_list *tmp;

    tmp = serv->game->egg;
    while (tmp != NULL)
    {
        enw_evnt(serv, tmp);
        tmp = tmp->next;
    }
    return (0);
}

int enw_evnt(t_server *serv, t_egg_list *egg)
{
    char *ret;

    ret = my_malloc(sizeof(char) * 111);
    sprintf(ret, "enw #%d #%d %d %d\n", egg->id, egg->plr_id,
        egg->pos.x, egg->pos.y);
    add_resp(serv->game, ret, GRAPHIC);
    free(ret);
    return (0);
}