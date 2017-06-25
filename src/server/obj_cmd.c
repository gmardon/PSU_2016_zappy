/*
** obj_cmd.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Sun Jun 25 23:12:58 2017 Aurelien
** Last update Sun Jun 25 23:13:04 2017 Aurelien
*/
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

int inventory_cmd(t_game *game, t_perso *perso)
{
    char *resp;

    if ((resp = malloc(sizeof(char) * 444)) == NULL)
        return (1);
    sprintf(resp, "[linemate %d", perso->ress.linemate);
    sprintf(resp, "%s, deraumere %d", resp, perso->ress.deraumere);
    sprintf(resp, "%s, sibur %d", resp, perso->ress.sibur);
    sprintf(resp, "%s, mendiane %d", resp, perso->ress.mendiane);
    sprintf(resp, "%s, phiras %d", resp, perso->ress.phiras);
    sprintf(resp, "%s, thystame %d", resp, perso->ress.thystame);
    sprintf(resp, "%s, food %d]\n", resp, perso->ress.food);
    add_resp(game, resp, perso->id);
    free(resp);
    return (0);
}
