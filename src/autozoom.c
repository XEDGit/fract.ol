/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   autozoom.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:00:42 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/07/09 13:57:56 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_autozoom_set(t_vars *vars, t_azframe *imgs)
{
	t_threadvars	tvars[AUTOZOOM_FRAMES];
	int				nthreads;

	nthreads = 0;
	while (nthreads < AUTOZOOM_FRAMES)
	{
		tvars[nthreads] = (t_threadvars){
			0, {0}, vars, 0, 0, vars->y_res, imgs[nthreads].i, \
			imgs[nthreads].zoom
		};
		pthread_create(&tvars[nthreads].thread, 0, \
			&thread_main, &tvars[nthreads]);
		nthreads++;
	}
	while (nthreads--)
		pthread_join(tvars[nthreads].thread, 0);
}

void	free_imgs(t_vars *vars, t_azframe *imgs)
{
	int	i;

	i = 0;
	while (i < AUTOZOOM_FRAMES && imgs[i].i)
		mlx_delete_image(vars->mlx, imgs[i++].i);
	free(imgs);
}

t_azframe	*gen_autozoom(t_vars *vars)
{
	t_azframe	*zoom_imgs;
	int			i;

	zoom_imgs = malloc(sizeof(t_azframe) * (AUTOZOOM_FRAMES));
	if (!zoom_imgs)
		return (0);
	i = 0;
	while (i < AUTOZOOM_FRAMES)
	{
		zoom(0, 0.5, vars);
		zoom_imgs[i].zoom = vars->zoom;
		zoom_imgs[i].i = mlx_new_image(vars->mlx, vars->x_res, vars->y_res);
		if (!zoom_imgs[i].i)
		{
			free_imgs(vars, zoom_imgs);
			win_close(vars, "Error allocating autozoom image\n");
			return (0);
		}
		i++;
	}
	draw_autozoom_set(vars, zoom_imgs);
	return (zoom_imgs);
}

void	reset_autozoom(t_vars *vars, t_azframe **imgs, int *i, uint8_t **pix)
{
	if (*i != AUTOZOOM_FRAMES)
		vars->autozoom = 0;
	if (*i == AUTOZOOM_FRAMES)
		*i = *i - 1;
	memcpy(*pix, (*imgs)[*i].i->pixels, vars->y_res * vars->x_res \
		* sizeof(uint32_t));
	vars->i->pixels = *pix;
	free_imgs(vars, *imgs);
	*pix = 0;
	*i = 0;
	*imgs = 0;
}

void	handle_autozoom(t_vars *vars)
{
	static uint8_t		*og_pixels = 0;
	static t_azframe	*autozoom_imgs = 0;
	static int			i = 0;

	if (!vars->autozoom && i)
		reset_autozoom(vars, &autozoom_imgs, &i, &og_pixels);
	if (vars->autozoom)
	{
		if (!autozoom_imgs)
		{
			autozoom_imgs = gen_autozoom(vars);
			og_pixels = vars->i->pixels;
		}
		if (i < AUTOZOOM_FRAMES)
		{
			vars->i->pixels = autozoom_imgs[i].i->pixels;
			i++;
		}
		else if (i == AUTOZOOM_FRAMES)
			reset_autozoom(vars, &autozoom_imgs, &i, &og_pixels);
	}
}
