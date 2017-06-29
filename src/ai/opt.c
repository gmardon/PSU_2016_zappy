/*
** opt.c for zappy_ai in /home/danibo_a/Documents/Epitech/tek2/PSU_2015_zappy/client/src
**
** Made by Daniboon
** Login   <danibo_a@epitech.net>
**
** Started on  Wed Jun 15 15:06:13 2016 Daniboon
** Last update Thu Jun 16 17:22:46 2016 quentin quero
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "ai.h"

static int  get_port(struct s_client *, char *);
static int  get_hostname(struct s_client *, char *);
static int  get_team(struct s_client *, char *);

/*
**  parsing des arguments de commande
**
**  argstr : chaine composée des caractères d'option possibles
**  ftab : tableau de pointeurs sur fonctions utilisé pour éviter
**  une fôret de if/else if;
**
*/

static const char   *argstr = "nph";
static int (*ftab[3])(struct s_client *, char *) = {
    &get_team,
    &get_port,
    &get_hostname
};

static int
get_port(struct s_client * receiver,
         char * arg)
{
    receiver->options->port = atoi(arg);
    if (receiver->options->port < 0)
        return (perror("Invalid port"), -1);
    return (0);
}

static int
get_hostname(struct s_client * receiver,
             char * name)
{
    free(receiver->options->hostname);
    receiver->options->hostname = strdup(name);
    if (receiver->options->hostname == NULL)
        return (perror("Error on malloc"), -1);
    return (0);
}

static int
get_team(struct s_client * receiver,
         char * name)
{
    free(receiver->options->team);
    receiver->options->team = strdup(name);
    if (receiver->options->team == NULL)
        return (perror("Error on malloc"), -1);
    return (0);
}

static int
get_index(int c)
{
    int i;

    i = 0;
    while (argstr[i])
    {
        if (argstr[i] == c)
            return (i);
        ++i;
    }
    return (-1);
}

/*
**  Utilisation de getopt
*/

int
retrieve_options(struct s_client * receiver,
                 int ac,
                 char * av[])
{
    int opt;
    int i;
    int rc;

    while ((opt = getopt(ac, av, argstr)) != -1)
    {
        i = get_index(opt);
        if (i == -1)
            return (-1);
        rc = ftab[i](receiver, av[optind]);
        if (rc == -1)
            return (-1);
    }
    return (0);
}
