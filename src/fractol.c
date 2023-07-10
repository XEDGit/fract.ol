/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:58 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 13:11:14 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*thread_main(void *vvars)
{
	t_threadvars	*v;

	v = (t_threadvars *)vvars;
	while (v->y < v->y_fract)
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
		v->y++;
	}
	pthread_exit(0);
}

void	draw_set(t_vars *vars)
{
	t_threadvars	tvars[MAX_THREADS];
	int				nthreads;

	nthreads = 0;
	while (nthreads < MAX_THREADS)
	{
		tvars[nthreads] = (t_threadvars){
			0, {0}, vars, 0, (vars->y_res / MAX_THREADS) * nthreads, \
			(vars->y_res / MAX_THREADS) * (nthreads + 1)
		};
		pthread_create(&tvars[nthreads].thread, 0, \
			&thread_main, &tvars[nthreads]);
		nthreads++;
	}
	while (nthreads--)
		pthread_join(tvars[nthreads].thread, 0);
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
	if (type == 1)
	{
		vars->yconst = -1.762;
		vars->xconst = 0.028;
	}
	current = type;
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
	vars->color_set = 0;
	change_fractal(vars, MANDELBROT);
	vars->mlx = mlx_init(vars->x_res, vars->y_res, "Fract.ol", true);
	vars->i = mlx_new_image(vars->mlx, vars->x_res, vars->y_res);
	if (!vars->i)
		win_close(vars, ERR_MSG);
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
	generate_palette(vars.palette);
	mlx_key_hook(vars.mlx, &key, &vars);
	mlx_scroll_hook(vars.mlx, &zoom, &vars);
	mlx_resize_hook(vars.mlx, &resize, &vars);
	mlx_mouse_hook(vars.mlx, mouse, &vars);
	mlx_loop_hook(vars.mlx, (void (*)(void *))loop, &vars);
	key((mlx_key_data_t){MLX_KEY_R, MLX_PRESS, 0, 0}, &vars);
	mlx_image_to_window(vars.mlx, vars.i, 0, 0);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
}
