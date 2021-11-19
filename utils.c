#include "fractol.h"

int	close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free(vars->zoom);
	exit(0);
}

double	map(double middle, double win_size, double min, double max)
{
	return (middle / win_size * (max - min) + min);
}

void	error_quit(char *msg)
{
	printf("%s", msg);
	exit(1);
}

int	key(int key, t_vars *vars)
{
	double	xstep;
	double	ystep;

	xstep = fabs(vars->zoom->xmax - vars->zoom->xmin) / 10;
	ystep = fabs(vars->zoom->ymax - vars->zoom->ymin) / 10;
	shift_view(key, vars, xstep, ystep);
	if (key == 53)
		close(vars);
	else if (key == 43)
		vars->colshift -= 10;
	else if (key == 47)
		vars->colshift += 10;
	else if (key == 15)
		set_zoom(vars, new_coords(-2.5, 1.5, -2, 2));
	return (0);
}
