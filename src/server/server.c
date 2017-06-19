#include "server.h"

t_client *alloc_new_client(int socket, struct sockaddr_in in, t_server *server)
{
	t_client *client;
	unsigned long ulMode; 

	ulMode = 1;
	client = my_malloc(sizeof(t_client));
	client->fd = socket;
	//int opt = 1;
	//ioctl(socket, FIONBIO, &opt);
	fcntl(socket, F_SETFL, O_NONBLOCK);

	client->in = in;
	client->team_id = -1;
	//client->server = server;
	return (client);
}

t_client *accept_client(t_server *server)
{
	t_client *client;
	socklen_t length;
	int socket;
	struct sockaddr_in in;

	length = sizeof(in);
	if ((socket = accept(server->fd, (struct sockaddr *)&in, &length)) == -1)
		my_error("Can't accept one client connection", -1);
	else
	{
		if (!(client = alloc_new_client(socket, in, server)))
			return;
			
		handle_client(client);
		return (client);
	}
}

t_server *get_socket(int port)
{
	t_server *server;
	int opt;

	opt = TRUE;
	server = (t_server *)my_malloc(sizeof(struct s_server));
	if ((server->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		my_error("Can't create socket", -1);
	server->in.sin_family = AF_INET;
	server->in.sin_addr.s_addr = INADDR_ANY;
	server->in.sin_port = htons(port);
	bzero(&(server->in.sin_zero), 8);
	if ((setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))) < 0)
		my_error("Can't allow multiple connection on socket", -1);
	if ((bind(server->fd, (struct sockaddr *)&server->in, sizeof(server->in))) < 0)
		my_error("Can't bind socket", -1);
	if ((listen(server->fd, 10)) == -1)
		my_error("Can't listen the socket", -1);
	fcntl(server->fd, F_SETFL, O_NONBLOCK);
	return (server);
}

t_server *create_server(t_configuration *config)
{
	t_server *server;

	server = get_socket(config->port);
	server->configuration = config;
	server->max_clients = config->client_per_team * 2;
	server->clients = calloc(server->max_clients + 1, sizeof(t_client));
	server->clients[server->max_clients + 1].fd = -1;
	FD_ZERO(&server->master);
	FD_SET(server->fd, &server->master);
	return (server);
}

void handle_io_connection(t_client *client, t_server *server)
{
	printf("new io connection\n");
	char *buffer;
	int rc;
	int bytes_available;
	int len;

	buffer = my_malloc(BUFFER_SIZE);
	memset(buffer, 0, BUFFER_SIZE);
	rc = recv(client->fd, buffer, sizeof(buffer), 0);
	if (rc < 0)
	{
		if (errno != EWOULDBLOCK)
		{
			FD_CLR(client->fd, &server->master);
			close_client(client);
		}
		return;
	}

	/**********************************************/
	/* Check to see if the connection has been    */
	/* closed by the client                       */
	/**********************************************/
	if (rc == 0)
	{
		FD_CLR(client->fd, &server->master);
		close_client(client);
		return;
	}

	/**********************************************/
	/* Data was received                          */
	/**********************************************/
	len = rc;
	printf("  %d bytes received\n", len);


	//buffer = my_malloc(BUFFER_SIZE);
	//memset(buffer, 0, BUFFER_SIZE);
	
	/*
	buffer = get_next_line(client->fd);
	if (buffer)
    {
		printf("receive %s\n", buffer);
	}
	else
	{
		printf("Disconnected\n");
		FD_CLR(client->fd, &server->master);
		client->fd = 0;
		//remove_connection(user, serv);
	}*/
}

void start_server(t_server *server)
{
	int max;
	int index;
	fd_set read_fds;
	t_client *client;

	max = server->fd;
	while (TRUE)
	{
		read_fds = server->master;
		if (select(max + 1, &server->master, NULL, NULL, 0) == -1)
			my_error("select", -1);
		if (FD_ISSET(server->fd, &server->master))
		{
			client = accept_client(server);
			FD_SET(client->fd, &server->master);
			if (client->fd > max)
				max = client->fd;
			index = 0;
			while (server->clients[index].fd && index < server->max_clients)
				index++;
			printf("index: %i\n", index);

			if (index > server->max_clients)
			{
				// cannot connect
				send_message(client, "MAX USER REACHED\n");
				close_client(client);
			}
			else
			{
				printf("set new user at index: %i\n", index);
				server->clients[index] = *client;
			}
		}
		index = 0;
		while (server->clients[index].fd && index < server->max_clients)
		{
			printf("fd: %i\n", server->clients[index].fd);
			if (FD_ISSET(server->clients[index].fd, &server->master))
			{
				handle_io_connection(&server->clients[index], server);
			}
			index++;
		}
	}
	/*int max_clients = server->configuration->client_per_team * 2;
	t_client *clients;
	
	clients = calloc(max_clients + 1, sizeof(t_client));//[max_clients];
	clients[max_clients + 1].fd = -42;
	int fd_max;
	fd_set fd_read;
	fd_set fd_write;
	printf("start on port %d, waiting for connections...\n", server->configuration->port);

	while (1)
    {
      fd_max = my_fd_set_list(clients, &fd_read, &fd_write);
      if (!my_select(fd_max, &fd_read, &fd_write))
		my_fd_isset(clients, &fd_read, &fd_write);
    }/*
	int max_clients = server->configuration->client_per_team * 2;
	t_client clients[max_clients];
    int master_socket , addrlen , new_socket , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;
      
    char *buffer;  //data buffer of 1K
      
    //set of socket descriptors
    fd_set readfds;
    for (i = 0; i < max_clients; i++) 
        clients[i].fd = -1;
	printf("start on port %d, waiting for connections...\n", server->configuration->port);
    while(TRUE) 
    {
        //clear the socket set
        FD_ZERO(&readfds);
  
        //add master socket to set
        FD_SET(server->fd, &readfds);
        max_sd = server->fd;
         
        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
            sd = clients[i].fd;
             
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET(sd , &readfds);
             
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }
  
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select(max_sd + 1, &readfds , NULL , NULL , NULL);
        if ((activity < 0) && (errno != EINTR)) 
            printf("select error");
        if (FD_ISSET(server->fd, &readfds)) 
		{
			for (i = 0; i < max_clients; i++) 
            {
                if( clients[i].fd == -1 )
                {
					clients[i] = *accept_client(server);
				}
			}
		}
			
        for (i = 0; i < max_clients; i++) 
        {
            sd = clients[i].fd;
            if (FD_ISSET(sd, &readfds)) 
            {
				printf("recv data\n");
				buffer = get_next_line(sd);
				if (buffer)
					handle_client_message(&clients[i], buffer);
				else
				{
					close_client(clients[i]);
					clients[i].fd = -1;
				}
            }
        }
		printf("while\n");
    }
      
    return 0;*/
}