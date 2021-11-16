#include "fractol.h"

size_t	color_set(int n, int shift)
{
	size_t		res;

	if (n == MAX_ITER)
		return (0x0);
	if (n < MAX_ITER / 30)
		return (0xFFFFFF);
	if (shift + MAX_ITER < n)
		shift = MAX_ITER;
	else
		shift += MAX_ITER;
	res = map(n, shift, 0, 0xFFFFFF);
	return (res);
}

size_t	calc_mandel(double a, double b, double oa, double ob)
{
	int		n;
	double	temp;
	int		max;

	n = 0;
	max = MAX_ITER;
	while (a + b < 4 && max > n)
	{
		temp = ((a * a) - (b * b)) + oa;
		b = 2 * a * b + ob;
		a = temp;
		n++;
	}
	return (n);
}

size_t	calc_julia(double a, double b, double vara, double varb)
{
	int		n;
	double	temp;
	int		max;

	n = 0;
	max = MAX_ITER;
	while (a + b < 4 && max > n)
	{
		temp = ((a * a) - (b * b)) + vara;
		b = 2 * a * b + varb;
		a = temp;
		n++;
	}
	return (n);
}

double	ft_atof(char *s)
{
	double	res;
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

void	atof_cycle(char *s, double *res)
{
	int	c;

	c = 0;
	while (*s != '.' && *s)
	{
		*res *= 10;
		*res += *s++ - '0';
	}
	if (*s == '.')
		s++;
	while (*s)
	{
		*res *= 10;
		*res += *s++ - '0';
		c++;
	}
	while (c--)
		*res /= 10;
}
