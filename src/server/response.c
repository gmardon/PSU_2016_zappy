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

int send_all_resp(t_server* serv)
{
    t_rlist *tmp;
    t_rlist *old;
    t_client *cl;

    tmp = serv->game->resp;
    while (tmp != NULL)
    {
        if (tmp->id != GRAPHIC)
        {
            if ((cl = get_cl_by_id(serv, tmp->id)) != NULL)
                send_message(cl, tmp->msg);
        }
        else
        {
            if ((cl = get_cl_graph(serv)) != NULL)
                send_message(cl, tmp->msg);
        }
        old = tmp;
        tmp = tmp->next;
        del_resp(serv->game, old);
    }
    return (0);
}

t_client *get_cl_graph(t_server *serv)
{
    t_clist *tmp;
    t_client *cl;

    cl = NULL;
    tmp = serv->client_list;
    while (tmp != NULL)
    {
        if (tmp->client->team_id == GRAPHIC)
            break;
        tmp = tmp->next;
    }
    if (tmp != NULL)
        cl = tmp->client;
    return (cl);
}

int add_resp(t_game *game, char *resp, int player_id)
{
    t_rlist *tmp;
    t_rlist *new;

    tmp = game->resp;
    while (tmp != NULL && tmp->next != NULL)
        tmp = tmp->next;
    if ((new = malloc(sizeof(t_rlist))) == NULL)
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