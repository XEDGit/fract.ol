/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calcs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:42 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 13:57:56 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

size_t	calc_mandel(t_complex *comp, int iter, t_vars *vars)
{
	int			n;
	long double	tempa;
	long double	tempb;

	n = 0;
	tempa = comp->a * comp->a;
	tempb = comp->b * comp->b;
	while (tempa + tempb < 100 && iter > n)
	{
		tempa = comp->a * comp->a;
		tempb = comp->b * comp->b;
		comp->b = comp->a * comp->b;
		comp->b = comp->b + comp->b + comp->bz;
		comp->a = tempa - tempb + comp->az;
		n++;
	}
	return (modulo_colors(tempa + tempb, n, iter, vars));
}

size_t	calc_burning_ship(t_complex *comp, int iter, t_vars *vars)
{
	int			n;
	long double	tempa;
	long double	tempb;

	n = 0;
	tempa = comp->a * comp->a;
	tempb = comp->b * comp->b;
	while (tempa + tempb < 100 && iter > n)
	{
		tempa = comp->a * comp->a;
		tempb = comp->b * comp->b;
		comp->b = fabsl(comp->a * comp->b);
		comp->b = comp->b + comp->b + comp->bz;
		comp->a = tempa - tempb + comp->az;
		n++;
	}
	return (modulo_colors(tempa + tempb, n, iter, vars));
}

long double	map(long double middle, long double win_size, long double min, \
long double max)
{
	long double	first;
	long double	second;

	first = middle / win_size;
	second = max - min;
	min = first * second + min;
	return (min);
}
