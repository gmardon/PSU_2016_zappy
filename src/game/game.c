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
#include <sys/time.h>
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
    struct timeval elapsed;
    char *resp;

    resp = NULL;
    if (cmd != NULL) // also need to know the player who sended the cmd
        resp = do_cmd(cmd);
    if (calc_elapsed((1000000 / game->freq)))
        do_one_cycle(game);
    return (resp);
}

int do_one_cycle(t_game *game)
{
    // boucler sur les joueurs
    //      decr tt les timer des joueurs
    // ???
    return (0);
}

int calc_elapsed(double unit)
{
    static char bool_old_set = 0;
    static struct timeval old_tv = {0, 0};
    struct timeval tv;
    struct timeval elapsed;

    if (bool_old_set == 0)
    {
        gettimeofday(&old_tv, NULL);
        bool_old_set = 1;
    }
    gettimeofday(&tv, NULL); // if the ret is not 0 -> err
    if ((elapsed.tv_sec = tv.tv_sec - old_tv.tv_sec) > 0
        && elapsed.tv_sec--)
        elapsed.tv_usec = tv.tv_usec + (1000000 - old_tv.tv_usec);
    else if (tv.tv_sec - old_tv.tv_sec == 0)
        elapsed.tv_usec = tv.tv_usec - old_tv.tv_usec;
    if (elapsed.tv_usec > unit
        || elapsed.tv_sec > 0)
    {
        gettimeofday(&old_tv, NULL);
        return (1);
    }
    return (0);
}
