#include "server.h"

void send_message(t_client *client, char *msg, ...)
{
    char *content;
    int len;
    va_list args;

	if (client->fd)
	{
        va_start(args, msg);
        len = vasprintf(&content, msg, args);
        printf("< %s", content);
        write(client->fd, content, len);
        va_end(args);
    }
}

void close_client(t_client *client)
{
    if (client->fd != -1)
	    close(client->fd);

	printf("Client disconnected <%s:%d>\n",
        get_client_addr(client->in), get_client_port(client->in));
	exit(0);
}

void handle_client(t_server *server, t_client *client)
{
	char *buffer;

	printf("New client connected from <%s:%d>\n",
        get_client_addr(client->in), get_client_port(client->in));
    send_message(client, "WELCOME\r");
    while (42)
	{
        buffer = get_next_line(client->fd);
		if (buffer)
		{
            printf("> %s\n", buffer);
            if (client->team_id == -1)
            {
                if (strcmp(buffer, server->configuration->team1_name) == 0)
                {
                    client->team_id = 1;
                }
                else if (strcmp(buffer, server->configuration->team2_name) == 0)
                {
                    client->team_id = 2;
                } 
                else 
                {
                    send_message(client, "ko");
                    close_client(client);
                }
            }
            /*if (!handle_command(buffer, client))
            {
                send_message(client, "500 Unknown command.\r\n");
            }*/
		}
		else
			close_client(client);
	}
}