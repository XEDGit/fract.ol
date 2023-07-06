/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:01:01 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/06 15:58:48 by XEDGit        ########   odam.nl         */
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
	write(1, s, buffer_length);
}

int	win_close(t_vars *vars, char *msg)
{
	if (vars)
	{
		if (vars->mlx)
		{
			mlx_close_window(vars->mlx);
			mlx_terminate(vars->mlx);
		}
		free(vars->zoom);
		vars->zoom = 0;
	}
	if (msg == HELP_MSG || msg == ERR_MSG \
	|| msg == ADD_ARG_MSG || msg == TOO_MANY_ARGS)
		print(msg);
	exit(0);
}

double	map(double middle, double win_size, double min, \
double max)
{
	double	first;
	double	second;

	first = middle / win_size;
	second = max - min;
	return (first * second + min);
}

void	key(mlx_key_data_t keydata, void *vvars)
{
	double	xstep;
	double	ystep;
	t_vars	*vars;

	vars = (t_vars *)vvars;
	if (!vars || !vars->zoom)
		return ;
	xstep = fabsl(vars->zoom->xmax - vars->zoom->xmin) / 10;
	ystep = fabsl(vars->zoom->ymax - vars->zoom->ymin) / 10;
	shift_view(keydata.key, vars, xstep, ystep);
	if (keydata.key == MLX_KEY_ESCAPE)
		win_close(vars, 0);
	else if (keydata.key == MLX_KEY_R)
		set_zoom(vars, new_coords(-(vars->x_res / 100), (vars->x_res / 100), \
		-(vars->y_res / 100), (vars->y_res / 100)));
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
