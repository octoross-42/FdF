NAME = fdf

SRCS =  src/main.c \
		src/events/events.c \
		src/window_handling/init_window.c \
		src/window_handling/draw.c \
		src/parsing/init_map.c \
		src/parsing/parsing.c \
		src/utils/split.c \
		src/utils/utils.c \
		src/utils/gnl.c \
		src/utils/read_altitude.c \
		src/projections/cubic.c \
		src/projections/parallel.c \
		src/projections/no.c \
		src/projections/isometric.c \

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) -I/usr/include -Iinclude/ -Imlx_linux -g3 -O3 -c $< -o ${<:.c=.o}	

$(NAME): ${OBJS}
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

