/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coords.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/06 15:57:36 by XEDGit        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(double xstep, double ystep, void *vvars)
{
	int32_t	x;
	int32_t	y;
	t_vars	*vars;

	vars = (t_vars *)vvars;
	mlx_get_mouse_pos(vars->mlx, &x, &y);
	if (ystep > 0)
	{
		xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10;
		ystep = fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10;
		shift_zoom(vars, x, y, 0);
		vars->zoom = (t_coords){vars->zoom.xmin + xstep, vars->zoom.\
		xmax - xstep, vars->zoom.ymin + ystep, vars->zoom.ymax - ystep};
	}
	else if (ystep < 0)
	{
		xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 5;
		if (xstep * 5 > 10)
			return ;
		ystep = fabsl(vars->zoom.ymax - vars->zoom.ymin) / 5;
		// shift_zoom(vars, x, y, 1);
		vars->zoom = (t_coords){vars->zoom.xmin - xstep, vars->zoom.\
		xmax + xstep, vars->zoom.ymin - ystep, vars->zoom.ymax + ystep};
	}
}

void	shift_zoom(t_vars *vars, int x, int y, int direction)
{
	long double	xmov;
	long double	ymov;
	long double	xstep;
	long double	ystep;

	xmov = -map(x, vars->x_res, -1, 1);
	ymov = -map(y, vars->y_res, -1, 1);
	xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10;
	ystep = -fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10;
	xstep *= xmov;
	ystep *= ymov;
	if (direction)
	{
		xstep = -xstep;
		ystep = -ystep;
	}
	vars->zoom = (t_coords){\
		vars->zoom.xmin - xstep, vars->zoom.xmax - xstep, \
		vars->zoom.ymin + ystep, vars->zoom.ymax + ystep};
}

void	shift_view(int key, t_vars *vars, long double xstep, long double ystep)
{
	if (key == MLX_KEY_DOWN)
		vars->zoom = (t_coords){\
		vars->zoom.xmin, vars->zoom.xmax, \
		vars->zoom.ymin + ystep, vars->zoom.ymax + ystep};
	if (key == MLX_KEY_UP)
		vars->zoom = (t_coords){\
		vars->zoom.xmin, vars->zoom.xmax, \
		vars->zoom.ymin - ystep, vars->zoom.ymax - ystep};
	if (key == MLX_KEY_LEFT)
		vars->zoom = (t_coords){\
		vars->zoom.xmin - xstep, vars->zoom.xmax - xstep, \
		vars->zoom.ymin, vars->zoom.ymax};
	if (key == MLX_KEY_RIGHT)
		vars->zoom = (t_coords){\
		vars->zoom.xmin + xstep, vars->zoom.xmax + xstep, \
		vars->zoom.ymin, vars->zoom.ymax};
	else if (key == MLX_KEY_A)
		vars->xconst -= vars->j_step;
	else if (key == MLX_KEY_D)
		vars->xconst += vars->j_step;
	else if (key == MLX_KEY_S)
		vars->yconst -= vars->j_step;
	else if (key == MLX_KEY_W)
		vars->yconst += vars->j_step;
}
