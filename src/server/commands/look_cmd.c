/*
** look_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/commands
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Sat Jul  1 23:12:35 2017 Aurelien
** Last update Sat Jul  1 23:12:40 2017 Aurelien
*/
#include "server.h"

int look_cmd(t_server *serv, t_client *cl)
{
    char *resp;
    char *tmp;
    int lvl;

    resp = strdup("[");
    tmp = get_one_tile(serv, cl->player->pos, 1);
    resp = my_strcat(resp, tmp, NULL);
    free(tmp);
    lvl = 1;
    while (lvl <= cl->player->lvl)
    {
        tmp = get_one_line(serv, cl, lvl);
        resp = my_strcat(resp, tmp, NULL);
        free(tmp);
        lvl++;
    }
    resp = my_strcat(resp, "]\n\0", NULL);
    add_resp(serv->game, resp, cl->player->id);
    free(resp);
    return (0);
}

char *get_one_line(t_server *serv, t_client *cl, int lvl)
{
    t_position pos;
    t_direction dir;
    char *resp;
    char *tmp;
    int i;

    resp = NULL;
    pos = cl->player->pos;
    dir = cl->player->dir;
    get_init_pos(serv, &pos, &dir, lvl);
    i = -1;
    while (++i < ((lvl * 2) + 1))
    {
        tmp = get_one_tile(serv, pos, 0);
        if (resp != NULL && (resp = my_strcat(resp, tmp, NULL)))
            free(tmp);
        else
            resp = tmp;
        pos.x -= dir.x * lvl;
        pos.y -= dir.y * lvl;
        check_pos(serv->game, &pos);
    }
    return (resp);
}

char *get_one_tile(t_server *serv, t_position pos, int first)
{
    char *resp;
    char *tmp;

    if (first)
        resp = strdup("");
    else
        resp = strdup(",");
    if ((tmp = get_tile_plr(serv, pos, first)) != NULL)
    {
        resp = my_strcat(resp, tmp, NULL);
        free(tmp);
    }
    if ((tmp = get_tile_ress(serv, pos)) != NULL)
    {
        resp = my_strcat(resp, tmp, NULL);
        free(tmp);
    }
    return (resp);
}

char *get_tile_plr(t_server *serv, t_position pos, int first)
{
    t_clist *tmp;
    char *ret;

    tmp = serv->client_list;
    ret = NULL;
    while (tmp != NULL)
    {
        if (tmp->client->player != NULL)
        {
            if (tmp->client->player->pos.x == pos.x
            && tmp->client->player->pos.y == pos.y)
            {
                if (ret == NULL && first == 0)
                    ret = strdup(" player");
                else if (ret == NULL && first)
                    ret = strdup("player");
                else
                    ret = my_strcat(ret, " player", NULL);
            }
        }
        tmp = tmp->next;
    }
    return (ret);
}

char *get_tile_ress(t_server *serv, t_position pos)
{
    char *ret;
    char *tmp;
    int count;
    t_ressources ress;

    ress = serv->game->map[pos.x][pos.y].ress;
    count = 0;
    ret = NULL;
    while (42)
    {
        if ((tmp = get_next_ress(&ress)) == NULL)
            break;
        if (ret != NULL)
            ret = my_strcat(ret, " ", &count);
        else
            ret = strdup(" ");
        ret = my_strcat(ret, tmp, &count);
        free(tmp);
    }
    return (ret);
}