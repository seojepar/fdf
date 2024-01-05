CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ./utils/get_next_line.c \
		./utils/get_next_line_utils.c \
		./utils/ft_split.c \
		./utils/ft_atoi.c \
		./utils/ft_substr.c \
		./utils/ft_strlcpy.c
INC = ./utils
OBJS = $(SRCS:.c=.o)
NAME = fdf.a

all: $(NAME)
$(NAME): $(OBJS)
	ar -cr $(NAME) $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)
clean:
	rm -f $(OBJS)
fclean: 
	make clean
	rm -f $(NAME)
re:
	make fclean
	make all
