SRCS :=  ./src/fractol.c ./src/calcs.c ./src/utils.c ./src/coords.c ./src/colors.c ./src/arguments.c

OUTS := ./fractol.o ./calcs.o ./utils.o ./coords.o ./colors.o ./arguments.o

FLAGS := -Wall -Wextra -Werror -Ofast -mtune=native -march=native -Imlx -Iincludes -c

FLAGS2 := -lm -L. -lmlx -framework OpenGL -framework AppKit

ITERS := 500

GREEN := \033[32m

DEFAULT := \033[39m

NAME := fractol

$(NAME): $(OUTS)
	gcc $(OUTS) $(FLAGS2) -o fractol
$(OUTS): $(SRCS) libmlx.dylib
	gcc $(SRCS) $(FLAGS)
libmlx.dylib:
	make -C ./mlx
	mv ./mlx/libmlx.dylib .
all: libmlx.dylib
	gcc $(SRCS) $(FLAGS)
	gcc $(OUTS) $(FLAGS2) -o fractol
clean:
	rm -f $(OUTS)
fclean:
	rm -f $(OUTS) fractol libmlx.dylib
re: fclean libmlx.dylib
	@make