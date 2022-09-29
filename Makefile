SRCS :=  ./src/fractol.c ./src/calcs.c ./src/utils.c ./src/coords.c ./src/colors.c ./src/arguments.c

OUTS := ./fractol.o ./calcs.o ./utils.o ./coords.o ./colors.o ./arguments.o

LIB := libmlx.dylib

FLAGS := -Wall -Wextra -Werror -Ofast -mtune=native -march=native -Imlx -Iincludes -c

FLAGS2 := -lm -L. -lmlx -framework OpenGL -framework AppKit

GREEN := \033[32m

DEFAULT := \033[39m

NAME := fractol

$(NAME): $(OUTS)
	gcc $(OUTS) $(FLAGS2) -o $(NAME)
$(OUTS): $(SRCS) $(LIB)
	gcc $(SRCS) $(FLAGS)
$(LIB):
	make -C ./mlx
	mv ./mlx/$(LIB) .
all: $(LIB)
	gcc $(SRCS) $(FLAGS)
	gcc $(OUTS) $(FLAGS2) -o $(NAME)
clean:
	rm -f $(OUTS)
fclean:
	rm -f $(OUTS) $(NAME) $(LIB)
re: fclean $(LIB) $(NAME)
	