/*
** init_client.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:27:24 2017 Julien Nabti
** Last update Fri Jun 30 17:28:56 2017 Julien Nabti
*/


#include <stdlib.h>
#include <string.h>

#include "ai.h"

/*
**  Initialisation en mémoire de la structure
**  s_client utilisée
*/

struct s_client *init_client()
{
    t_client    *zappy_client;

    zappy_client = malloc(sizeof(struct s_client));
    if (zappy_client == NULL)
        return (NULL);
    zappy_client->options = malloc(sizeof(struct s_opt));
    if (zappy_client->options == NULL)
    {
        free(zappy_client);
        return (NULL);
    }
    zappy_client->options->port = 4242;
    zappy_client->options->hostname = strdup("127.0.0.1");
    zappy_client->options->team = strdup("none");
    if (zappy_client->options->hostname == NULL ||
        zappy_client->options->team == NULL)
        {
            free(zappy_client->options);
            free(zappy_client);
            return (NULL);
        }
    return (zappy_client);
}
