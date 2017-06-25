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

int new_player(t_game *game, char *team_name, int id)
{
    t_plist *tmp;
    t_plist *new;

    tmp = game->player_list;
    while (tmp != NULL && tmp->next != NULL)
        tmp = tmp->next;
    if ((new = malloc(sizeof(t_plist))) == NULL)
        return (1);
    new->player.id = id;
    //new->player.team = team_name;
    new->player.lvl = 1;
    new->player.x = 0;
    new->player.y = 0;
    new->player.ress = init_ress();
    new->player.ress.food = 9;
    new->player.time_left = 126;
    new->player.act_time_left = 0;
    if (tmp == NULL)
        game->player_list = new;
    else
        tmp->next = new;
    return (0);
}

int del_player(t_game *game, int player_id)
{
    t_plist *tmp;
    t_plist *old;

    tmp = game->player_list;
    old = NULL;
    while (tmp != NULL)
    {
        if (tmp->player.id == player_id)
            break;
        old = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return (1);
    if (old == NULL)
        game->player_list = tmp->next;
    else
        old->next = tmp->next;
    // free(tmp->player.team) ?
    free(tmp);
    return (0);
}