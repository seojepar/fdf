SRC = main.c linline.c read_file.c utils.c
TARGET = fdf
INC = ./minilibx_macos
CC = cc
CFLAGS = -lmlx -framework OpenGL -framework AppKit


all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $@ $^ -I $(INC) -L $(INC) $(CFLAGS)

clean:
	rm -f $(TARGET)

re:
	make clean
	make all