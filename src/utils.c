/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:01:01 by lmuzio            #+#    #+#             */
/*   Updated: 2022/03/27 21:50:17 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print(const char *s)
{
	int		buffer_length;

	buffer_length = 0;
	if (!s)
		return ;
	while (s[buffer_length])
		buffer_length++;
	write(1, s, buffer_length);
}

int	win_close(t_vars *vars, char *msg)
{
	if (vars)
	{
		if (vars->i->img)
			mlx_destroy_image(vars->mlx, vars->i->img);
		if (vars->img_buff->img)
			mlx_destroy_image(vars->mlx, vars->img_buff->img);
		if (vars->mlx_win)
			mlx_destroy_window(vars->mlx, vars->mlx_win);
		free(vars->zoom);
	}
	if (msg == HELP_MSG || msg == ERR_MSG \
	|| msg == ADD_ARG_MSG || msg == TOO_MANY_ARGS)
		print(msg);
	exit(0);
}

double	map(double middle, double win_size, double min, \
double max)
{
	double	first;
	double	second;

	first = middle / win_size;
	second = max - min;
	return (first * second + min);
}

int	key(int key, t_vars *vars)
{
	double	xstep;
	double	ystep;

	xstep = fabsl(vars->zoom->xmax - vars->zoom->xmin) / 10;
	ystep = fabsl(vars->zoom->ymax - vars->zoom->ymin) / 10;
	shift_view(key, vars, xstep, ystep);
	if (key == 53)
		win_close(vars, 0);
	else if (key == 15)
		set_zoom(vars, new_coords(-(vars->x_res / 100), (vars->x_res / 100), \
		-(vars->y_res / 100), (vars->y_res / 100)));
	else if (key == 43 && !vars->color_set && vars->palette[P_SIZE] > 12)
		vars->palette[P_SIZE] -= 12;
	else if (key == 43 && vars->color_set)
		vars->palette[P_SIZE] -= 12;
	else if (key == 47)
		vars->palette[P_SIZE] += 13;
	else if (key == 35)
		vars->palette[P_SIZE] = 0;
	return (0);
}

void	img_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
