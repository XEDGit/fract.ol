SRCS := main.c calcs.c utils.c coords.c colors.c

OUTS := $(SRCS:.c=.o)

FLAGS := -Wall -Wextra -Werror

STEP := 0.001

all:
	@gcc $(SRCS) $(FLAGS) -Imlx -c -O3 
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol -fsanitize=address
	@make clean
clean:
	@rm $(OUTS)
m:
	@make all
	./fractol m
b:
	@make all
	./fractol b
j:
	@make
	./fractol j $(1) $(2)
bn:
	@gcc $(SRCS) -O3 -Imlx -c -D COL_SET=1
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m
fast:
	@gcc $(SRCS) -O3 -Imlx -c -D MAX_ITER=1000 -D WIN_SIZE=800
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
col:
	@gcc $(SRCS) -O3 -Imlx -c -D MAX_ITER=250 -D WIN_SIZE=800 -D COL_SET=$(SET)
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m
change:
	@gcc $(SRCS) -O3 -Imlx -c -D MAX_ITER=500 -D WIN_SIZE=600 -D COL_SET=0 -D JSTEP=$(STEP)
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol j $(1) $(2)