/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:01:01 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 13:14:43 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print(const char *s)
{
	int		buffer_length;

	buffer_length = 0;
	if (!s)
		return ;
	while (s[buffer_length])
		buffer_length++;
	if (write(1, s, buffer_length))
		return ;
}

int	win_close(t_vars *vars, char *msg)
{
	if (vars && vars->mlx)
	{
		mlx_close_window(vars->mlx);
		mlx_terminate(vars->mlx);
	}
	print(msg);
	exit(0);
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
