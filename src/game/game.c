/*
** game.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Wed Jun 21 23:08:35 2017 Aurelien
** Last update Wed Jun 21 23:08:36 2017 Aurelien
*/
#include <unistd.h>
#include <stdlib.h>
#include "game.h"

//main is for exemple of use only
int main()
{
    t_game *game;
    char *cmd;

    int width = 100;
    int height = 100;
    int clientsNb = 5;
    if ((game = init_game(width, height, clientsNb)) == NULL)
        return (84);
    while (1)
    {
        resp = do_game(game, cmd);
        // resp is to be sendedd to the client
        // and all graph_evnt need to be sended to graph monitor
    }
    return (0);
}

char *do_game(t_game *game, char *cmd)
{
    //static time; ?
    char *resp;

    resp = NULL;
    if (cmd != NULL) // also need to know the player who sended the cmd
        resp = do_cmd(cmd);
    /* if sec passed
        do_one_cycle(game); */
    return (resp);
}