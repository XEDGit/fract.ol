/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:50 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/10 12:32:28 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	interpolate(t_color col1, t_color col2, float temp)
{
	t_color	res;

	res.rgba[3] = col1.rgba[3];
	res.rgba[2] = col1.rgba[2];
	res.rgba[1] = col1.rgba[1];
	res.rgba[3] = (col2.rgba[3] - res.rgba[3]) * temp + res.rgba[3];
	res.rgba[2] = (col2.rgba[2] - res.rgba[2]) * temp + res.rgba[2];
	res.rgba[1] = (col2.rgba[1] - res.rgba[1]) * temp + res.rgba[1];
	res.rgba[0] = 0xff;
	return (res.value);
}

int	color_mode(t_vars *vars, int n, int iter, float temp)
{
	if (!vars->color_set)
		return (interpolate((t_color){map(n, iter + 1, vars->color.value, \
			vars->color.value * vars->multiply)}, (t_color){map(n + 1, \
			iter + 1, vars->color.value, vars->color.value \
			* vars->multiply)}, temp));
	else if (vars->color_set == 1)
		return (interpolate((t_color){vars->palette[n % P_SIZE] + \
		vars->color.value}, (t_color){vars->palette[(n + 1) % P_SIZE] + \
		vars->color.value}, temp));
	else if (vars->color_set == 2)
		return (interpolate((t_color){((vars->color.rgba[3] * n) << 24) + \
		((vars->color.rgba[2] * n) << 16) + ((vars->color.rgba[1] * n) << 8)}, \
		(t_color){((vars->color.rgba[3] * (n + 1)) << 24) + \
		((vars->color.rgba[2] * (n + 1)) << 16) + ((vars->color.rgba[1] * \
		(n + 1)) << 8)}, temp));
	else
		return (interpolate((t_color){((vars->color.rgba[3] + n) << 24) \
		+ ((vars->color.rgba[2] + n) << 16) + ((vars->color.rgba[1] + n) << 8) \
		}, (t_color){((vars->color.rgba[3] + (n + 1)) << 24) + \
		((vars->color.rgba[2] + (n + 1)) << 16) + ((vars->color.rgba[1] + \
		(n + 1)) << 8)}, temp));
}

int	modulo_colors(long double z, int n, int iter, t_vars *vars)
{
	float	temp;
	t_color	i;

	if (n == iter)
		return (0xff);
	temp = n + 2 - log(log(z)) / .693147;
	n = (int)temp;
	temp = temp - n;
	i.value = color_mode(vars, n, iter, temp);
	i.rgba[0] = 0xff;
	return (i.value);
}

void	generate_palette(unsigned int *palette)
{
	palette[0] = (66 << 24) + (30 << 16) + (15 << 8) + 0xff;
	palette[1] = (25 << 24) + (7 << 16) + (26 << 8) + 0xff;
	palette[2] = (9 << 24) + (1 << 16) + (47 << 8) + 0xff;
	palette[3] = (4 << 24) + (4 << 16) + (73 << 8) + 0xff;
	palette[4] = (7 << 16) + (100 << 8) + 0xff;
	palette[5] = (12 << 24) + (44 << 16) + (138 << 8) + 0xff;
	palette[6] = (24 << 24) + (82 << 16) + (177 << 8) + 0xff;
	palette[7] = (57 << 24) + (125 << 16) + (209 << 8) + 0xff;
	palette[8] = (134 << 24) + (181 << 16) + (229 << 8) + 0xff;
	palette[9] = (211 << 24) + (236 << 16) + (248 << 8) + 0xff;
	palette[10] = (241 << 24) + (233 << 16) + (191 << 8) + 0xff;
	palette[11] = (248 << 24) + (201 << 16) + (95 << 8) + 0xff;
	palette[12] = (255 << 24) + (170 << 16) + 0xff;
	palette[13] = (204 << 24) + (128 << 16) + 0xff;
	palette[14] = (153 << 24) + (87 << 16) + 0xff;
	palette[15] = (106 << 24) + (52 << 16) + (3 << 8) + 0xff;
}
