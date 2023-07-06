SRC_DIR := src

OBJ_DIR := obj

FILES :=  fractol.c calcs.c utils.c coords.c colors.c arguments.c

SRC := $(addprefix $(SRC_DIR)/, $(FILES))

OBJ := $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

LIB := build/libmlx42.a

CFLAGS := -g -Wall -Wextra -Werror -IMLX42/include -Iincludes -c -flto -O3

LFLAGS := -g -L "/Users/$(USER)/.brew/lib" -lglfw -framework Cocoa -framework OpenGL -Iincludes -IMLX42/include -framework IOKit# -flto -O3

GREEN := \033[32m

DEFAULT := \033[39m

NAME := fractol

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	gcc $^ $(LFLAGS) -o $@

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $< $(CFLAGS) -o $@

$(LIB):
	cmake -S MLX42 -B build
	cmake --build build -j4
clean:
	rm -rf $(OBJ_DIR)
fclean:
	rm -rf $(OBJ_DIR) $(NAME) build
re: fclean $(LIB) $(NAME)
	
mem:
	memdetect $(SRC) $(LIB) $(LFLAGS) $(1)