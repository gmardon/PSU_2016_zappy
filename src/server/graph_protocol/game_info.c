/*
** game_info.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/graph_protocol
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Tue Jun 27 20:11:21 2017 Aurelien
** Last update Tue Jun 27 20:11:27 2017 Aurelien
*/
#include "server.h"

int sgt_evnt(t_server *serv)
{
    char *ret;

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