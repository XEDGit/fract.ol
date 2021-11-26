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

typedef struct s_vars
{
	void			*mlx;
	void			*mlx_win;
	int				type;
	size_t			(*func)(t_complex *comp, int iter, unsigned long *p);
	t_coords		*zoom;
	t_data			*i;
	t_data			*img_buff;
	unsigned long	*palette;
	double			xconst;
	double			yconst;
	int				iters;
}	t_vars;

void			draw_set(t_vars *vars);
size_t			modulo_colors(double z, int n, int iter, unsigned long *p);
int				win_close(t_vars *vars, char *msg);
int				key(int key, t_vars *vars);
void			img_mlx_pixel_put(t_data *data, int x, int y, int color);
void			set_zoom(t_vars *vars, t_coords *coords);
int				zoom(int key, int x, int y, t_vars *vars);
void			shift_zoom(t_vars *vars, int x, int y, int direction);
double			ft_atof(char *s);
void			atof_cycle(char *s, double *res);
void			shift_view(int key, t_vars *vars, double xstep, \
double ystep);
double			map(double middle, double win_size, \
double min, double max);
t_coords		*new_coords(double xmin, double xmax, \
double ymin, double ymax);
size_t			calc_mandel(t_complex *comp, int iter, unsigned long *p);
size_t			calc_burning_ship(t_complex *comp, int iter, unsigned long *p);
void			generate_palette(unsigned long *palette);
int				loop(t_vars *vars);

# define HELP_MSG "Usage: ./fractol <lowcase initial\
 of set's name> <optional args> <max iterations>\n\n\
Available Sets:\n\t\
m <max iterations>:\t\t\tMandelbrot\n\t\
b <max iterations>:\t\t\tBurning ship\n\t\
j <float> <float> <max iterations>:\tJulia\t\t\n"
# define ERR_MSG "Program terminated. An error occourred\n"
# ifdef P_SIZE
#  undef P_SIZE
# endif
# define P_SIZE 16
# ifndef WIN_SIZE_X
#  define WIN_SIZE_X 1920
# endif
# ifndef WIN_SIZE_Y
#  define WIN_SIZE_Y 1080
# endif
# ifndef COL_SET
#  define COL_SET 0
# endif
# ifndef JSTEP
#  define JSTEP 0.01
# endif

#endif