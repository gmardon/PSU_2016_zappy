/*
** listen.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:28:12 2017 Julien Nabti
** Last update Fri Jun 30 17:28:13 2017 Julien Nabti
*/


#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "ai.h"

int
listen_cmp(struct s_client *client)
{
    (void)client;
    if (strncmp(read_buffer, "message", 7) == 0)
    {
        // message de broadcast
    }
    return (0);
}
