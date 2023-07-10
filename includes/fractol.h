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

# define HELP_MSG "This is a help message, to run the program \
without displaying this do not add arguments after ./fractol\n\n\
Commands:\n\
\tTAB:	Change fractal displayed\n\
\tR:	Reload original zoom\n\
\tC:	Change color set\n\
\tJ:	Visualize Julia's set of the current fractal\n\
\t.:	Shift color\n\
\t,:	Shift color backwards\n\
\t/:	Reset color shift\n\
\t-: 	Zoom out\n\
\t+(=):	Zoom in\n\
\tSCROLL:	Zoom in/out\n\
\tRCLICK:	Visualize Julia's set at mouse coordinates\n\
\tWASD:	Change constants of Julia's set\n\
\tARROWS:	Move within the scene\n\
\tESC:	Exit\n"
# define ERR_MSG "Program terminated. An error occourred\n"
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

enum e_fractal
{
	MANDELBROT,
	BURNING_SHIP,
	NUM_FRACTALS
};

long double	ft_atof(char *s);
void		atof_cycle(char *s, long double *res);
void		draw_set(t_vars *vars);
size_t		modulo_colors(long double z, int n, int iter, t_vars *vars);
int			win_close(t_vars *vars, char *msg);
void		key(mlx_key_data_t keydata, void *vvars);
void		zoom(double xstep, double ystep, void *vvars);
void		resize(int width, int height, void *vvars);
void		mouse(mouse_key_t button, action_t action, \
				modifier_key_t mods, void *vvars);
void		print(const char *s);
void		shift_zoom(t_vars *vars, int x, int y, int direction);
size_t		calc_mandel(t_complex *comp, int iter, t_vars *vars);
size_t		calc_burning_ship(t_complex *comp, int iter, t_vars *vars);
void		generate_palette(unsigned long *palette);
void		loop(t_vars *vars);
void		change_fractal(t_vars *vars, int type);
int			shift_view(int key, t_vars *vars, long double xstep, \
					long double ystep);
long double	map(long double middle, long double win_size, \
					long double min, long double max);

#endif