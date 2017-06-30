/*
** destroy_client.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:27:14 2017 Julien Nabti
** Last update Fri Jun 30 17:27:14 2017 Julien Nabti
*/


#include <stdlib.h>
#include <unistd.h>

#include "ai.h"

/*
**  Juste des free
*/

//////////// TODO Conditionnal jump dans free de team

void destroy_client(struct s_client **zappy_client)
{
    close((*zappy_client)->fd);
    free((*zappy_client)->options->team);
    free((*zappy_client)->options->hostname);
    free((*zappy_client)->options);
    free(*zappy_client);
}
