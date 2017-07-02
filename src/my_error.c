/*
** my_error.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 23:15:02 2017 Aurelien
** Last update Sun Jul  2 23:15:14 2017 Aurelien
*/
#include "zappy.h"

void my_error(char *msg, int exit_code)
{
  printf("%s\n", msg);
  if (exit_code != 0)
    exit(exit_code);
}
