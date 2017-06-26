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
    t_playetr *player;

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
    add_resp(game, resp, player->id);
    free(resp);
    return (0);
}
