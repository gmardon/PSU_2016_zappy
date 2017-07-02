#ifndef _ZAPPY_H_
# define _ZAPPY_H_
# include <stdlib.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdarg.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <string.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <fcntl.h>
# include <dirent.h>
# define _GNU_SOURCE
# include <stdio.h>
# define TRUE 1
# define FALSE 0
# define __UNUSED__ __attribute__((unused))
# define BUFFER_SIZE 2048

void my_error(char *msg, int exit_code);
char *get_next_line(const int fd);
void *my_malloc(int size);
void set_non_blocking(int socket);
#endif
