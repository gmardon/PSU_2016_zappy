/*
** my_malloc.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 23:15:21 2017 Aurelien
** Last update Sun Jul  2 23:15:39 2017 Aurelien
*/
#include "zappy.h"

void	*my_malloc(int size)
{
  void	*ref;

  if (!(ref = malloc(size)))
    exit(84);
  return (ref);
}
