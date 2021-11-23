#include "fractol.h"

size_t	interpolate(size_t col1, size_t col2, float temp)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (col1) >> 16 & 0xff;
	g = (col1) >> 8 & 0xff;
	b = (col1) & 0xff;
	r = ((unsigned char)((col2) >> 16 & 0xff) - r) * temp + r;
	g = ((unsigned char)((col2) >> 8 & 0xff) - g) * temp + g;
	b = ((unsigned char)((col2) & 0xff) - b) * temp + b;
	return ((r << 16) + (g << 8) + b);
}

size_t	modulo_colors(double z, int n, int iter, unsigned long *p)
{
	float			temp;
	unsigned long	i;

	if (n == iter)
		return (0);
	temp = n + 2 - log(log(z)) / .693147;
	n = (int)temp;
	temp = temp - (int)temp;
	(void)p;
	if (!COL_SET)
		i = interpolate(map(n, iter, 0x888888, 0xffffff), \
						map(n + 1, iter, 0x888888, 0xffffff), temp);
	else
		i = interpolate(p[n % P_SIZE], p[(n + 1) % P_SIZE], temp);
	return (i);
}

void	generate_palette(unsigned long *palette)
{
	palette[0] = (66 << 16) + (30 << 8) + 15;
	palette[1] = (25 << 16) + (7 << 8) + 26;
	palette[2] = (9 << 16) + (1 << 8) + 47;
	palette[3] = (4 << 16) + (4 << 8) + 73;
	palette[4] = (7 << 8) + 100;
	palette[5] = (12 << 16) + (44 << 8) + 138;
	palette[6] = (24 << 16) + (82 << 8) + 177;
	palette[7] = (57 << 16) + (125 << 8) + 209;
	palette[8] = (134 << 16) + (181 << 8) + 229;
	palette[9] = (211 << 16) + (236 << 8) + 248;
	palette[10] = (241 << 16) + (233 << 8) + 191;
	palette[11] = (248 << 16) + (201 << 8) + 95;
	palette[12] = (255 << 16) + (170 << 8);
	palette[13] = (204 << 16) + (128 << 8);
	palette[14] = (153 << 16) + (87 << 8);
	palette[15] = (106 << 16) + (52 << 8) + 3;
}
