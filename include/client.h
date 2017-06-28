#ifndef __CLIENT__
#define __CLIENT__

#include "server.h"
#define BUFF_SIZE 1024

typedef	struct s_cli
{
  int	sock;
  int	port;
  char	*addr;
  struct sockaddr_in	m_addr;
}		t_cli;

typedef struct	s_cmdList
{
  char	*mnemo;
  int	nb_arg;
  /* char	type[10]; */
  int	(*fptr)(t_cli *, char **, int);
  int	num;
}	t_cmdList;

int	msz(t_cli *, char **, int);
int	bct(t_cli *, char **, int);
int	tna(t_cli *, char **, int);
int	mct(t_cli *, char **, int);
int	pnw(t_cli *, char **, int);
int	ppo(t_cli *, char **, int);
int	plv(t_cli *, char **, int);
int	pin(t_cli *, char **, int);
int	pbc(t_cli *, char **, int);
int	pex(t_cli *, char **, int);
int	pic(t_cli *, char **, int);
int	pie(t_cli *, char **, int);
int	pfk(t_cli *, char **, int);
int	pdr(t_cli *, char **, int);
int	pgt(t_cli *, char **, int);
int	pdi(t_cli *, char **, int);
int	enw(t_cli *, char **, int);
int	eht(t_cli *, char **, int);
int	ebo(t_cli *, char **, int);
int	edi(t_cli *, char **, int);
int	sgt(t_cli *, char **, int);
int	seg(t_cli *, char **, int);
int	smg(t_cli *, char **, int);
int	suc(t_cli *, char **, int);
int	sbp(t_cli *, char **, int);

extern	int(*fptr[25])(t_cli *, char **, int );

#endif
