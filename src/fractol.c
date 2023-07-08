/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:58 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 00:54:31 by lmuzio        ########   odam.nl         */
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

void	check_args(t_vars *v, char **argv, int argc)
{
	v->type = 0;
	if (argc < 3 || ft_isnum(argv[2]))
		win_close(0, HELP_MSG);
	v->iters = ft_atof(argv[2]);
	if (argv[1][0] == 'm' && !argv[1][1])
		v->func = calc_mandel;
	else if (argv[1][0] == 'j' && !argv[1][1])
	{
		if (argc < 5)
			win_close(v, HELP_MSG);
		v->xconst = ft_atof(argv[2]);
		v->yconst = ft_atof(argv[3]);
		v->iters = ft_atof(argv[4]);
		v->func = calc_mandel;
		v->type = 1;
	}
	else if (argv[1][0] == 'b' && !argv[1][1])
		v->func = calc_burning_ship;
	else
		win_close(0, HELP_MSG);
	if (v->iters <= 0)
		win_close(0, ERR_MSG);
	parse_settings(v, argv, argc);
}

void	initialize_vars(t_vars *vars)
{
	vars->mlx = mlx_init(vars->x_res, vars->y_res, "Fract.ol", false);
	vars->i = mlx_new_image(vars->mlx, vars->x_res, vars->y_res);
	if (!vars->i)
		win_close(vars, ERR_MSG);
	pthread_mutex_init(&vars->mutex, 0);
}

int	main(int argc, char **argv)
{
	t_vars			vars;

	vars = (t_vars){0};
	check_args(&vars, argv, argc);
	initialize_vars(&vars);
	generate_palette(vars.palette);
	vars.zoom = (t_coords){(-(vars.x_res / 100)), (vars.x_res / 100), \
	-(vars.y_res / 100), (vars.y_res / 100)};
	mlx_key_hook(vars.mlx, &key, &vars);
	mlx_scroll_hook(vars.mlx, &zoom, &vars);
	draw_set(&vars);
	mlx_loop_hook(vars.mlx, (void (*)(void *))loop, &vars);
	mlx_image_to_window(vars.mlx, vars.i, 0, 0);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
}
