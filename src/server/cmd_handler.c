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
    {"Forward", &forward_cmd, 0, 7},
    {"Right", &right_cmd, 0, 7},
    {"Left", &left_cmd, 0, 7},
    /*{"Look", &look_cmd, 7},*/
    {"Inventory", &inventory_cmd, 0, 1},
     // {"Broadcast", &broadcast_cmd, 1}, exception, take 1 arg (text)
    //{"Connect_nbr", &connect_nbr_cmd, 0},
    //{"Fork", &fork_cmd, 42},
    //{"Eject", &eject_cmd, 7},
    {"Death", &death_cmd, &death_cmd_chk, 0},
    {"Take", &take_cmd, &take_cmd_chk, 7}, // take 1 arg
    {"Set", &set_cmd, &set_cmd_chk, 7}, // take 1 arg
    {"Incantation", &incant_cmd, &incant_cmd_chk, 300}, // not regular...
    //{"ppo", &ppo_cmd, 0}, // take 1 arg
    {"", 0, 0, 0}
};

int handle_cmd(t_server *server, t_client *client, char *cmd)
{
    int i;
    t_player *player;

    if ((player = client->player) == NULL)
        return (2);
    i = 0;
    while (g_cmd_tab[i].fct != 0)
    {
        if (strstr(cmd, g_cmd_tab[i].str) != NULL)
        {
            if (player->act_time_left > 0
                && strstr(cmd, "Death") == NULL)
                return (add_action(client->player, cmd));
            if (g_cmd_tab[i].check != 0
            && g_cmd_tab[i].check(server, player, cmd))
                return (set_next_action(server, client));
            player->act_time_left = g_cmd_tab[i].cycle;
            player->action = strdup(cmd);
            return (0);
        }
        i++;
    }
    // to replace to "ko"
    add_resp(server->game, "404 command not found\n", client->player->id);
    return (404);
}

int do_cmd(t_server *serv, t_client *cl)
{
    int i;
    int ret;

    i = ret = 0;
    if (cl->player->action == NULL)
        return (1);
    while (g_cmd_tab[i].fct != 0)
    {
        if (strstr(cl->player->action, g_cmd_tab[i].str) != NULL)
        {
            ret = g_cmd_tab[i].fct(serv, cl);
            free(cl->player->action);
            cl->player->action = NULL;
            set_next_action(serv, cl);
            return (ret);
        }
        i++;
    }
    return (404); // cmd not found
}

int set_next_action(t_server *serv, t_client *cl)
{
    char *tmp;

    if ((tmp = pop_action(cl->player)) != NULL)
    {
        handle_cmd(serv, cl, tmp);
        free(tmp);
    }
    else
    {
        cl->player->action = NULL;
        cl->player->act_time_left = 0;
    }
    return (4);
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