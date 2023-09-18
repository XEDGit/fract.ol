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

t_task	get_task(t_threadvars *v)
{
	t_task	ret;

	pthread_mutex_lock(&v->vars->task_lock);
	v->vars->working_threads--;
	pthread_cond_signal(&v->vars->work_cond);
	while (v->vars->tasks[v->vars->tasks_index].starty == -1 && v->vars->running)
		pthread_cond_wait(&v->vars->task_cond, &v->vars->task_lock);
	if (!v->vars->running)
	{
		pthread_mutex_unlock(&v->vars->task_lock);
		pthread_exit(0);
	}
	v->vars->working_threads++;
	ret = v->vars->tasks[v->vars->tasks_index];
	if (ret.starty != -1)
		v->vars->tasks_index++;
	pthread_mutex_unlock(&v->vars->task_lock);
	return (ret);
}

void	thread_process_task(t_threadvars *v, long double y_mapped)
{
	while (v->x < v->vars->x_res)
	{
		v->complex.b = y_mapped;
		v->complex.a = map(v->x, v->vars->x_res, v->vars->zoom.xmin, \
			v->vars->zoom.xmax);
		if (v->vars->type)
		{
			v->complex.az = v->vars->xconst;
			v->complex.bz = v->vars->yconst;
		}
		else
		{
			v->complex.az = v->complex.a;
			v->complex.bz = v->complex.b;
		}
		mlx_put_pixel(v->vars->i, v->x++, v->y, v->vars->func(&v->complex, \
				v->vars->iters, v->vars));
	}
}

void	*thread_main(void *vvars)
{
	t_threadvars	*v;
	t_task			task;

	v = (t_threadvars *)vvars;
	while (v->vars->running)
	{
		task.starty = -1;
		while (task.starty == -1)
			task = get_task(v);
		v->y = task.starty;
		for (int i = 0; i < task.count; i++)
		{
			v->x = 0;
			thread_process_task(v, map(v->y, v->vars->y_res, v->vars->zoom.ymin, \
				v->vars->zoom.ymax));
			v->y++;
		}
	}
	pthread_exit(0);
}

void	draw_set(t_vars *vars)
{
	static int			nthreads = 0;
	int					i;

	pthread_mutex_lock(&vars->task_end);
	pthread_mutex_lock(&vars->task_lock);
	vars->tasks_index = 0;
	i = 0;
	while (i * TASK_SIZE + TASK_SIZE <= vars->y_res)
	{
		vars->tasks[i] = (t_task){i * TASK_SIZE, TASK_SIZE};
		i++;
	}
	if (i * TASK_SIZE < vars->y_res)
	{
		vars->tasks[i] = (t_task){i * TASK_SIZE, vars->y_res - (i * TASK_SIZE) - 1};
		i++;
	}
	vars->tasks[i].starty = -1;
	pthread_mutex_unlock(&vars->task_lock);
	if (nthreads == 0)
	{
		vars->running = 1;
		while (nthreads < NTHREADS)
		{
			vars->threads[nthreads].vars = vars;
			pthread_create(&vars->threads[nthreads].thread, 0, \
				&thread_main, &vars->threads[nthreads]);
			nthreads++;
		}
	}
	pthread_cond_broadcast(&vars->task_cond);
	usleep(3);
	pthread_mutex_lock(&vars->task_lock);
	while (vars->working_threads != 0)
		pthread_cond_wait(&vars->work_cond, &vars->task_lock);
	if (vars->running == false)
	{
		pthread_mutex_unlock(&vars->task_lock);
		pthread_mutex_unlock(&vars->task_end);
		vars->running = true;
		win_close(vars, 0);
	}
	pthread_mutex_unlock(&vars->task_lock);
	pthread_mutex_unlock(&vars->task_end);
}

void	initialize_vars(t_vars *vars)
{
	vars->iters = 200;
	vars->j_step = 0.001;
	vars->autozoom = BENCH_AUTOZOOM;
	vars->running = true;
	vars->tasks_index = vars->y_res;
	vars->working_threads = NTHREADS;
	vars->tasks[0].starty = -1;
	vars->x_res = 1000;
	vars->y_res = 1000;
	vars->xconst = 0;
	vars->yconst = 0;
	vars->typeog = -1;
	vars->update = true;
	vars->multiply = 2;
	vars->color_set = 0;
	vars->color.value = 0x11111100;
	pthread_mutex_init(&vars->task_lock, 0);
	pthread_mutex_init(&vars->task_end, 0);
	pthread_cond_init(&vars->task_cond, 0);
	pthread_cond_init(&vars->work_cond, 0);
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
		BENCH_START;
		vars->update = false;
		draw_set(vars);
		BENCH_END;
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
	vars.tasks = malloc((1000 / TASK_SIZE) * sizeof(t_task) * 2);
	if (!vars.tasks)
		win_close(0, "Failed allocating space for task queue");
	initialize_vars(&vars);
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
