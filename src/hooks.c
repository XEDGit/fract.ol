/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 00:51:13 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>

void	resize(int width, int height, void *vvars)
{
	t_vars		*vars;

	vars = (t_vars *)vvars;
	vars->x_res = width;
	vars->y_res = height;
	mlx_resize_image(vars->i, width, height);
	key((mlx_key_data_t){MLX_KEY_R, MLX_PRESS, 0, 0}, vars);
}

int	key2(mlx_key_data_t k, t_vars *vars)
{
	if (k.key == MLX_KEY_COMMA && vars->palette[P_SIZE] > 500)
			vars->palette[P_SIZE] -= 500;
	else if (k.key == MLX_KEY_PERIOD)
		vars->palette[P_SIZE] += 500;
	else if (k.key == MLX_KEY_TAB && k.action == MLX_PRESS)
		change_fractal(vars, -1);
	else if (k.key == MLX_KEY_RIGHT_BRACKET && vars->iters < 1000 && \
	k.action == MLX_PRESS)
		vars->iters += 100;
	else if (k.key == MLX_KEY_LEFT_BRACKET && vars->iters - 100 >= 100 \
	&& k.action == MLX_PRESS)
		vars->iters -= 100;
	else if (k.key == MLX_KEY_C && k.action == MLX_PRESS)
	{
		if (vars->color_set++)
			vars->color_set = 0;
	}
	else if (k.key == MLX_KEY_J && k.action == MLX_PRESS)
	{
		if (vars->type++)
			vars->type = 0;
	}
	else
		return (0);
	return (1);
}

void	key3(mlx_key_data_t k, t_vars *vars, int cmd)
{
	long double	xstep;
	long double	ystep;

	xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10;
	ystep = fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10;
	if (!cmd && k.action != MLX_RELEASE)
		cmd = shift_view(k.key, vars, xstep, ystep);
	if (cmd)
		draw_set(vars);
}

void	key(mlx_key_data_t k, void *vvars)
{
	t_vars		*vars;
	int			cmd;

	cmd = 1;
	vars = (t_vars *)vvars;
	if (k.key == MLX_KEY_R)
	{
		if (vars->x_res < vars->y_res)
			vars->zoom = (t_coords){-2, 2, -2 * ((double)vars->y_res / \
			vars->x_res), 2 * ((double)vars->y_res / vars->x_res)};
		else
			vars->zoom = (t_coords){-2 * ((double)vars->x_res / \
			vars->y_res), 2 * ((double)vars->x_res / vars->y_res), -2, 2};
	}
	else if (k.key == MLX_KEY_EQUAL)
		zoom(0, 1, vars);
	else if (k.key == MLX_KEY_MINUS)
		zoom(0, -1, vars);
	else if (k.key == MLX_KEY_SLASH)
		vars->palette[P_SIZE] = 0;
	else if (k.key == MLX_KEY_ESCAPE)
		win_close(vars, 0);
	else
		cmd = key2(k, vars);
	key3(k, vars, cmd);
}

void	mouse(mouse_key_t button, action_t action, modifier_key_t mods, \
	void *vvars)
{
	t_vars	*vars;
	int		cmd;

	cmd = 1;
	vars = (t_vars *)vvars;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
	{
		vars->type = vars->typeog;
		vars->typeog = -1;
	}
	else
		cmd = 0;
	if (cmd)
		draw_set(vars);
}
