/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:01:01 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 01:06:42 by lmuzio        ########   odam.nl         */
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
		pthread_mutex_destroy(&vars->mutex);
		mlx_close_window(vars->mlx);
		mlx_terminate(vars->mlx);
	}
	print(msg);
	exit(0);
}

long double	map(long double middle, long double win_size, long double min, \
long double max)
{
	long double	first;
	long double	second;

	first = middle / win_size;
	second = max - min;
	min = first * second + min;
	return (min);
}

void	key(mlx_key_data_t keydata, void *vvars)
{
	long double	xstep;
	long double	ystep;
	t_vars		*vars;

	vars = (t_vars *)vvars;
	if (!vars)
		return ;
	xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10;
	ystep = fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10;
	shift_view(keydata.key, vars, xstep, ystep);
	if (keydata.key == MLX_KEY_ESCAPE)
		win_close(vars, 0);
	else if (keydata.key == MLX_KEY_EQUAL)
		zoom(0, 1, vars);
	else if (keydata.key == MLX_KEY_MINUS)
		zoom(0, -1, vars);
	else if (keydata.key == MLX_KEY_R)
		vars->zoom = (t_coords){(-(vars->x_res / 100)), (vars->x_res / 100), \
		-(vars->y_res / 100), (vars->y_res / 100)};
	else if (keydata.key == MLX_KEY_PERIOD && \
	!vars->color_set && vars->palette[P_SIZE] > 12)
		vars->palette[P_SIZE] -= 12;
	else if (keydata.key == MLX_KEY_PERIOD && vars->color_set)
		vars->palette[P_SIZE] -= 12;
	else if (keydata.key == MLX_KEY_COMMA)
		vars->palette[P_SIZE] += 13;
	else if (keydata.key == MLX_KEY_SLASH)
		vars->palette[P_SIZE] = 0;
}
