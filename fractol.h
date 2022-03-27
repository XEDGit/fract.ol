/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:01:05 by lmuzio            #+#    #+#             */
/*   Updated: 2022/03/27 21:57:40 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct s_coords
{
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
}	t_coords;

typedef struct s_complex
{
	double	a;
	double	az;
	double	b;
	double	bz;
}	t_complex;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_l;
	int		e;
}				t_data;

typedef struct s_vars	t_vars;

typedef size_t			(*t_func)(t_complex*, int, t_vars *);

typedef struct s_vars
{
	void			*mlx;
	void			*mlx_win;
	int				type;
	t_func			func;
	t_coords		*zoom;
	t_data			*i;
	t_data			*img_buff;
	unsigned long	*palette;
	double			xconst;
	double			yconst;
	int				iters;
	int				x_res;
	int				y_res;
	double			j_step;
	int				color_set;
}	t_vars;

void			draw_set(t_vars *vars);
size_t			modulo_colors(double z, int n, int iter, t_vars *vars);
int				win_close(t_vars *vars, char *msg);
int				key(int key, t_vars *vars);
void			img_mlx_pixel_put(t_data *data, int x, int y, int color);
void			set_zoom(t_vars *vars, t_coords *coords);
int				zoom(int key, int x, int y, t_vars *vars);
void			shift_zoom(t_vars *vars, int x, int y, int direction);
double			ft_atof(char *s);
void			atof_cycle(char *s, double *res);
size_t			calc_mandel(t_complex *comp, int iter, t_vars *vars);
size_t			calc_burning_ship(t_complex *comp, int iter, t_vars *vars);
void			generate_palette(unsigned long *palette);
void			parse_settings(t_vars *v, char **argv, int argc);
int				loop(t_vars *vars);
void			shift_view(int key, t_vars *vars, double xstep, \
							double ystep);
double			map(double middle, double win_size, \
					double min, double max);
t_coords		*new_coords(double xmin, double xmax, \
							double ymin, double ymax);

# ifndef HELP_MSG
#  define HELP_MSG "Usage: ./fractol <lowcase initial\
 of set's name> <optional args> <max iterations>\n\n\
Available Sets:\n\t\
m <max iterations>:\t\t\tMandelbrot\n\t\
b <max iterations>:\t\t\tBurning ship\n\t\
j <float> <float> <max iterations>:\tJulia\t\t\n"
# endif

# ifndef ERR_MSG
#  define ERR_MSG "Program terminated. An error occourred\n"
# endif

# ifndef  ADD_ARG_MSG
#  define ADD_ARG_MSG "An error occourred while parsing additional arguments.\n\
Through additional arguments you can define different values:\n\n\
Color palette:\t0: procedurally generated palette\n\t\t1: fixed palette\n\n\
Window size:\ttype <x size>x<y size>. Ex: 1920x1080\n\n\
Julia's step:\tthis is gonna change the intensity\n\
\t\tof the WASD controls when viewing Julia's set.\n\
\t\tType a decimal (not integer) to set this value. Ex: 0.01\n"
# endif

# ifndef TOO_MANY_ARGS
#  define TOO_MANY_ARGS "You typed too many optional arguments, \
use maximum 3 more than required\n"
# endif

# ifndef P_SIZE
#  define P_SIZE 16
# endif

#endif