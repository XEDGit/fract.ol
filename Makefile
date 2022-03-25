SRCS := fractol.c calcs.c utils.c coords.c colors.c

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
prod:
	@echo "\n$(GREEN)Cleaning '$(DEFAULT)Executables$(GREEN)' folder...\n"
	@rm -f ./Executables/*
	@echo "		NAME		WIN_SIZE	COL_SET\n"
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_xtra0	2560x1440	0"
	@gcc $(SRCS) $(FLAGS) -D COL_SET=0 -D WIN_SIZE_X=2560 -D WIN_SIZE_Y=1440
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_xtra0
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_xtra1	2560x1440	1"
	@gcc $(SRCS) $(FLAGS) -D COL_SET=1 -D WIN_SIZE_X=2560 -D WIN_SIZE_Y=1440
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_xtra1
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_big0	1920x1080	0"
	@gcc $(SRCS) $(FLAGS) -D COL_SET=0
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_big0
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_big1	1920x1080	1"
	@gcc $(SRCS) $(FLAGS) -D COL_SET=1
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_big1
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_medium0	1000x1000	0"
	@gcc $(SRCS) $(FLAGS) -D WIN_SIZE_X=1000 -D WIN_SIZE_Y=1000
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_medium0
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_medium1	1000x1000	1"
	@gcc $(SRCS) $(FLAGS) -D WIN_SIZE_X=1000 -D WIN_SIZE_Y=1000 -D COL_SET=1
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_medium1
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_small0	640x480		0"
	@gcc $(SRCS) $(FLAGS) -D WIN_SIZE_X=640 -D WIN_SIZE_Y=480
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_small0
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_small1	640x480		1"
	@gcc $(SRCS) $(FLAGS) -D WIN_SIZE_X=640 -D WIN_SIZE_Y=480 -D COL_SET=1
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_small1
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_xsmall0	100x100		0"
	@gcc $(SRCS) $(FLAGS) -D WIN_SIZE_X=100 -D WIN_SIZE_Y=100
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_xsmall0
	@echo "$(GREEN)Compiling$(DEFAULT)	fractol_xsmall1	100x100		1"
	@gcc $(SRCS) $(FLAGS) -D WIN_SIZE_X=100 -D WIN_SIZE_Y=100 -D COL_SET=1
	@gcc $(OUTS) $(FLAGS2) -o Executables/fractol_xsmall1
	@echo "\n$(GREEN)Copying '$(DEFAULT)libmlx.dylib$(GREEN)'...\n"
	@cp libmlx.dylib Executables
	@echo "Done!$(DEFAULT)\n"
	@make clean