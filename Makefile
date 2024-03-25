SRCS = init.c main.c linedraw.c read_file.c utils.c loop.c color.c save.c rotate.c
OBJS = $(SRCS:.c=.o)
NAME = fdf
INC = ./minilibx_macos
CC = cc
CFLAGS = -Wall -Wextra -Werror
TAGS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ -I $(INC) -L $(INC) $(TAGS)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c $< -I $(INC)

clean:
	rm -f $(OBJS)

fclean:
	make clean
	rm -f $(NAME)

re:
	make fclean
	make all