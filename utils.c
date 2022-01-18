/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:01:01 by lmuzio            #+#    #+#             */
/*   Updated: 2022/01/18 19:04:38 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	if (msg == HELP_MSG || msg == ERR_MSG)
		printf("%s", msg);
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
		set_zoom(vars, new_coords(-(WIN_SIZE_X / 100), (WIN_SIZE_X / 100), \
		-(WIN_SIZE_Y / 100), (WIN_SIZE_Y / 100)));
	else if (key == 43 && !COL_SET && vars->palette[P_SIZE] - 13 >= 0)
		vars->palette[P_SIZE] -= 13;
	else if (key == 43 && COL_SET)
		vars->palette[P_SIZE] -= 13;
	else if (key == 47)
		vars->palette[P_SIZE] += 12;
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
