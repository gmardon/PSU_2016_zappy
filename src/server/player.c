/*
** player.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Thu Jun 22 23:46:39 2017 Aurelien
** Last update Thu Jun 22 23:46:46 2017 Aurelien
*/
#include "server.h"

t_player *new_player(int id, int team_id)
{
    t_player *new;

    if ((new = malloc(sizeof(t_player))) == NULL)
        return (1);
    new->id = id;
    new->lvl = 1;
    new->team_id = team_id;
    //new->pos = {0, 0}; // generate pos & dir here ?
    //new->dir = {0, -1};
    new->ress = init_ress();
    new->ress.food = 9;
    new->time_left = 126;
    new->act_time_left = 0;
    new->action = NULL;
    return (new);
}

void del_player(t_player *player)
{
    if (player->action != NULL)
        free(player->action);
    free(player);
}