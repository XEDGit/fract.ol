#include "fractol.h"

int	close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free(vars->zoom);
	exit(0);
}

void	shift_view(int key, t_vars *vars, double xstep, double ystep)
{
	if (key == 125)
		set_zoom(vars, new_coords(\
		vars->zoom->xmin, vars->zoom->xmax, \
		vars->zoom->ymin + ystep, vars->zoom->ymax + ystep));
	if (key == 126)
		set_zoom(vars, new_coords(\
		vars->zoom->xmin, vars->zoom->xmax, \
		vars->zoom->ymin - ystep, vars->zoom->ymax - ystep));
	if (key == 123)
		set_zoom(vars, new_coords(\
		vars->zoom->xmin - xstep, vars->zoom->xmax - xstep, \
		vars->zoom->ymin, vars->zoom->ymax));
	if (key == 124)
		set_zoom(vars, new_coords(\
		vars->zoom->xmin + xstep, vars->zoom->xmax + xstep, \
		vars->zoom->ymin, vars->zoom->ymax));
}

int	key(int key, t_vars *vars)
{
	double	xstep;
	double	ystep;

	xstep = fabs(vars->zoom->xmax - vars->zoom->xmin) / 10;
	ystep = fabs(vars->zoom->ymax - vars->zoom->ymin) / 10;
	if (key == 53)
		close(vars);
	shift_view(key, vars, xstep, ystep);
	if (key == 43)
		vars->colshift -= 1;
	if (key == 47)
		vars->colshift += 1;
	return (0);
}

void	error_quit(void)
{
	printf(HELP_MSG);
	exit(1);
}

double	map(double middle, double win_size, double min, double max)
{
	return (middle / win_size * (max - min) + min);
}
