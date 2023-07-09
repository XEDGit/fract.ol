/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calcs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:42 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 12:47:57 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	loop(t_vars *vars)
{
	static t_coords	last_zoom = {-100, -100, 0, 0};
	int				mpos[2];
	int				mousedown;

	mousedown = mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_LEFT);
	if (mousedown)
	{
		if (vars->typeog == -1)
			vars->typeog = vars->type;
		vars->type = 1;
		mlx_get_mouse_pos(vars->mlx, &mpos[0], &mpos[1]);
		vars->xconst = map(mpos[0], vars->x_res, vars->zoom.xmin, vars->zoom.xmax);
		vars->yconst = map(mpos[1], vars->y_res, vars->zoom.ymin, vars->zoom.ymax);
	}
	if (mousedown || last_zoom.xmax != vars->zoom.xmax || last_zoom.xmin != vars->zoom.xmin)
		draw_set(vars);
	last_zoom = vars->zoom;
	return ;
}
