#include "fractol.h"

void	draw_set(t_vars *vars)
{
	int				x;
	int				y;
	long double		a;
	long double		b;
	size_t			col;

	y = 0;
	while (y < WIN_SIZE)
	{
		x = 0;
		b = map(y, WIN_SIZE, vars->zoom->ymin, vars->zoom->ymax);
		while (x < WIN_SIZE)
		{
			a = map(x, WIN_SIZE, vars->zoom->xmin, vars->zoom->xmax);
			if (!vars->type)
				col = vars->func(a, b, a, b);
			else
				col = vars->func(a, b, vars->xconst, vars->yconst);
			col = color_set(col, vars->colshift, COL_SET);
			img_mlx_pixel_put(vars->img, x, y, col);
			x++;
		}
		y++;
	}
}

void	check_args(t_vars *vars, char **argv, int argc)
{
	vars->type = 0;
	vars->zoom = 0;
	if (argc < 2)
		win_close(vars, HELP_MSG);
	vars->colshift = 0;
	if (argv[1][0] == 'm')
		vars->func = calc_mandel;
	else if (argv[1][0] == 'j')
	{
		if (argc < 4)
			win_close(vars, HELP_MSG);
		vars->xconst = ft_atof(argv[2]);
		vars->yconst = ft_atof(argv[3]);
		vars->func = calc_mandel;
		vars->type = 1;
	}
	else if (argv[1][0] == 'b')
		vars->func = calc_burning_ship;
	else
		win_close(vars, ERR_MSG);
}

int	loop(t_vars *vars)
{
	t_data	*temp;

	mlx_clear_window(vars->mlx, vars->mlx_win);
	temp = vars->img_buff;
	vars->img_buff = vars->img;
	vars->img = temp;
	draw_set(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;
	t_data	img_buff;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, WIN_SIZE, WIN_SIZE, "fract.ol");
	vars.img = &img;
	vars.img_buff = &img_buff;
	img.img = mlx_new_image(vars.mlx, WIN_SIZE, WIN_SIZE);
	img_buff.img = mlx_new_image(vars.mlx, WIN_SIZE, WIN_SIZE);
	if (!img.img || !img_buff.img)
		win_close(&vars, ERR_MSG);
	check_args(&vars, argv, argc);
	set_zoom(&vars, new_coords(-2, 2, -2, 2));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
									&img.line_length, &img.endian);
	img_buff.addr = mlx_get_data_addr(img_buff.img, &img_buff.bits_per_pixel, \
									&img_buff.line_length, &img_buff.endian);
	mlx_mouse_hook(vars.mlx_win, zoom, &vars);
	mlx_key_hook(vars.mlx_win, key, &vars);
	mlx_hook(vars.mlx_win, 17, 0, win_close, &vars);
	mlx_loop_hook(vars.mlx, loop, &vars);
	mlx_loop(vars.mlx);
}
