/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:00:54 by lmuzio            #+#    #+#             */
/*   Updated: 2022/03/26 21:36:04 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_coords	*new_coords(double xmin, double xmax, double ymin, \
double ymax)
{
	t_coords	*res;

	res = malloc(sizeof(t_coords));
	if (res)
	{
		res->xmin = xmin;
		res->xmax = xmax;
		res->ymin = ymin;
		res->ymax = ymax;
	}
	return (res);
}

void	set_zoom(t_vars *vars, t_coords *coords)
{
	free(vars->zoom);
	if (!coords)
		win_close(vars, ERR_MSG);
	vars->zoom = coords;
}

int	zoom(int key, int x, int y, t_vars *vars)
{
	double	xstep;
	double	ystep;

	if (key == 4)
	{
		xstep = fabsl(vars->zoom->xmax - vars->zoom->xmin) / 10;
		ystep = fabsl(vars->zoom->ymax - vars->zoom->ymin) / 10;
		shift_zoom(vars, x, y, 0);
		set_zoom(vars, new_coords(vars->zoom->xmin + xstep, vars->zoom->\
		xmax - xstep, vars->zoom->ymin + ystep, vars->zoom->ymax - ystep));
	}
	else if (key == 5)
	{
		xstep = fabsl(vars->zoom->xmax - vars->zoom->xmin) / 5;
		if (xstep * 5 > 10)
			return (0);
		ystep = fabsl(vars->zoom->ymax - vars->zoom->ymin) / 5;
		shift_zoom(vars, x, y, 1);
		set_zoom(vars, new_coords(vars->zoom->xmin - xstep, vars->zoom->\
		xmax + xstep, vars->zoom->ymin - ystep, vars->zoom->ymax + ystep));
	}
	return (0);
}

void	shift_zoom(t_vars *vars, int x, int y, int direction)
{
	double	xmov;
	double	ymov;
	double	xstep;
	double	ystep;

	xmov = -map(x, vars->x_res, -1, 1);
	ymov = -map(y, vars->y_res, -1, 1);
	xstep = fabsl(vars->zoom->xmax - vars->zoom->xmin) / 10;
	ystep = fabsl(vars->zoom->ymax - vars->zoom->ymin) / 10;
	xstep *= xmov;
	ystep *= ymov;
	if (direction)
	{
		xstep = -xstep;
		ystep = -ystep;
	}
	set_zoom(vars, new_coords(\
		vars->zoom->xmin - xstep, vars->zoom->xmax - xstep, \
		vars->zoom->ymin + ystep, vars->zoom->ymax + ystep));
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
	else if (key == 1)
		vars->xconst -= vars->j_step;
	else if (key == 13)
		vars->xconst += vars->j_step;
	else if (key == 0)
		vars->yconst -= vars->j_step;
	else if (key == 2)
		vars->yconst += vars->j_step;
}
