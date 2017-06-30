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

t_player *new_player(t_server *serv, int id, int team_id)
{
    t_player *new;

    if ((new = malloc(sizeof(t_player))) == NULL)
        return (NULL);
    new->id = id;
    new->lvl = 1;
    new->team_id = team_id;
    new->pos.x = rand() % serv->configuration->world_width;
    new->pos.y = rand() % serv->configuration->world_height;
    new->dir.x = 0;
    new->dir.y = -1;
    new->ress = init_ress(0);
    new->ress.food = 9;
    new->time_left = 126;
    new->act_time_left = 0;
    new->action = NULL;
    new->action_list = NULL;
    return (new);
}

void del_player(t_player *player)
{
    if (player->action != NULL)
        free(player->action);
    free(player);
}