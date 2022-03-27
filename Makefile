SRCS := fractol.c calcs.c utils.c coords.c colors.c arguments.c

OUTS := $(SRCS:.c=.o)

FLAGS := -Wall -Wextra -Werror -Ofast -mtune=native -march=native -Imlx -c

FLAGS2 := -lm -L. -lmlx -framework OpenGL -framework AppKit

ITERS := 500

GREEN := \033[32m

DEFAULT := \033[39m

NAME := fractol

$(NAME): $(OUTS)
	gcc $(OUTS) $(FLAGS2) -o fractol
$(OUTS): $(SRCS)
	gcc $(SRCS) $(FLAGS)
all:
	gcc $(SRCS) $(FLAGS)
	gcc $(OUTS) $(FLAGS2) -o fractol
clean:
	rm -f $(OUTS)
fclean:
	rm -f $(OUTS) fractol
re:
	@make fclean
	@make