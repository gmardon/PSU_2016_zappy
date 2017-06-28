/*
** instructions.c for  in /home/julienN/PSU_2016_zappy/src/client
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Wed Jun 28 16:00:22 2017 Julien Nabti
** Last update Wed Jun 28 16:21:21 2017 Julien Nabti
*/

#include "client.h"

t_cmdList	cmd_tab[] =
  {
    {"msz", 2, &msz, 0},
    {"bct", 9, &bct, 1},
    {"tna", 1, &tna, 2},
    {"mct", -1, &mct, 3},
    {"pnw", 6, &pnw, 4},
    {"ppo", 5, &ppo, 5},
    {"plv", 1 ,&plv, 6},
    {"pin", 9 ,&pin, 7},
    {"pex", 1, &pex, 8},
    {"pbc", 1, &pbc, 9},
    {"pic", 5, &pic, 10},
    {"pie", 3, &pie, 11},
    {"pfk", 1, &pfk, 12},
    {"pdr", 2, &pdr, 13},
    {"pgt", 2, &pgt, 14},
    {"pdi", 1, &pdi, 15},
    {"enw", 4, &enw, 16},
    {"eht", 1, &eht, 17},
    {"ebo", 1, &ebo, 18},
    {"edi", 1, &edi, 19},
    {"sgt", 1, &sgt, 20},
    {"seg", 1, &seg, 21},
    {"smg", 1, &smg, 22},
    {"suc", 0, &suc, 23},
    {"sbp", 0, &sbp, 24},
    {NULL, 0, NULL, 0}
  };

int	(*fptr[25])(t_cli *, char **, int) =
{
  [0] = &msz,
  [1] = &bct,
  [2] = &tna,
  [3] = &mct,
  [4] = &pnw,
  [5] = &ppo,
  [6] = &plv,
  [7] = &pin,
  [8] = &pbc,
  [9] = &pex,
  [10] = &pic,
  [11] = &pie,
  [12] = &pfk,
  [13] = &pdr,
  [14] = &pgt,
  [15] = &pdi,
  [16] = &enw,
  [17] = &eht,
  [18] = &ebo,
  [19] = &edi,
  [20] = &sgt,
  [21] = &seg,
  [22] = &smg,
  [23] = &suc,
  [24] = &sbp,
};

int	msz(t_cli *c, char **args, int nb)
{
  printf("Fct: msz\n");
  return (0);
}



int	bct(t_cli *c, char **args, int nb)
{
  printf("Fct: bct\n");
  return (0);
}

int	tna(t_cli *c, char **args, int nb)
{
  printf("Fct: tna\n");
  return (0);
}

int	mct(t_cli *c, char **args, int nb)
{
  printf("Fct: mct\n");
  return (0);
}

int	pnw(t_cli *c, char **args, int nb)
{
  printf("Fct: pnw\n");
  return (0);
}

int	ppo(t_cli *c, char **args, int nb)
{
  printf("Fct:ppo\n");
  return (0);
}

int	plv(t_cli *c, char **args, int nb)
{
  printf("Fct:plv\n");
  return (0);
}

int	pin(t_cli *c, char **args, int nb)
{
  printf("Fct: pin\n");
  return (0);
}

int	pbc(t_cli *c, char **args, int nb)
{
  printf("Fct: pbc\n");
  return (0);
}

int	pex(t_cli *c, char **args, int nb)
{
  printf("Fct: pex\n");
  return (0);
}

int	pic(t_cli *c, char **args, int nb)
{
  printf("Fct: pic\n");
  return (0);
}

int	pie(t_cli *c, char **args, int nb)
{
  printf("Fct: pie\n");
  return (0);
}

int	pfk(t_cli *c, char **args, int nb)
{
  printf("Fct: pfk\n");
  return (0);
}

int	pdr(t_cli *c, char **args, int nb)
{
  printf("Fct: pdr\n");
  return (0);
}

int	pgt(t_cli *c, char **args, int nb)
{
  printf("Fct: pgt\n");
  return (0);
}

int	pdi(t_cli *c, char **args, int nb)
{
  printf("Fct: pdi\n");
  return (0);
}



int	enw(t_cli *c, char **args, int nb)
{
  printf("Fct: enw\n");
  return (0);
}

int	eht(t_cli *c, char **args, int nb)
{
  printf("Fct: eht\n");
  return (0);
}

int	ebo(t_cli *c, char **args, int nb)
{
  printf("Fct:ebo\n");
  return (0);
}

int	edi(t_cli *c, char **args, int nb)
{
  printf("Fct:edi\n");
  return (0);
}

int	sgt(t_cli *c, char **args, int nb)
{
  printf("Fct:sgt\n");
  return (0);
}

int	seg(t_cli *c, char **args, int nb)
{
  printf("Fct: seg\n");
  return (0);
}

int	smg(t_cli *c, char **args, int nb)
{
  printf("Fct: smg\n");
  return (0);
}

int	suc(t_cli *c, char **args, int nb)
{
  printf("Fct: suc\n");
  return (0);
}



int	sbp(t_cli *c, char **args, int nb)
{
  printf("Fct:sbp\n");
  return (0);
}
