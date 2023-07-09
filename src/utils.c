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

void	mouse(mouse_key_t button, action_t action, modifier_key_t mods, void* vvars)
{
	t_vars	*vars;
	int		cmd;

	cmd = 1;
	vars = (t_vars *)vvars;
	(void)mods;
	switch (button)
	{
		case MLX_MOUSE_BUTTON_LEFT:
			if (action == MLX_RELEASE)
			{
				vars->type = vars->typeog;
				vars->typeog = -1;
			}
			break;
		default:
			cmd = 0;
			break;
	}
	if (cmd)
		draw_set(vars);
}

void	key(mlx_key_data_t keydata, void *vvars)
{
	long double	xstep;
	long double	ystep;
	t_vars		*vars;
	int			cmd;

	cmd = 1;
	vars = (t_vars *)vvars;
	if (!vars)
		return ;
	xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10;
	ystep = fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10;
	shift_view(keydata.key, vars, xstep, ystep);
	switch (keydata.key)
	{
		case MLX_KEY_ESCAPE:
			win_close(vars, 0);
			break;
		case MLX_KEY_EQUAL:
			zoom(0, 1, vars);
			break;
		case MLX_KEY_MINUS:
			zoom(0, -1, vars);
			break;
		case MLX_KEY_R:
			vars->zoom = (t_coords){(-(vars->x_res / 50)), (vars->x_res / 50), \
			-(vars->y_res / 50), (vars->y_res / 50)};
			break;
		case MLX_KEY_COMMA:
			if (!vars->color_set && vars->palette[P_SIZE] > 500)
				vars->palette[P_SIZE] -= 500;
			break;
		case MLX_KEY_PERIOD:
			vars->palette[P_SIZE] += 500;
			break;
		case MLX_KEY_SLASH:
			vars->palette[P_SIZE] = 0;
			break;
		case MLX_KEY_W:
			vars->xconst -= vars->j_step;
			break;
		case MLX_KEY_S:
			vars->xconst += vars->j_step;
			break;
		case MLX_KEY_A:
			vars->yconst -= vars->j_step;
			break;
		case MLX_KEY_D:
			vars->yconst += vars->j_step;
			break;
		case MLX_KEY_TAB:
			if (keydata.action == MLX_PRESS)
				change_fractal(vars, -1);
			break;
		case MLX_KEY_RIGHT_BRACKET:
			if (vars->iters < 1000)
				vars->iters += 100;
			break;
		case MLX_KEY_LEFT_BRACKET:
			if (vars->iters - 100 >= 100)
				vars->iters -= 100;
			break;
		case MLX_KEY_C:
			if (keydata.action == MLX_PRESS && vars->color_set++)
				vars->color_set = 0;
			break;
		case MLX_KEY_J:
			if (keydata.action == MLX_PRESS && vars->type++)
				vars->type = 0;
			break;
		default:
			cmd = 0;
			break;
	}
	if (cmd)
		draw_set(vars);
}
