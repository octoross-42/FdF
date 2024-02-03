NAME = fdf

SRCS =  src/main.c \
		src/events/mouse.c \
		src/events/keyboard.c \
		src/events/events.c \
		src/window_handling/init_window.c \
		src/window_handling/draw.c \
		src/parsing/init_map.c \
		src/parsing/parsing.c \
		src/utils/split.c \
		src/utils/utils.c \
		src/utils/gnl.c \
		src/utils/printf.c \
		src/utils/puts.c \
		src/utils/printf_utils.c \
		src/utils/read_altitude.c \
		src/projections/parallel.c \
		src/projections/no.c \
		src/projections/isometric.c \
		src/projections/dimensions.c \
		src/colors/density.c \

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lXext -lX11

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude/ -Imlx_linux -c $< -o ${<:.c=.o}	

$(NAME): ${OBJS}
	$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -L/usr/lib $(MLX_FLAGS) -lm -lz -o $(NAME)

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

