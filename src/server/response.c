/*
** response.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Sun Jun 25 02:31:57 2017 Aurelien
** Last update Sun Jun 25 02:32:02 2017 Aurelien
*/
#include "server.h"

int add_resp(t_game *game, char *resp, int player_id)
{
    t_rlist *tmp;
    t_rlist *new;

    tmp = game->resp;
    while (tmp != NULL && tmp->next != NULL)
        tmp = tmp->next;
    if ((new = malloc(sizeof(t_plist))) == NULL)
        return (1);
    new->id = player_id;
    new->msg = strdup(resp);
    new->next = NULL;
    if (tmp == NULL)
        game->resp = new;
    else
        tmp->next = new;
    return (0);
}

int del_resp(t_game *game, t_rlist *node)
{
    t_rlist *tmp;
    t_rlist *old;

    tmp = game->resp;
    old = NULL;
    while (tmp != NULL)
    {
        if (tmp == node)
            break;
        old = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return (1);
    if (old == NULL)
        game->resp = tmp->next;
    else
        old->next = tmp->next;
    free(tmp->msg);
    free(tmp);
    return (0);
}