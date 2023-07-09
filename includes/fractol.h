/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:01:05 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 13:24:30 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/MLX42_Int.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h>

# define HELP_MSG "Usage: ./fractol <lowcase initial\
 of set's name> <optional args> <max iterations> <additional args>\n\n\
Available Sets:\n\t\
m <max iterations>:\t\t\tMandelbrot\n\t\
b <max iterations>:\t\t\tBurning ship\n\t\
j <float> <float> <max iterations>:\tJulia\t\t\n"
# define ERR_MSG "Program terminated. An error occourred\n"
# define ADD_ARG_MSG "An error occourred while parsing additional arguments.\n\
Through additional arguments you can define different values:\n\n\
Color palette:\t0: procedurally generated palette\n\t\t1: fixed palette\n\n\
Window size:\ttype <x size>x<y size>. Ex: 1920x1080\n\n\
Julia's step:\tthis is gonna change the intensity\n\
\t\tof the WASD controls when viewing Julia's set.\n\
\t\tType a decimal (not integer) to set this value. Ex: 0.01\n"
# define TOO_MANY_ARGS "You typed too many additional arguments, \
use maximum 3 more than required for Julia, 2 more for others\n"
# define P_SIZE 16
# define MAX_THREADS 15

typedef struct s_coords
{
	long double	xmin;
	long double	xmax;
	long double	ymin;
	long double	ymax;
}	t_coords;

typedef struct s_complex
{
	long double	a;
	long double	az;
	long double	b;
	long double	bz;
}	t_complex;

typedef struct s_vars	t_vars;

typedef size_t			(*t_func)(t_complex*, int, t_vars *);

typedef struct s_vars
{
	mlx_t			*mlx;
	int				type;
	t_func			func;
	t_coords		zoom;
	mlx_image_t		*i;
	unsigned long	palette[P_SIZE + 1];
	long double		xconst;
	long double		yconst;
	int				iters;
	int				x_res;
	int				y_res;
	long double		j_step;
	int				color_set;
	int				typeog;
}	t_vars;

typedef struct s_threadvars
{
	pthread_t	thread;
	t_complex	complex;
	t_vars		*vars;
	int			x;
	int			y;
	int			y_fract;
}	t_threadvars;

enum Fractal
{
	MANDELBROT,
	BURNING_SHIP,
	NUM_FRACTALS
};

long double			ft_atof(char *s);
void				atof_cycle(char *s, long double *res);
void				draw_set(t_vars *vars);
size_t				modulo_colors(long double z, int n, int iter, t_vars *vars);
int					win_close(t_vars *vars, char *msg);
void				key(mlx_key_data_t keydata, void *vvars);
void				zoom(double xstep, double ystep, void *vvars);
void				mouse(mouse_key_t button, action_t action, modifier_key_t mods, void* vvars);
void				shift_zoom(t_vars *vars, int x, int y, int direction);
int					ft_isnum(char *str);
size_t				calc_mandel(t_complex *comp, int iter, t_vars *vars);
size_t				calc_burning_ship(t_complex *comp, int iter, t_vars *vars);
void				generate_palette(unsigned long *palette);
void				parse_settings(t_vars *v, char **argv, int argc);
void				loop(t_vars *vars);
void				change_fractal(t_vars *vars, int type);
void				shift_view(int key, t_vars *vars, long double xstep, \
							long double ystep);
long double	map(long double middle, long double win_size, \
					long double min, long double max);

#endif