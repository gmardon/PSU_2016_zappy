/*
** listen.c for zappy_ai in /home/danibo_a/Documents/Epitech/tek2/PSU_2015_zappy/client
** 
** Made by Daniboon
** Login   <danibo_a@epitech.net>
** 
** Started on  Sun Jun 26 17:11:14 2016 Daniboon
** Last update Sun Jun 26 17:11:15 2016 Daniboon
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
