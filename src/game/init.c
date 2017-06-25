/*
** init.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Thu Jun 22 20:02:35 2017 Aurelien
** Last update Thu Jun 22 20:02:41 2017 Aurelien
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

/*
** clientNb is the number of client auhtorized per team
*/
t_game *init_game(int width, int height, int clientsNb)
{
    t_game *game;
    size_t i;

    if ((game = malloc(sizeof(t_game))) == NULL)
        return (NULL);
    game->width = width;
    game->height = height;
    if ((game->map = malloc(sizeof(t_tile *) * width)) == NULL)
        return (NULL);
    i = 0;
    while (i < width)
    {
        if ((game->map[i] = malloc(sizeof(t_tile) * height)) == NULL)
            return (NULL);
        init_tile_tab(game, i);
        i++;
    }
    game->perso_list = NULL;
    game->resp = NULL;
    game->freq = 100;
    return (game);
}

void init_tile_tab(t_game *game, int i)
{
    size_t j;

    j = 0;
    while (j < game->height)
    {
        game->map[i][j].ress = init_ress();
        j++;
    }
}

t_ressources init_ress()
{
    t_ressources ress;

    ress.linemate = 0;
    ress.deraumere = 0;
    ress.sibur = 0;
    ress.mendiane = 0;
    ress.phiras = 0;
    ress.thystame = 0;
    ress.food = 0;
    return (ress);
}