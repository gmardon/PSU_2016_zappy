NAME_SERVER			=		zappy_server

NAME_CLI			=		zappy_client

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
							src/server/client_list.c \
							src/server/client_utils.c 	\
							src/server/configuration.c \
							src/server/cmd_handler.c    \
							src/server/init.c       \
							src/server/response.c   \
							src/server/player.c     \
							src/server/client_handler.c \
							src/server/select_team.c \
							src/server/action_list.c \
							src/server/commands/map_cmd.c \
							src/server/commands/move_cmd.c \
							src/server/commands/obj_cmd.c \
							src/server/commands/incant_cmd.c \
							src/server/commands/check_cmd.c \
							src/server/commands/look_cmd.c \
							src/server/graph_protocol/game_info.c \
							src/server/graph_protocol/map_info.c \
							src/server/graph_protocol/player_info.c \
							src/server/game.c \
							$(SRC_COMMON)

SRC_CLI				=		src/client/instructions.c \
							src/client/main.c

SRC_AI				=		src/ai/main.c		\
							src/ai/configuration.c \
							src/ai/client.c \
							src/ai/destroy_client.c \
							src/ai/init_client.c \
							src/ai/init.c \
							src/ai/invent.c \
							src/ai/items.c \
							src/ai/lay.c \
							src/ai/listen.c \
							src/ai/move.c \
							src/ai/opt.c \
							src/ai/send.c \
							src/ai/ia.c \
							src/ai/take.c \
							src/ai/go_obj.c \
							$(SRC_COMMON)

OBJ_SERVER			=		$(SRC_SERVER:.c=.o)

OBJ_AI			=		$(SRC_AI:.c=.o)

OBJ_CLI			=		$(SRC_CLI:.c=.o)

CFLAGS			=		-W -Wall -Wextra -g -I./include/ -g

all:			zappy_ai zappy_server

zappy_server:			$(OBJ_SERVER) 
				gcc -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS) -lm

zappy_ai:			$(OBJ_AI)
				gcc -o $(NAME_AI) $(OBJ_AI) $(CFLAGS) -pthread

client:				$(OBJ_CLI)
				gcc -o $(NAME_CLI) $(OBJ_CLI) $(CFLAGS)

clean:
				rm -rf $(OBJ_SERVER)
				rm -rf $(OBJ_AI)

fclean:			clean
				rm -rf $(NAME_SERVER)
				rm -rf $(NAME_AI)

re:			fclean all
