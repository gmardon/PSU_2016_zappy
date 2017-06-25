NAME_SERVER			=		zappy_server

NAME_AI				=		zappy_ai

SRC_COMMON			= 		src/my_malloc.c			\
							src/my_error.c			\
							src/my_select.c			\
							src/get_next_line.c		\
							src/socket_utils.c

SRC_SERVER			=		src/server/server.c		\
							src/server/server_socket.c \
							src/server/main.c		\
							src/server/client.c 	\
							src/server/client_utils.c 	\
							src/server/configuration.c \
							$(SRC_COMMON)

SRC_AI				=		src/ai/main.c		\
							src/ai/configuration.c \
							$(SRC_COMMON)

OBJ_SERVER			=		$(SRC_SERVER:.c=.o)

OBJ_AI			=		$(SRC_AI:.c=.o)

CFLAGS			=		-W -Wall -Wextra -g -I./include/ -g

all:			zappy_ai zappy_server

zappy_server:			$(OBJ_SERVER)
				gcc -I./src/server/ -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS) -lm

zappy_ai:			$(OBJ_AI)
				gcc -I./src/ai/ -o $(NAME_AI) $(OBJ_AI) $(CFLAGS) 

clean:
				rm -rf $(OBJ_SERVER)
				rm -rf $(OBJ_AI)

fclean:			clean
				rm -rf $(NAME_SERVER)
				rm -rf $(NAME_AI)

re:			fclean all