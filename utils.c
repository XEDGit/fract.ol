#include "fractol.h"

int	win_close(t_vars *vars, char *msg)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_image(vars->mlx, vars->img_buff->img);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free(vars->zoom);
	if (msg && *msg >= 'A' && *msg <= 'Z')
		printf("%s", msg);
	exit(0);
}

long double	map(long double middle, long double win_size, long double min, \
long double max)
{
	return (middle / win_size * (max - min) + min);
}

int	key(int key, t_vars *vars)
{
	long double	xstep;
	long double	ystep;

	xstep = fabsl(vars->zoom->xmax - vars->zoom->xmin) / 10;
	ystep = fabsl(vars->zoom->ymax - vars->zoom->ymin) / 10;
	shift_view(key, vars, xstep, ystep);
	if (key == 53)
		win_close(vars, 0);
	else if (key == 47)
		vars->colshift += 10;
	else if (key == 15)
		set_zoom(vars, new_coords(-2.5, 1.5, -2, 2));
	else if (key == 35)
		vars->colshift = 0;
	else if (key == 43 && !COL_SET && vars->colshift > 0)
		vars->colshift -= 10;
	else if (key == 43 && COL_SET == 2)
		vars->colshift -= 10;
	return (0);
}

void	img_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
