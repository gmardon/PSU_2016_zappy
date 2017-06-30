/*
** main.c for zappy_ai in /home/danibo_a/Documents/Epitech/tek2/PSU_2015_zappy/client/src
** 
** Made by Daniboon
** Login   <danibo_a@epitech.net>
** 
** Started on  Wed Jun 15 14:52:00 2016 Daniboon
** Last update Wed Jun 15 14:52:01 2016 Daniboon
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "ai.h"

int main(int ac, char *av[])
{
    t_client    *zappy_client;
    int         rc;

    zappy_client = init_client();
    if (zappy_client == NULL)
        return (perror("Error on initializing s_client structure"),
                EXIT_FAILURE);
    rc = retrieve_options(zappy_client, ac, av);
    if (rc == -1)
        return (perror("Error on retrieving options"), EXIT_FAILURE);
    rc = launch_client(zappy_client);
    if (rc == -1)
        return (perror("Error on lauching client"), EXIT_FAILURE);
    destroy_client(&zappy_client);
    return (EXIT_SUCCESS);
}
