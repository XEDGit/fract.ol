#include "fractol.h"

void	draw_set(t_vars *vars)
{
	int			x;
	int			y;
	double		a;
	double		b;
	size_t		col;

	y = 0;
	while (y < vars->sizey)
	{
		x = 0;
		while (x < vars->sizex)
		{
			b = map(y, vars->sizey, vars->zoom->ymin, vars->zoom->ymax);
			a = map(x, vars->sizex, vars->zoom->xmin, vars->zoom->xmax);
			if (!vars->type)
				col = vars->func(a, b, a, b);
			else
				col = vars->func(a, b, vars->xconst, vars->yconst);
			col = color_set(col, vars->colshift, COL_SET);
			mlx_pixel_put(vars->mlx, vars->mlx_win, x, y, col);
			x++;
		}
		y++;
	}
}

void	check_args(t_vars *vars, char **argv, int argc)
{
	vars->type = 0;
	if (argc < 2)
		error_quit(HELP_MSG);
	vars->colshift = 0;
	if (argv[1][0] == 'm')
		vars->func = calc_mandel;
	else if (argv[1][0] == 'j')
	{
		if (argc < 4)
			error_quit(HELP_MSG);
		vars->xconst = ft_atof(argv[2]);
		vars->yconst = ft_atof(argv[3]);
		vars->func = calc_mandel;
		vars->type = 1;
	}
	else
		error_quit(HELP_MSG);
}

int	loop(t_vars *vars)
{
	draw_set(vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.sizex = WIN_SIZE;
	vars.sizey = WIN_SIZE;
	check_args(&vars, argv, argc);
	vars.zoom = 0;
	set_zoom(&vars, new_coords(-2.5, 1.5, -2, 2));
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, vars.sizex, vars.sizey, "fract.ol");
	mlx_mouse_hook(vars.mlx_win, zoom, &vars);
	mlx_key_hook(vars.mlx_win, key, &vars);
	mlx_hook(vars.mlx_win, 17, 0, close, &vars);
	mlx_loop_hook(vars.mlx, loop, &vars);
	draw_set(&vars);
	mlx_loop(vars.mlx);
}
