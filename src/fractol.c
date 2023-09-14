/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:58 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/26 17:23:00 by XEDGit        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_task(t_threadvars *v)
{
	int	ret;

	while (1)
	{
		pthread_mutex_lock(&v->vars->task_lock);
		if (!v->vars->running)
		{
			pthread_mutex_unlock(&v->vars->task_lock);
			pthread_exit(0);
		}
		if (v->vars->tasks_index * TASK_SIZE + TASK_SIZE <= v->vars->y_res)
			break ;
		pthread_mutex_unlock(&v->vars->task_lock);
		usleep(17000);
	}
	ret = v->vars->tasks[v->vars->tasks_index++];
	pthread_mutex_unlock(&v->vars->task_lock);
	return (ret);
}

void	*thread_main(void *vvars)
{
	t_threadvars	*v;
	int				i;

	v = (t_threadvars *)vvars;
	while (v->vars->running)
	{
		v->y = get_task(v);
		i = 0;
		while (i < TASK_SIZE)
		{
			v->x = 0;
			while (v->x < v->vars->x_res)
			{
				v->complex.b = map(v->y, v->vars->y_res, v->vars->zoom.ymin, \
					v->vars->zoom.ymax);
				v->complex.a = map(v->x, v->vars->x_res, v->vars->zoom.xmin, \
					v->vars->zoom.xmax);
				v->complex.az = v->complex.a;
				v->complex.bz = v->complex.b;
				if (v->vars->type)
				{
					v->complex.az = v->vars->xconst;
					v->complex.bz = v->vars->yconst;
				}
				mlx_put_pixel(v->vars->i, v->x++, v->y, v->vars->func(&v->complex, \
						v->vars->iters, v->vars));
			}
			i++;
			v->y++;
		}
	}
	pthread_exit(0);
}

void	draw_set(t_vars *vars)
{
	static int			nthreads = 0;
	int					i;

	vars->tasks_index = 0;
	i = 0;
	while (i * TASK_SIZE + TASK_SIZE <= vars->y_res)
	{
		vars->tasks[i] = i * TASK_SIZE;
		i++;
	}
	if (nthreads == 0)
	{
		vars->running = 1;
		while (nthreads < MAX_THREADS)
		{
			vars->threads[nthreads].vars = vars;
			pthread_create(&vars->threads[nthreads].thread, 0, \
				&thread_main, &vars->threads[nthreads]);
			nthreads++;
		}
	}
	while (vars->tasks_index * TASK_SIZE + TASK_SIZE < vars->y_res)
	{
		usleep(17000);
		continue ;
	}
}

void	initialize_vars(t_vars *vars)
{
	vars->iters = 200;
	vars->j_step = 0.001;
	vars->x_res = 1000;
	vars->y_res = 1000;
	vars->xconst = 0;
	vars->yconst = 0;
	vars->typeog = -1;
	vars->update = true;
	vars->multiply = 2;
	vars->color_set = 0;
	vars->color.value = 0x11111100;
	vars->running = true;
	vars->tasks_index = vars->y_res;
	pthread_mutex_init(&vars->task_lock, 0);
	change_fractal(vars, MANDELBROT);
	vars->mlx = mlx_init(vars->x_res, vars->y_res, "Fract.ol", true);
	vars->i = mlx_new_image(vars->mlx, vars->x_res, vars->y_res);
	if (!vars->i)
		win_close(vars, ERR_MSG);
}

void	loop(t_vars *vars)
{
	int				mpos[2];

	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		if (vars->typeog == -1)
			vars->typeog = vars->type;
		vars->type = 1;
		mlx_get_mouse_pos(vars->mlx, &mpos[0], &mpos[1]);
		vars->xconst = map(mpos[0], vars->x_res, vars->zoom.xmin, \
		vars->zoom.xmax);
		vars->yconst = map(mpos[1], vars->y_res, vars->zoom.ymin, \
		vars->zoom.ymax);
		vars->update = true;
	}
	if (vars->autozoom)
		zoom(0, 2, vars);
	if (vars->update || vars->autozoom)
	{
		vars->update = false;
		draw_set(vars);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_vars			vars;

	if (argc > 1)
	{
		print(HELP_MSG);
		return (0);
	}
	(void)argv;
	vars = (t_vars){0};
	initialize_vars(&vars);
	vars.tasks = malloc((vars.y_res / TASK_SIZE) * sizeof(int));
	generate_palette(vars.palette);
	mlx_key_hook(vars.mlx, &key, &vars);
	mlx_scroll_hook(vars.mlx, &zoom, &vars);
	mlx_resize_hook(vars.mlx, &resize, &vars);
	mlx_mouse_hook(vars.mlx, mouse, &vars);
	mlx_loop_hook(vars.mlx, (void (*)(void *))loop, &vars);
	reset_zoom(&vars);
	mlx_image_to_window(vars.mlx, vars.i, 0, 0);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
}
