/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:58 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/06 15:34:35 by XEDGit        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_set(t_vars *vars)
{
	int				x;
	int				y;
	t_complex		complex;

	y = 0;
	while (y < vars->y_res)
	{
		x = 0;
		if (y == vars->y_res / 2)
		{
			mlx_put_pixel(vars->i, x, y, (0xff << 24) + 0xff);
			y++;
			continue ;
		}
		while (x < vars->x_res)
		{
			if (x == vars->x_res / 2)
			{
				mlx_put_pixel(vars->i, x, y, (0xff << 24) + 0xff);
				x++;
				continue ;
			}
			complex.b = map(y, vars->y_res, vars->zoom.ymin, vars->zoom.ymax);
			complex.a = map(x, vars->x_res, vars->zoom.xmin, vars->zoom.xmax);
			complex.az = complex.a;
			complex.bz = complex.b;
			if (vars->type)
			{
				complex.az = vars->xconst;
				complex.bz = vars->yconst;
			}
			mlx_put_pixel(vars->i, x, y, vars->func(&complex, \
			vars->iters, vars));
			x++;
		}
		y++;
	}
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

void	loop(t_vars *vars)
{
	draw_set(vars);
	mlx_image_to_window(vars->mlx, vars->i, 0, 0);
	return ;
}

void	initialize_vars(t_vars *vars)
{
	vars->mlx = mlx_init(vars->x_res, vars->y_res, "Fract.ol", false);
	vars->i = mlx_new_image(vars->mlx, vars->x_res, vars->y_res);
	if (!vars->i)
		win_close(vars, ERR_MSG);
}

int	main(int argc, char **argv)
{
	t_vars			vars;

	vars = (t_vars){0};
	check_args(&vars, argv, argc);
	initialize_vars(&vars);
	generate_palette(vars.palette);
	vars.zoom = (t_coords){-(vars.x_res / 100), (vars.x_res / 100), \
	-(vars.y_res / 100), (vars.y_res / 100)};
	mlx_key_hook(vars.mlx, &key, &vars);
	mlx_scroll_hook(vars.mlx, &zoom, &vars);
	mlx_loop_hook(vars.mlx, (void (*)(void *))loop, &vars);
	mlx_image_to_window(vars.mlx, vars.i, 0, 0);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
}
