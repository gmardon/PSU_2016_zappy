/*
** move_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Sun Jun 25 23:13:59 2017 Aurelien
** Last update Sun Jun 25 23:14:01 2017 Aurelien
*/
#include "server.h"

int forward_cmd(t_server *serv, t_client *cl)
{
    t_player *plr;

    if ((plr = cl->player) == NULL)
        return (1);
    plr->pos.x += plr->dir.x;
    plr->pos.y += plr->dir.y;
    check_pos(serv->game, plr);
    add_resp(serv->game, "ok\n", cl->fd);
    return (0);
}

int right_cmd(t_server *serv, t_client *cl)
{
    t_player *plr;

    if ((plr = cl->player) == NULL)
        return (1);
    if (plr->dir.x != 0)
    {
        plr->dir.y = plr->dir.x;
        plr->dir.x = 0;
    }
    else if (plr->dir.y != 0)
    {
        plr->dir.x = (plr->dir.y * -1);
        plr->dir.y = 0;
    }
    add_resp(serv->game, "ok\n", cl->fd);    
    ppo_evnt(serv, cl->player);
    return (0);
}

int left_cmd(t_server *serv, t_client *cl)
{
    t_player *plr;

    if ((plr = cl->player) == NULL)
        return (1);
    if (plr->dir.x != 0)
    {
        plr->dir.y = (plr->dir.x * -1);
        plr->dir.x = 0;
    }
    else if (plr->dir.y != 0)
    {
        plr->dir.x = plr->dir.y;
        plr->dir.y = 0;
    }
    add_resp(serv->game, "ok\n", cl->fd);
    ppo_evnt(serv, cl->player);
    return (0);
}

void check_pos(t_game *game, t_player *plr)
{
    if (plr->pos.x >= game->width)
        plr->pos.x = 0;
    else if (plr->pos.x < 0)
        plr->pos.x = game->width - 1;
    if (plr->pos.y >= game->height)
        plr->pos.y = 0;
    else if (plr->pos.y < 0)
        plr->pos.y = game->height - 1;
}