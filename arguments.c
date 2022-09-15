/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:34:18 by lmuzio            #+#    #+#             */
/*   Updated: 2022/09/15 21:11:46 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isnum(char *str)
{
	while (*str)
		if (*str < '0' || *str++ > '9')
			return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	long		res;
	int			min;

	res = 0;
	min = 0;
	if (!*str)
		return (res);
	while (*str == ' ' || *str == '	' || *str == '\t'\
	|| *str == '\n' || *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		min = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str++ - '0';
	}
	if (min)
		res *= -min;
	return (res);
}

void	check_additional_settings(t_vars *v, char *s)
{
	int	counter;

	counter = 0;
	while (s[counter])
	{
		if (s[counter] == 'x')
		{
			v->x_res = ft_atoi(s);
			v->y_res = ft_atoi(&s[counter + 1]);
			if (v->x_res <= 0 || v->y_res <= 0)
				win_close(0, ERR_MSG);
			return ;
		}
		else if (s[counter] == '.')
		{
			v->j_step = ft_atof(s);
			return ;
		}
		counter++;
	}
	if (counter == 1 && (*s == '0' || *s == '1'))
		v->color_set = ft_atoi(s);
	else
		win_close(0, ADD_ARG_MSG);
}

void	parse_settings(t_vars *v, char **argv, int argc)
{
	int	arg_start;

	v->j_step = 0.1;
	v->color_set = 0;
	v->x_res = 1000;
	v->y_res = 1000;
	if ((argc < 5 && argv[1][0] == 'j') || argc < 3)
		return ;
	if (argv[1][0] != 'j')
		arg_start = 3;
	else
		arg_start = 5;
	if (argc - arg_start > 3)
		win_close(0, TOO_MANY_ARGS);
	while (--argc >= arg_start)
	{
		check_additional_settings(v, argv[argc]);
		if (argv[1][0] != 'j' && v->j_step != 0.1)
			win_close(0, TOO_MANY_ARGS);
	}
}
