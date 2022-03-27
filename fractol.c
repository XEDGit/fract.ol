/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:00:58 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/08 15:51:42 by lmuzio           ###   ########.fr       */
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
		while (x < vars->x_res)
		{
			complex.b = map(y, vars->y_res, vars->zoom->ymin, vars->zoom->ymax);
			complex.a = map(x, vars->x_res, vars->zoom->xmin, vars->zoom->xmax);
			complex.az = complex.a;
			complex.bz = complex.b;
			if (vars->type)
			{
				complex.az = vars->xconst;
				complex.bz = vars->yconst;
			}
			img_mlx_pixel_put(vars->i, x, y, vars->func(&complex, \
			vars->iters, vars));
			x++;
		}
		y++;
	}
}

void	check_args(t_vars *v, char **argv, int argc)
{
	v->type = 0;
	if (argc < 3)
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
	parse_settings(v, argv, argc);
}

int	loop(t_vars *vars)
{
	t_data	*temp;

	mlx_clear_window(vars->mlx, vars->mlx_win);
	temp = vars->img_buff;
	vars->img_buff = vars->i;
	vars->i = temp;
	draw_set(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->i->img, 0, 0);
	return (0);
}

void	initialize_vars(t_vars *vars, t_data *i, t_data *ib, unsigned long *p)
{
	vars->mlx = mlx_init();
	vars->mlx_win = 0;
	vars->zoom = 0;
	vars->i = i;
	vars->img_buff = ib;
	vars->palette = p;
	vars->i->img = mlx_new_image(vars->mlx, vars->x_res, vars->y_res);
	vars->img_buff->img = mlx_new_image(vars->mlx, vars->x_res, vars->y_res);
	if (!vars->i->img || !vars->img_buff->img)
		win_close(vars, ERR_MSG);
	vars->i->addr = mlx_get_data_addr(vars->i->img, \
	&vars->i->bpp, &vars->i->l_l, &vars->i->e);
	vars->img_buff->addr = mlx_get_data_addr(vars->img_buff->img, \
	&vars->img_buff->bpp, &vars->img_buff->l_l, &vars->img_buff->e);
}

int	main(int argc, char **argv)
{
	t_vars			vars;
	t_data			img;
	t_data			img_b;
	unsigned long	palette[P_SIZE + 1];

	check_args(&vars, argv, argc);
	initialize_vars(&vars, &img, &img_b, palette);
	if (vars.color_set)
		generate_palette(palette);
	vars.mlx_win = mlx_new_window(vars.mlx, vars.x_res, vars.y_res, "fract.ol");
	set_zoom(&vars, new_coords(-(vars.x_res / 100), (vars.x_res / 100), \
	-(vars.y_res / 100), (vars.y_res / 100)));
	mlx_mouse_hook(vars.mlx_win, zoom, &vars);
	mlx_key_hook(vars.mlx_win, key, &vars);
	mlx_hook(vars.mlx_win, 17, 0, win_close, &vars);
	mlx_loop_hook(vars.mlx, loop, &vars);
	mlx_loop(vars.mlx);
}
