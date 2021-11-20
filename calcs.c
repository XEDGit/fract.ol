#include "fractol.h"

size_t	calc_mandel(long double a, long double b, long double oa, \
long double ob)
{
	int			n;
	long double	tempa;
	long double	tempb;

	n = 0;
	tempa = 0;
	tempb = 0;
	while (tempa + tempb < 4 && MAX_ITER > n)
	{
		tempa = a * a;
		tempb = b * b;
		b = a * b;
		b = b + b + ob;
		a = tempa - tempb + oa;
		n++;
	}
	return (n);
}

long double	ft_atof(char *s)
{
	long double	res;
	int			min;

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

size_t	calc_burning_ship(long double a, long double b, long double oa, \
long double ob)
{
	int			n;
	long double	tempa;
	long double	tempb;

	n = 0;
	tempa = 0;
	tempb = 0;
	while ((int)(tempa + tempb) < 4 && MAX_ITER > n)
	{
		tempa = a * a;
		tempb = b * b;
		b = fabsl(a * b);
		b = b + b + ob;
		a = tempa - tempb + oa;
		n++;
	}
	return (n);
}
