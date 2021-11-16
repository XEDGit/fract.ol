#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_coords
{
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
}	t_coords;

typedef struct s_vars
{
	void		*mlx;
	void		*mlx_win;
	size_t		(*type)(double, double, double, double);
	t_coords	*zoom;
	int			colshift;
	double		xconst;
	double		yconst;
	int			sizex;
	int			sizey;
}	t_vars;

size_t		calc_mandel(double a, double b, double oa, double ob);
size_t		calc_julia(double a, double b, double vara, double varb);
size_t		color_set(int n, int shift);
void		shift_view(int key, t_vars *vars, double xstep, double ystep);
double		map(double middle, double win_size, double min, double max);
int			close(t_vars *vars);
int			key(int key, t_vars *vars);
double		map(double middle, double win_size, double min, double max);
void		error_quit(void);
t_coords	*new_coords(double xmin, double xmax, double ymin, double ymax);
void		set_zoom(t_vars *vars, t_coords *coords);
int			zoom(int key, int x, int y, t_vars *vars);
void		shift_zoom(t_vars *vars, int x, int y);
double		ft_atof(char *s);
void		atof_cycle(char *s, double *res);

# define HELP_MSG "Usage: ./fractol <lowcase initial of set's name> <optional args>\n\
Available Sets:\n\t.Mandelbrot\n\t.Julia\t<float> <float>\n"
# ifndef MAX_ITER
#  define MAX_ITER 500
# endif
# ifndef WIN_SIZE
#  define WIN_SIZE 500
# endif

#endif