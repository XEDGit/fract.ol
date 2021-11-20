#include "fractol.h"

size_t	modulo_colors(int n)
{
	unsigned long	palette[10];

	if (n == MAX_ITER)
		return (0);
	palette[0] = (0x1a1a1a);
	palette[1] = (0x333333);
	palette[2] = (0x4d4d4d);
	palette[3] = (0x666666);
	palette[4] = (0x7f7f7f);
	palette[5] = (0x999999);
	palette[6] = (0xb3b3b3);
	palette[7] = (0xcccccc);
	palette[8] = (0xe5e5e5);
	palette[9] = (0xffffff);
	return (palette[n % (MAX_ITER / (MAX_ITER / 10))]);
}

size_t	color_set(int n, int shift, int set)
{
	size_t		res;

	if (set == 1)
		return (modulo_colors(n));
	if (n == MAX_ITER)
		return (0x0);
	if (!set)
		return (n * 255 * (shift + 1));
	if (shift + MAX_ITER < n)
		shift = MAX_ITER;
	else
		shift += MAX_ITER;
	res = map(n, shift, 0, 0xFFFFFF);
	return (res);
}
