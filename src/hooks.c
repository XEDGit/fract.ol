/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/15 02:43:44 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	resize(int width, int height, void *vvars)
{
	t_vars	*vars;
	t_task	*new_tasks;
	int		i;

	vars = (t_vars *)vvars;
	new_tasks = malloc((height / TASK_SIZE) * sizeof(t_task) * 2);
	if (!new_tasks)
	{
		vars->running = 0;
		print("Failed allocating space for task queue");
		return ;
	}
	i = 0;
	while (vars->tasks[i].starty != -1)
	{
		new_tasks[i] = vars->tasks[i];
		i++;
	}
	pthread_mutex_lock(&vars->task_end);
	vars->x_res = width;
	vars->y_res = height;
	free(vars->tasks);
	vars->tasks = new_tasks;
	vars->tasks_index = 0;
	mlx_resize_image(vars->i, width, height);
	reset_zoom(vars);
	pthread_mutex_unlock(&vars->task_end);
}

void	key3(mlx_key_data_t k, t_vars *vars, int *cmd)
{
	if (k.key == MLX_KEY_APOSTROPHE && k.action != MLX_RELEASE)
		vars->multiply += 0.01;
	else if (k.key == MLX_KEY_SEMICOLON && \
	k.action != MLX_RELEASE)
		vars->multiply -= 0.01;
	else if (k.key == MLX_KEY_BACKSLASH)
		vars->multiply = 2;
	else if (k.key == MLX_KEY_SPACE && k.action == MLX_PRESS)
		vars->autozoom = !vars->autozoom;
	else if (k.key == MLX_KEY_R && k.action != MLX_RELEASE)
		vars->color.rgba[3] += 1;
	else if (k.key == MLX_KEY_G && k.action != MLX_RELEASE)
		vars->color.rgba[2] += 1;
	else if (k.key == MLX_KEY_B && k.action != MLX_RELEASE)
		vars->color.rgba[1] += 1;
	else if (k.action != MLX_RELEASE)
		shift_view(k.key, vars, fabsl(vars->zoom.xmax - vars->zoom.xmin) / 10, \
		fabsl(vars->zoom.ymax - vars->zoom.ymin) / 10);
	else
		*cmd = 0;
}

void	key2(mlx_key_data_t k, t_vars *vars, int *cmd)
{
	if (k.key == MLX_KEY_COMMA && vars->color.rgba[3] >= 0x11 \
	&& k.action != MLX_RELEASE)
			vars->color.value -= 0x11111100;
	else if (k.key == MLX_KEY_PERIOD && vars->color.rgba[3] <= 0xee \
	&& k.action != MLX_RELEASE)
		vars->color.value += 0x11111100;
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
		if (vars->color_set++ == 3)
			vars->color_set = 0;
	}
	else if (k.key == MLX_KEY_J && k.action == MLX_PRESS)
		vars->type = !vars->type;
	else
		key3(k, vars, cmd);
}

void	key(mlx_key_data_t k, void *vvars)
{
	t_vars		*vars;
	int			cmd;

	cmd = 0;
	vars = (t_vars *)vvars;
	if (k.key == MLX_KEY_EQUAL)
		zoom(0, 1, vars);
	else if (k.key == MLX_KEY_MINUS)
		zoom(0, -1, vars);
	else
		cmd = 1;
	if (!cmd)
		return ;
	pthread_mutex_lock(&vars->task_end);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT_CONTROL) && k.key == MLX_KEY_R)
		reset_zoom(vars);
	else if (k.key == MLX_KEY_SLASH)
		vars->color.value = 0x11111100;
	else if (k.key == MLX_KEY_ESCAPE)
		vars->running = 0;
	else
		key2(k, vars, &cmd);
	vars->update = cmd;
	pthread_mutex_unlock(&vars->task_end);
}

void	mouse(mouse_key_t button, action_t action, modifier_key_t mods, \
	void *vvars)
{
	t_vars	*vars;
	int		cmd;

	cmd = 1;
	vars = (t_vars *)vvars;
	pthread_mutex_lock(&vars->task_end);
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
	{
		vars->type = vars->typeog;
		vars->typeog = -1;
	}
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		vars->autozoom = !vars->autozoom;
	else
		cmd = 0;
	vars->update = cmd;
	pthread_mutex_unlock(&vars->task_end);
}
