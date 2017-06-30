/*
** main.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:28:48 2017 Julien Nabti
** Last update Fri Jun 30 17:28:49 2017 Julien Nabti
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
