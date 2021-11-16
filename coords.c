#include "fractol.h"

t_coords	*new_coords(double xmin, double xmax, double ymin, double ymax)
{
	t_coords	*res;

	res = malloc(sizeof(t_coords));
	res->xmin = xmin;
	res->xmax = xmax;
	res->ymin = ymin;
	res->ymax = ymax;
	return (res);
}

void	set_zoom(t_vars *vars, t_coords *coords)
{
	free(vars->zoom);
	vars->zoom = coords;
}

int	zoom(int key, int x, int y, t_vars *vars)
{
	double	xstep;
	double	ystep;

	if (key == 4)
	{
		xstep = fabs(vars->zoom->xmax - vars->zoom->xmin) / 10;
		ystep = fabs(vars->zoom->ymax - vars->zoom->ymin) / 10;
		shift_zoom(vars, x, y);
		set_zoom(vars, new_coords(\
		vars->zoom->xmin + xstep, vars->zoom->xmax - xstep, \
		vars->zoom->ymin + ystep, vars->zoom->ymax - ystep));
	}
	if (key == 5)
	{
		xstep = fabs(vars->zoom->xmax - vars->zoom->xmin) / 5;
		ystep = fabs(vars->zoom->ymax - vars->zoom->ymin) / 5;
		if (xstep * 5 > 4)
			return (0);
		shift_zoom(vars, x, y);
		set_zoom(vars, new_coords(\
		vars->zoom->xmin - xstep, vars->zoom->xmax + xstep, \
		vars->zoom->ymin - ystep, vars->zoom->ymax + ystep));
	}
	return (0);
}

void	shift_zoom(t_vars *vars, int x, int y)
{
	float	xmov;
	float	ymov;
	float	xstep;
	float	ystep;

	xmov = -map(x, vars->sizex, -1, 1);
	ymov = -map(y, vars->sizey, -1, 1);
	xstep = fabs(vars->zoom->xmax - vars->zoom->xmin) / 10;
	ystep = fabs(vars->zoom->ymax - vars->zoom->ymin) / 10;
	xstep *= xmov;
	ystep *= ymov;
	set_zoom(vars, new_coords(\
		vars->zoom->xmin - xstep, vars->zoom->xmax - xstep, \
		vars->zoom->ymin + ystep, vars->zoom->ymax + ystep));
}
