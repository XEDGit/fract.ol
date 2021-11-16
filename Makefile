SRCS := main.c calcs.c utils.c coords.c

OUTS := $(SRCS:.c=.o)

all:
	@gcc $(SRCS) -Imlx -c
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
clean:
	@rm calcs.o main.o
m:
	@make
	./fractol m
j:
	@make
	./fractol j $(1) $(2)
toomany:
	@make
	./fractol j k l ghbec q7n
fastp:
	@gcc $(SRCS) -Imlx -c -D MAX_ITER=1000 -D WIN_SIZE=200
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m
fastb:
	@gcc $(SRCS) -Imlx -c -D MAX_ITER=50 -D WIN_SIZE=1000
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m
slowp:
	@gcc $(SRCS) -Imlx -c -D MAX_ITER=2000 -D WIN_SIZE=200
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m
slowb:
	@gcc $(SRCS) -Imlx -c -D MAX_ITER=200 -D WIN_SIZE=1000
	@gcc $(OUTS) -lm -L. -lmlx -framework OpenGL -framework AppKit -o fractol
	@make clean
	./fractol m