/*
** incant_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server/commands
** 


** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Fri Jun 30 22:54:36 2017 Aurelien
** Last update Fri Jun 30 22:54:41 2017 Aurelien
*/
#include "server.h"

static t_incant_req g_incant_tab[] = 
{
    {1, 1, {1, 0, 0, 0, 0, 0, 0}},
    {2, 2, {1, 1, 1, 0, 2, 0, 0}},
    {3, 2, {2, 0, 1, 0, 2, 0, 0}},
    {4, 4, {1, 1, 2, 0, 1, 0, 0}},
    {5, 4, {1, 2, 1, 3, 0, 0, 0}},
    {6, 6, {1, 2, 3, 0, 1, 0, 0}},
    {7, 6, {2, 2, 2, 2, 2, 1, 0}},
    {0, 0, {0, 0, 0, 0, 0, 0, 0}}
};

int incant_cmd(t_server *serv, t_client *cl)
{
    t_clist *tmp;
    char *resp;

    if ((resp = my_malloc(sizeof(char) * 56)) == NULL)
        return (2);
    if (incant_chk(serv, cl->player))
    {
        sprintf(resp, "Current level: %d\n", (cl->player->lvl + 1));
        tmp = serv->client_list;
        while (tmp != NULL)
        {
            if (tmp->client->player->pos.x == cl->player->pos.x
            && tmp->client->player->pos.y == cl->player->pos.y
            && (tmp->client->player->lvl += 1))
                add_resp(serv->game, resp, tmp->client->player->id);
            tmp = tmp->next;
        }
        return (0);
    }
    add_resp(serv->game, "ko\n", cl->player->id);
    return (1);
}

int incant_cmd_chk(t_server *serv, t_player *plr, char *cmd)
{
    t_clist *tmp;
    t_client *cl;
    int id;

    if (incant_chk(serv, plr) && cmd)
    {
        tmp = serv->client_list;
        while (tmp != NULL)
        {
            cl = tmp->client;
            id = cl->player->id;
            if (cl->player->pos.x == plr->pos.x
            && cl->player->pos.y == plr->pos.y)
                add_resp(serv->game, "Elevation underway\n", id);
            tmp = tmp->next;
        }
        return (0);
    }
    add_resp(serv->game, "ko\n", plr->id);
    return (1);
}

int incant_chk(t_server *serv, t_player *plr)
{
    int nb_plr;
    int i;
    t_ressources map_ress;

    if ((nb_plr = count_plr_pos_lvl(serv, plr)) == 0)
        return (0); // KO
    map_ress = serv->game->map[plr->pos.x][plr->pos.y].ress;
    i = 0;
    while (g_incant_tab[i].lvl != 0)
    {
        if (g_incant_tab[i].lvl == plr->lvl)
        {
            if (g_incant_tab[i].nb_plr != nb_plr)
                return (0); // KO
            if (comp_ress(g_incant_tab[i].ress, map_ress))
                return (1); // ok
            else
                return (0); // KO
        }
        i++;
    }
    return (0); // KO
}

int count_plr_pos_lvl(t_server *serv, t_player *plr)
{
    t_clist *tmp;
    int nb_plr;

    nb_plr = 0;
    tmp = serv->client_list;
    while (tmp != NULL)
    {
        if (tmp->client->player->pos.x == plr->pos.x
        && tmp->client->player->pos.y == plr->pos.y)
        {
            if (tmp->client->player->lvl != plr->lvl)
                return (0);
            nb_plr++;
        }
        tmp = tmp->next;
    }
    return (nb_plr);
}

int comp_ress(t_ressources need_ress, t_ressources map_ress)
{
    if (need_ress.linemate != map_ress.linemate)
        return (0);
    if (need_ress.deraumere != map_ress.deraumere)
        return (0);
    if (need_ress.sibur != map_ress.sibur)
        return (0);
    if (need_ress.mendiane != map_ress.mendiane)
        return (0);
    if (need_ress.phiras != map_ress.phiras)
        return (0);
    if (need_ress.thystame != map_ress.thystame)
        return (0);
    if (need_ress.food != map_ress.food)
        return (0);
    return (1); // ok
}