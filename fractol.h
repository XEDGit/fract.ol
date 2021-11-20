#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_coords
{
	long double	xmin;
	long double	xmax;
	long double	ymin;
	long double	ymax;
}	t_coords;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void			*mlx;
	void			*mlx_win;
	int				type;
	size_t			(*func)(long double, long double, long double, long double);
	t_coords		*zoom;
	t_data			*img;
	t_data			*img_buff;
	int				colshift;
	long double		xconst;
	long double		yconst;
}	t_vars;

void			draw_set(t_vars *vars);
size_t			color_set(int n, int shift, int set);
size_t			modulo_colors(int n);
int				win_close(t_vars *vars, char *msg);
int				key(int key, t_vars *vars);
void			img_mlx_pixel_put(t_data *data, int x, int y, int color);
void			set_zoom(t_vars *vars, t_coords *coords);
int				zoom(int key, int x, int y, t_vars *vars);
void			shift_zoom(t_vars *vars, int x, int y, int direction);
long double		ft_atof(char *s);
void			atof_cycle(char *s, long double *res);
void			shift_view(int key, t_vars *vars, long double xstep, \
long double ystep);
long double		map(long double middle, long double win_size, \
long double min, long double max);
t_coords		*new_coords(long double xmin, long double xmax, \
long double ymin, long double ymax);
size_t			calc_mandel(long double a, long double b, long double oa, \
long double ob);
size_t			calc_burning_ship(long double a, long double b, long double \
oa, long double ob);

# define HELP_MSG "Usage: ./fractol <lowcase initial\
 of set's name> <optional args>\n\n\
Available Sets:\n\t\
m:	Mandelbrot\n\t\
b:	Burning ship\n\t\
j:	Julia\t\t<float> <float>\n"
# define ERR_MSG "Program terminated.\nAn error occourred\n"
# ifndef MAX_ITER
#  define MAX_ITER 1080
# endif
# ifndef WIN_SIZE
#  define WIN_SIZE 500
# endif
# ifndef COL_SET
#  define COL_SET 0
# endif
# ifndef JSTEP
#  define JSTEP 0.01
# endif

#endif