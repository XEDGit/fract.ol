#include "fractol.h"

size_t	calc_mandel(double a, double b, double oa, double ob)
{
	int		n;
	double	temp;
	double	tempa;
	double	tempb;

	n = 0;
	tempa = 0;
	tempb = 0;
	while (tempa + tempb < 4 && MAX_ITER > n)
	{
		tempa = a * a;
		tempb = b * b;
		temp = tempa - tempb + oa;
		b = 2 * a * b + ob;
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

size_t	modulo_colors(int n)
{
	int	modulo;

	modulo = n % (MAX_ITER / (MAX_ITER / 10));
	if (modulo == 1)
		return (0x1a1a1a);
	if (modulo == 2)
		return (0x333333);
	if (modulo == 3)
		return (0x4d4d4d);
	if (modulo == 4)
		return (0x666666);
	if (modulo == 5)
		return (0x7f7f7f);
	if (modulo == 6)
		return (0x999999);
	if (modulo == 7)
		return (0xb3b3b3);
	if (modulo == 8)
		return (0xcccccc);
	if (modulo == 9)
		return (0xe5e5e5);
	if (modulo == 10)
		return (0xffffff);
	return (0);
}

size_t	color_set(int n, int shift, int set)
{
	size_t		res;

	if (set == 1)
		return (modulo_colors(n));
	if (!set)
		return ((MAX_ITER - n) * 255 * (shift + 1));
	if (n == MAX_ITER)
		return (0x0);
	if (shift + MAX_ITER < n)
		shift = MAX_ITER;
	else
		shift += MAX_ITER;
	res = map(n, shift, 0, 0xFFFFFF);
	return (res);
}
