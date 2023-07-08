SRC_DIR := src

OBJ_DIR := obj

FILES :=  fractol.c calcs.c utils.c coords.c colors.c arguments.c

SRC := $(addprefix $(SRC_DIR)/, $(FILES))

OBJ := $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

LIB := build/libmlx42.a

INC := -Iincludes -IMLX42/include

CFLAGS := -Wall -Wextra -Werror $(INC) -c -flto -O3 -fno-stack-protector

LFLAGS := -L "/Users/$(USER)/.brew/lib" -lglfw -framework Cocoa -framework OpenGL $(INC) -framework IOKit -flto -O3

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

l: LFLAGS = -flto -O3 $(INC) -ldl -lglfw -pthread -lm
l: all

rel: LFLAGS = -flto -O3 $(INC) -ldl -lglfw -pthread -lm
rel: fclean all

mem:
	memdetect $(SRC) $(LIB) $(LFLAGS) $(1)