/*
** eject_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/commands
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Sun Jul  2 03:03:10 2017 Aurelien
** Last update Sun Jul  2 03:03:15 2017 Aurelien
*/
#include "server.h"

int eject_cmd(t_server *serv, t_client *cl)
{
    t_clist *tmp;
    char *resp;
    int direction;

    tmp = serv->client_list;
    direction = 0;
    pex_evnt(serv, cl->player);
    while (tmp != NULL)
    {
        if (tmp->client->player->pos.x == cl->player->pos.x
        && tmp->client->player->pos.y == cl->player->pos.y
        && tmp->client != cl)
        {
            direction = do_eject(serv, cl->player, tmp->client->player);
            resp = my_malloc(sizeof(char) * 33);
            sprintf(resp, "eject: %d\n", direction);
            add_resp(serv->game, resp, tmp->client->player->id);
            free(resp);
        }
        tmp = tmp->next;
    }
    if (direction)
        return (add_resp(serv->game, "ok\n", cl->player->id));
    else
        return (add_resp(serv->game, "ko\n", cl->player->id));
}

int do_eject(t_server *serv, t_player *plr, t_player *tgt)
{
    int direction;

    tgt->pos.x += plr->dir.x;
    tgt->pos.y += plr->dir.y;
    ppo_evnt(serv, plr);
    direction = 0;
    if ((direction = eject_dir_test(plr, tgt)))
        return (direction);
    else if (tgt->dir.x != 0)
    {
        if (tgt->dir.x == plr->dir.y)
            direction = 7;
        else
            direction = 3;
    }
    else if (tgt->dir.y != 0)
    {
        if (tgt->dir.y == plr->dir.x)
            direction = 3;
        else
            direction = 7;
    }
    return (direction);
}

int eject_dir_test(t_player *plr, t_player *tgt)
{
    int direction;

    direction = 0;
    if (tgt->dir.x != 0 && plr->dir.x != 0)
    {
        if (tgt->dir.x == plr->dir.x)
            direction = 1;
        else
            direction = 5;
    }
    else if (tgt->dir.y != 0 && plr->dir.y != 0)
    {
        if (tgt->dir.y == plr->dir.y)
            direction = 1;
        else
            direction = 5;
    }
    return (direction);
}

int eject_cmd_chk(t_server *serv, t_player *plr, char *cmd)
{
    t_clist *tmp;

    tmp = serv->client_list;
    if (cmd == NULL)
        return (666);
    while (tmp != NULL)
    {
        if (tmp->client->player->pos.x == plr->pos.x
        && tmp->client->player->pos.y == plr->pos.y)
            break;
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        add_resp(serv->game, "ko\n", plr->id);
        return (1);
    }
    return (0);
}