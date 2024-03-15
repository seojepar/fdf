SRC = main.c bresenham.c read_file.c utils.c event_handler.c init.c gen_color.c gen_dot.c
TARGET = fdf
INC = ./minilibx_macos
CC = cc -g -fsanitize=address
CFLAGS = -lmlx -framework OpenGL -framework AppKit
TEST_FILES := $(wildcard test_maps/*.fdf)
TEST_OUTPUTS := $(TEST_FILES:test_maps/%.fdf=test_output/%.out)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $@ $^ -I $(INC) -L $(INC) $(CFLAGS)

test: $(TEST_OUTPUTS)

test_output/%.out: test_maps/%.fdf
	./$(TARGET) $< > $@

clean:
	rm -f $(TARGET)

fclean:
	make clean
	rm -f $(TEST_OUTPUTS)

re:
	make fclean
	make all