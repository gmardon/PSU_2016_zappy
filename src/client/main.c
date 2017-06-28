/*
** main.c for  in /home/julienN/PSU_2016_zappy/src/client
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Wed Jun 28 16:00:09 2017 Julien Nabti
** Last update Wed Jun 28 16:03:39 2017 Julien Nabti
*/
#include "client.h"


t_cli	*get_opt(int ac, char **av)
{
  t_cli	*client;
  char opt;

  client = malloc(sizeof(t_cli));
  client->addr = -1;
  client->port = -1;
  memset(&(client->m_addr), 0, sizeof(client->m_addr));
  while ((opt = getopt(ac, av, "p:a:")) != -1)
    {
      if (opt == 'p')
	{
	  client->port = atoi(optarg);
	  if (client->port < 1000)
	    {
	      printf("[!] Can't use port below 1000...\n");
	      return (NULL);
	    }
	  printf("[*] Port set to %d ...\n", client->port);
	}
      else if (opt == 'a')
	{
	  if ((client->addr = optarg) == NULL)
	    {
	      printf("[!] Can't have empty host...\n");
	      return (NULL);
	    }
	  printf("[*] Address set to %s ...\n", client->addr);
	}
      else
	{
	  printf("[!] Unrecognized arg : %c\n", opt);
	  return (NULL);
	}
    }
  return (client);
}

t_cli	*initCli(t_cli *client)
{
  int	i = 1;
  int	status;
  
  if ((client->sock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("[!] Error while creating client socket...\n");
      return (NULL);
    }
  printf("[*] Socket created [%d]...\n", client->sock);
  if (setsockopt(client->sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&i, sizeof(i)) == -1)
    {
      printf("[!] Error while setting socket options...\n");
      return (NULL);
    }
  printf("[*] Socket options set...\n");
  client->m_addr.sin_family = AF_INET;
  client->m_addr.sin_port = htons(client->port);
  if ((status = inet_pton(AF_INET, client->addr, &(client->m_addr.sin_addr)))
      == EAFNOSUPPORT)
    {
      printf("[!] Error while converting ipv4 to ipv6...\n");
      return (NULL);
    }
  if ((status = connect(client->sock, (struct sockaddr *)&(client->m_addr), sizeof(client->m_addr))) == 0)
      printf("[*] Connection established to remote host [%s]...\n", client->addr);
  else
    {
      printf("[!] Couldn't connect to remote host [%s] ...\n", client->addr);
      return (NULL);
    }
  return (client);
}

int	main(int ac, char **av)
{
  t_cli	*client;
  fd_set readfd;
  fd_set writefd;
  fd_set exceptfd;
  char	buff[1024];
  char	*tmp;
  
  printf("[*] Starting client...\n");
  if (ac == 1)
    {
      printf("[!} You must specify a port !\n");
      return (-1);
    }
  if ((client = get_opt(ac, av)) == NULL)
    return (-1);
  if ((client = initCli(client)) == -1)
    return (-1);
  while (42)
    {
      FD_ZERO(&readfd);
      FD_ZERO(&writefd);
      FD_ZERO(&exceptfd);
      FD_SET(STDIN_FILENO, &readfd);
      FD_SET(client->sock, &readfd);
      FD_SET(client->sock, &writefd);
      FD_SET(client->sock, &exceptfd);
      if (select(client->sock + 1, &readfd, &writefd, &exceptfd, NULL) == -1)
	{
	  printf("[!] Select error...\n");
	  return (-1);
	}
      if (FD_ISSET(STDIN_FILENO, &readfd))
	{
	  fgets(buff, BUFF_SIZE - 1, stdin);
	  tmp = strstr(buff, "\n");
	  if (tmp != NULL)
	    *tmp = 0;
	  else
	    buff[BUFF_SIZE - 1] = 0;
	  if (send(client->sock, buff, strlen(buff), 0) < 0)
	    {
	      printf("[!] Error while sending [%s] ...\n", buff);
	      return (-1);
	    }
	}
      else if (FD_ISSET(client->sock, &readfd))
	{
	  int	ret;
	  if ((ret = recv(client->sock, buff, BUFF_SIZE - 1, 0)) < 0)
	    {
	      printf("[!] Error while recieving msg...\n");
	      return (-1);
	    }
	  if (ret == 0)
	    {
	      printf("[*] Connection close by remote host...\n");
	      close (client->sock);
	      return (0);
	    }
	  buff[ret] = 0;
	  printf("[*} Message recieved : [%s] ...\n", buff);
	}
    }
}
