/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/10 12:33:21 by lmuzio        ########   odam.nl         */
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

void	key3(mlx_key_data_t k, t_vars *vars, int *cmd)
{
	long double	xstep;
	long double	ystep;

	if (k.key == MLX_KEY_APOSTROPHE && k.action != MLX_RELEASE)
		vars->multiply += 0.1;
	else if (k.key == MLX_KEY_SEMICOLON && vars->multiply > 1.1 && \
	k.action != MLX_RELEASE)
		vars->multiply -= 0.1;
	else if (k.key == MLX_KEY_BACKSLASH)
		vars->multiply = 2;
	else if (k.key == MLX_KEY_SPACE && k.action == MLX_PRESS)
	{
		if (vars->autozoom++)
			vars->autozoom = 0;
	}
	else if (k.action != MLX_RELEASE)
	{
		xstep = fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10;
		ystep = fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10;
		shift_view(k.key, vars, xstep, ystep);
	}
	else
		*cmd = 0;
}

void	key2(mlx_key_data_t k, t_vars *vars, int *cmd)
{
	if (k.key == MLX_KEY_COMMA && k.action != MLX_RELEASE)
			vars->palette[P_SIZE] -= 0x111111ff;
	else if (k.key == MLX_KEY_PERIOD && k.action != MLX_RELEASE)
		vars->palette[P_SIZE] += 0x111111ff;
	else if (k.key == MLX_KEY_TAB && k.action == MLX_PRESS)
		change_fractal(vars, -1);
	else if (k.key == MLX_KEY_RIGHT_BRACKET && vars->iters < 2000 && \
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
		key3(k, vars, cmd);
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
		key2(k, vars, &cmd);
	vars->update = cmd;
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
	vars->update = cmd;
}
