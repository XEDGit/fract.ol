/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:00:42 by lmuzio            #+#    #+#             */
/*   Updated: 2022/03/26 21:41:50 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double	ft_atof(char *s)
{
	long double	res;
	int		min;

	res = 0;
	min = 0;
	if (*s == '-')
		min = 1;
	if (min)
		s++;
	atof_cycle(s, &res);
	if (min)
		res = -res;
	return (res);
}

void	atof_cycle(char *s, long double *res)
{
	int	c;

	c = 0;
	while (*s != '.' && *s)
	{
		*res *= 10;
		*res += *s - '0';
		s++;
	}
	if (*s == '.')
		s++;
	while (*s)
	{
		*res *= 10;
		*res += *s - '0';
		c++;
		s++;
	}
	while (c--)
		*res /= 10;
}

size_t	calc_mandel(t_complex *comp, int iter, t_vars *vars)
{
	int		n;
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
	int		n;
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
