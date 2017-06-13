#include "zappy.h"

void *my_malloc(int size)
{
  void *ref;

  if (!(ref = malloc(size)))
    exit(84);
  return (ref);
}
