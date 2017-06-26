/*
** cmd_tab.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Sun Jun 25 02:51:28 2017 Aurelien
** Last update Sun Jun 25 02:51:36 2017 Aurelien
*/
#include "server.h"

static t_cmd g_cmd_tab[] =
{
    /*
    {"Forward", &forward_cmd, 7},
    {"Right", &right_cmd, 7},
    {"Left", &left_cmd, 7},
    {"Look", &look_cmd, 7},
    {"Inventory", &inventory_cmd, 1},
     // {"Broadcast", &broadcast_cmd, 1}, exception, take 1 arg (text)
    {"Connect_nbr", &connect_nbr_cmd, 0},
    {"Fork", &fork_cmd, 42},
    {"Eject", &eject_cmd, 7},
    // {"Death", &death_cmd, 7}, execption, not a cmd ...
    {"Take", &take_cmd, 7}, // take 1 arg
    {"Set", &set_cmd, 7}, // take 1 arg
    {"Incantation", &incant_cmd, 300}, // not regular...
    */
    {"", 0, 0}
};

int handle_cmd(t_server *server, t_client *client, char *cmd)
{
    int i;
    t_player *player;

    player = client->player;
    i = 0;
    while (g_cmd_tab[i].fct != 0)
    {
        if (strstr(cmd, g_cmd_tab[i].str) != NULL)
        {
            if ((player) == NULL)
                return (2);
            if (player->act_time_left > 0)
                return (3);
            player->act_time_left = g_cmd_tab[i].cycle;
            player->action = strdup(g_cmd_tab[i].str);
            return (0);
        }
        i++;
    }
    // NEED check if cmd is ok
    return (1);
}

int do_cmd(t_server *serv, t_client *cl)
{
    int i;
    int ret;

    i = ret = 0;
    while (g_cmd_tab[i].fct != 0)
    {
        if (strstr(cl->player->action, g_cmd_tab[i].str) != NULL)
        {
            ret = g_cmd_tab[i].fct(game, cl);
            free(cl->player->action);
            cl->player->action = NULL;
            return (ret);
        }
        i++;
    }
    return (404); // cmd not found
}

/*t_player *get_player(t_game *game, int id)
{
    t_plist *tmp;

    tmp = game->player_list;
    while (tmp != NULL)
    {
        if (tmp->player.id == id)
            break;
        tmp = tmp->next;
    }
    return (&(tmp->player));
}*/