SRCS := main.c calcs.c utils.c coords.c

OUTS := $(SRCS:.c=.o)

FLAGS := -Wall -Wextra -Werror

STEP := 0.001

all:
	@gcc $(SRCS) $(FLAGS) -Imlx -c -O3
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
clean:
	@rm $(OUTS)
m:
	@make all
	./fractol m
j:
	@make
	./fractol j $(1) $(2)
bn:
	@gcc $(SRCS) -O3 -Imlx -c -D COL_SET=1
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m
fast:
	@gcc $(SRCS) -O3 -Imlx -c -D MAX_ITER=100 -D WIN_SIZE=500
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m
fastbn:
	@gcc $(SRCS) -O3 -Imlx -c -D MAX_ITER=200 -D WIN_SIZE=400 -D COL_SET=1
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m
change:
	@gcc $(SRCS) -O3 -Imlx -c -D MAX_ITER=200 -D WIN_SIZE=400 -D JSTEP=$(STEP)
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol j $(1) $(2)