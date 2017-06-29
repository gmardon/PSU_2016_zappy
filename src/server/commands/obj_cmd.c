/*
** obj_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Sun Jun 25 23:12:58 2017 Aurelien
** Last update Sun Jun 25 23:13:04 2017 Aurelien
*/
#include "server.h"

int inventory_cmd(t_server *serv, t_client *cl)
{
    char *resp;
    t_player *player;

    if ((resp = malloc(sizeof(char) * 444)) == NULL)
        return (1);
    if ((player = cl->player) == NULL)
        return (2);
    sprintf(resp, "[linemate %d", player->ress.linemate);
    sprintf(resp, "%s, deraumere %d", resp, player->ress.deraumere);
    sprintf(resp, "%s, sibur %d", resp, player->ress.sibur);
    sprintf(resp, "%s, mendiane %d", resp, player->ress.mendiane);
    sprintf(resp, "%s, phiras %d", resp, player->ress.phiras);
    sprintf(resp, "%s, thystame %d", resp, player->ress.thystame);
    sprintf(resp, "%s, food %d]\n", resp, player->ress.food);
    add_resp(serv->game, resp, player->id);
    free(resp);
    return (0);
}

int set_cmd(t_server *serv, t_client *cl)
{
    t_ressources *re;
    int *obj;
    char *str;

    re = &(cl->player->ress);
    if ((str = strstr(cl->player->action, "Set")) == NULL)
        return (666);
    str += (uintptr_t) 4;
    while (*str == ' ')
        str += (uintptr_t) 1;
    if ((obj = get_ress_by_name(re, str)) == NULL || *obj <= 0)
    {
        add_resp(serv->game, "ko\n", cl->player->id);
        return (404); // obj not found
    }
    *obj -= 1;
    re = &(serv->game->map[cl->player->pos.x][cl->player->pos.y].ress);
    obj = get_ress_by_name(re, str); // can't return NULL (i hope)
    *obj += 1;
    add_resp(serv->game, "ok\n", cl->player->id);
    return (0);
}

int take_cmd(t_server *serv, t_client *cl)
{
    t_ressources *re;
    int *obj;
    char *str;

    re = &(serv->game->map[cl->player->pos.x][cl->player->pos.y].ress);
    printf("Take: cl.player.Action = %s\n", cl->player->action);
    if ((str = strstr(cl->player->action, "Take")) == NULL)
        return (666);
    printf("Take: str_before = %s\n", str);
    str += (uintptr_t) 4;
    while (*str == ' ')
        str += (uintptr_t) 1;
    if ((obj = get_ress_by_name(re, str)) == NULL || *obj <= 0)
    {
        printf("Take: parsed str = %s\n", str);
        add_resp(serv->game, "ko\n", cl->player->id);
        return (404); // obj not found
    }
    *obj -= 1;
    re = &(cl->player->ress);
    obj = get_ress_by_name(re, str); // can't return NULL (i hope)
    *obj += 1;
    add_resp(serv->game, "ok\n", cl->player->id);

    char *tmp;
    if ((tmp = get_all_ress(&(serv->game->map[cl->player->pos.x][cl->player->pos.y].ress))) == NULL)
        return (1);
    printf("Take: tile: x=%d y=%d, %s\n");
    free(tmp);
    return (0);
}

int *get_ress_by_name(t_ressources *ress, char *name)
{
    int *ret;

    ret = NULL;
    if (strstr(name, "linemate") != NULL)
        ret = &(ress->linemate);
    else if (strstr(name, "deraumere") != NULL)
        ret = &(ress->deraumere);
    else if (strstr(name, "sibur") != NULL)
        ret = &(ress->sibur);
    else if (strstr(name, "mendiane") != NULL)
        ret = &(ress->mendiane);
    else if (strstr(name, "phiras") != NULL)
        ret = &(ress->phiras);
    else if (strstr(name, "thystame") != NULL)
        ret = &(ress->thystame);
    else if (strstr(name, "food") != NULL)
        ret = &(ress->food);
    return (ret);
}