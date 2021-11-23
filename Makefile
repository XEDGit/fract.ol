SRCS := main.c calcs.c utils.c coords.c colors.c

OUTS := $(SRCS:.c=.o)

FLAGS := -Wall -Wextra -Werror

STEP := 0.001

all:
	@gcc $(SRCS) $(FLAGS) -Imlx -c -O3
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
clean:
	@rm $(OUTS)
fclean:
	@rm $(OUTS) fractol
re:
	@make fclean
	@make all
bonus:
	@make all
m:
	@make all
	./fractol m
b:
	@make all
	./fractol b
j:
	@make
	./fractol j $(1) $(2)
fast:
	@gcc $(SRCS) -O3 -Imlx -c -D MAX_ITER=1000 -D WIN_SIZE=300
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
col:
	@gcc $(SRCS) -O3 -Imlx -c -D COL_SET=$(SET)
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol_colset$(SET)
	@make clean
change:
	@gcc $(SRCS) -O3 -Imlx -c -D MAX_ITER=500 -D WIN_SIZE=600 -D COL_SET=0 -D JSTEP=$(STEP)
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol j $(1) $(2)