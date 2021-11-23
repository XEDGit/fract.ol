SRCS := main.c calcs.c utils.c coords.c colors.c

OUTS := $(SRCS:.c=.o)

FLAGS := -Wall -Wextra -Werror -Ofast -Imlx -c

FLAGS2 := -lm -L. -lmlx -framework OpenGL -framework AppKit

ITERS := 500

GREEN := \033[32m

DEFAULT := \033[39m

all:
	@gcc $(SRCS) $(FLAGS)
	@gcc $(OUTS) $(FLAGS2) -o fractol
clean:
	@rm -f $(OUTS)
fclean:
	@rm -f $(OUTS) fractol
re:
	@make fclean
	@make all
bonus:
	@make all
m:
	@make all
	./fractol m $(ITERS)
b:
	@make all
	./fractol b $(ITERS)
j:
	@make
	./fractol j $(1) $(2) $(ITERS)
prod:
	@echo "\n$(GREEN)Cleaning '$(DEFAULT)Executables$(GREEN)' folder...\n"
	@rm -f ./Executables/*
	@echo "		NAME		WIN_SIZE	COL_SET\n"
	@echo "Compiling$(DEFAULT)	fractol_big0	1920x1080	0"
	@gcc $(SRCS) $(FLAGS) -D COL_SET=0
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_big0
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_big1	1920x1080	1"
	@gcc $(SRCS) $(FLAGS) -D COL_SET=1
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_big1
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_small0	640x480		0"
	@gcc $(SRCS) $(FLAGS) -D WIN_SIZE_X=640 -D WIN_SIZE_Y=480
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_small0
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_small1	640x480		1\n"
	@gcc $(SRCS) $(FLAGS) -D WIN_SIZE_X=640 -D WIN_SIZE_Y=480 -D COL_SET=1
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_small1
	@echo "$(GREEN)Copying '$(DEFAULT)libmlx.dylib$(GREEN)'...\n"
	@cp libmlx.dylib Executables
	@echo "Done!$(DEFAULT)\n"
	@make clean