/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coords.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 00:51:13 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(double xstep, double ystep, void *vvars)
{
	int32_t			x;
	int32_t			y;
	t_vars			*vars;

	vars = (t_vars *)vvars;
	mlx_get_mouse_pos(vars->mlx, &x, &y);
	if (ystep > 0)
	{
		xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10;
		ystep = fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10;
		shift_zoom(vars, x, y, 0);
	}
	else if (ystep < 0)
	{
		xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 5;
		if (xstep * 5 > 10)
			return ;
		ystep = fabsl(vars->zoom.ymax - vars->zoom.ymin) / 5;
		shift_zoom(vars, x, y, 1);
	}
}

void	shift_zoom(t_vars *vars, int x, int y, int direction)
{
	long double	xmov;
	long double	ymov;

	if (!direction)
	{
		xmov = map(x, vars->x_res, vars->zoom.xmin, vars->zoom.xmax);
		ymov = map(y, vars->y_res, vars->zoom.ymin, vars->zoom.ymax);
		vars->zoom = (t_coords){\
			xmov + ((vars->zoom.xmin - xmov) * 0.9), \
			xmov + ((vars->zoom.xmax - xmov) * 0.9), \
			ymov + ((vars->zoom.ymin - ymov) * 0.9), \
			ymov + ((vars->zoom.ymax - ymov) * 0.9), \
		};
	}
	else
	{
		xmov = (fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10);
		ymov = (fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10);
		vars->zoom = (t_coords){\
			vars->zoom.xmin - xmov, vars->zoom.xmax + xmov, \
			vars->zoom.ymin - ymov, vars->zoom.ymax + ymov \
		};
	}
}

int	shift_view(int key, t_vars *vars, long double xstep, long double ystep)
{
	if (key == MLX_KEY_DOWN)
		vars->zoom = (t_coords){vars->zoom.xmin, vars->zoom.xmax, \
		vars->zoom.ymin + ystep, vars->zoom.ymax + ystep};
	else if (key == MLX_KEY_UP)
		vars->zoom = (t_coords){vars->zoom.xmin, vars->zoom.xmax, \
		vars->zoom.ymin - ystep, vars->zoom.ymax - ystep};
	else if (key == MLX_KEY_LEFT)
		vars->zoom = (t_coords){vars->zoom.xmin - xstep, vars->zoom.xmax - \
		xstep, vars->zoom.ymin, vars->zoom.ymax};
	else if (key == MLX_KEY_RIGHT)
		vars->zoom = (t_coords){vars->zoom.xmin + xstep, vars->zoom.xmax + \
		xstep, vars->zoom.ymin, vars->zoom.ymax};
	else if (key == MLX_KEY_A)
		vars->xconst -= vars->j_step;
	else if (key == MLX_KEY_D)
		vars->xconst += vars->j_step;
	else if (key == MLX_KEY_S)
		vars->yconst -= vars->j_step;
	else if (key == MLX_KEY_W)
		vars->yconst += vars->j_step;
	else
		return (0);
	return (1);
}
