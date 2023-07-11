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

size_t	interpolate(size_t col1, size_t col2, float temp)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (col1 >> 24) & 0xff;
	g = (col1 >> 16) & 0xff;
	b = (col1 >> 8) & 0xff;
	r = ((unsigned char)((col2 >> 24) & 0xff) - r) * temp + r;
	g = ((unsigned char)((col2 >> 16) & 0xff) - g) * temp + g;
	b = ((unsigned char)((col2 >> 8) & 0xff) - b) * temp + b;
	return (((r << 24) + (g << 16) + (b << 8)) + 0xff);
}

size_t	modulo_colors(long double z, int n, int iter, t_vars *vars)
{
	float			temp;
	unsigned long	i;

	if (n == iter)
		return (0xff);
	temp = n + 2 - log(log(z)) / .693147;
	n = (int)temp;
	temp = temp - n;
	if (!vars->color_set)
		i = interpolate(map(n, iter + 1, vars->palette[P_SIZE], \
			vars->palette[P_SIZE] * vars->multiply), map(n + 1, \
			iter + 1, vars->palette[P_SIZE], vars->palette[P_SIZE] \
			* vars->multiply), temp);
	else
		i = interpolate(vars->palette[n % P_SIZE] + vars->palette[P_SIZE], \
			vars->palette[(n + 1) % P_SIZE] + vars->palette[P_SIZE], temp);
	return (((i >> 8) << 8) + 0xff);
}

void	generate_palette(unsigned long *palette)
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
	palette[P_SIZE] = 0x222222ff;
}
