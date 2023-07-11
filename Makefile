SRC_DIR := src

OBJ_DIR := obj

FILES :=  fractol.c calcs.c utils.c zoom.c colors.c hooks.c

HEADERS := includes/fractol.h

SRC := $(addprefix $(SRC_DIR)/, $(FILES))

OBJ := $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

LIB := build/libmlx42.a

INC := -Iincludes -IMLX42/include

CFLAGS := -Wall -Wextra -Werror $(INC) -c -flto -O3

LFLAGS := -L "/Users/$(USER)/.brew/lib" -lglfw -framework Cocoa -framework OpenGL $(INC) -framework IOKit -flto -O3

GREEN := \033[32m

DEFAULT := \033[39m

NAME := fractol

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc $(OBJ) $(LIB) $(LFLAGS) -o $@

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $< $(CFLAGS) -o $@

$(LIB):
	cmake -S MLX42 -B build
	cmake --build build -j4

clean:
	rm -rf $(OBJ_DIR)
fclean:
	rm -rf $(OBJ_DIR) $(NAME) build

re: fclean all

l: LFLAGS = -flto -O3 $(INC) -ldl -lglfw -pthread -lm
l: all

rel: LFLAGS = -flto -O3 $(INC) -ldl -lglfw -pthread -lm
rel: fclean all

mem:
	memdetect $(SRC) $(LIB) $(LFLAGS) $(1)