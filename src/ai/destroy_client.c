/*
** destroy_client.c for zappy_ai in /home/danibo_a/Documents/Epitech/tek2/PSU_2015_zappy/client
**
** Made by Daniboon
** Login   <danibo_a@epitech.net>
**
** Started on  Wed Jun 15 16:51:00 2016 Daniboon
** Last update Fri Jun 24 16:46:56 2016 Daniboon
*/

#include <stdlib.h>
#include <unistd.h>

#include "ai.h"

/*
**  Juste des free
*/

//////////// TODO Conditionnal jump dans free de team

void
destroy_client(struct s_client **zappy_client)
{
    close((*zappy_client)->fd);
    free((*zappy_client)->options->team);
    free((*zappy_client)->options->hostname);
    free((*zappy_client)->options);
    free(*zappy_client);
}
