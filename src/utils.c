/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:01:01 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 13:14:43 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print(const char *s)
{
	int		buffer_length;

	buffer_length = 0;
	if (!s)
		return ;
	while (s[buffer_length])
		buffer_length++;
	if (write(1, s, buffer_length))
		return ;
}

int	win_close(t_vars *vars, char *msg)
{
	if (vars && vars->mlx)
	{
		mlx_close_window(vars->mlx);
		mlx_terminate(vars->mlx);
	}
	print(msg);
	exit(0);
}

void	change_fractal(t_vars *vars, int type)
{
	static t_func	algos[2] = {
		calc_mandel,
		calc_burning_ship,
	};
	static int		current = MANDELBROT;

	if (type == -1)
	{
		type = current + 1;
		if (type >= NUM_FRACTALS)
			type = 0;
	}
	vars->func = algos[type];
	current = type;
}

void	reset_zoom(t_vars *vars)
{
	if (vars->x_res < vars->y_res)
		vars->zoom = (t_coords){-2, 2, -2 * ((double)vars->y_res / \
			vars->x_res), 2 * ((double)vars->y_res / vars->x_res)};
	else
		vars->zoom = (t_coords){-2 * ((double)vars->x_res / \
			vars->y_res), 2 * ((double)vars->x_res / vars->y_res), -2, 2};
}
