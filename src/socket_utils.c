#include "zappy.h"

void set_non_blocking(int socket)
{
	int opts;

	opts = fcntl(socket, F_GETFL);
	if (opts < 0)
		my_error("fcntl(F_GETFL)", EXIT_FAILURE);
	opts = (opts | O_NONBLOCK);
	if (fcntl(socket, F_SETFL, opts) < 0)
		my_error("fcntl(F_SETFL)", EXIT_FAILURE);
	return;
}