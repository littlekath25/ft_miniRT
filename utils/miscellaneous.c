/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miscellaneous.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 17:24:24 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/29 19:33:09 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	reset_impact(t_impact *impact)
{
	impact->intersect = 0;
	impact->near = INFINITY;
	impact->normal = (t_vector){0};
}

int	close_rt(void)
{
	exit(1);
	return (1);
}

int	key_hook(int keycode, t_mlx *window)
{
	t_scene	*scene;

	scene = static_scene();
	if (keycode == ESC)
		exit(1);
	if (keycode == TAB)
	{
		if (scene->current_cam->next != NULL)
			scene->current_cam = scene->current_cam->next;
		else
			scene->current_cam = scene->camera;
		make_image(window->image, scene);
		mlx_put_image_to_window(window->ptr, \
		window->win, window->image->img, 0, 0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char		*dst;
	t_scene		*scene;
	int			i;

	scene = static_scene();
	i = (scene->height - y - 1) * img->line_len + x * img->bpp / 8;
	if (scene->bmp == 1)
	{
		img->data[i] = color & 255;
		img->data[i + 1] = (color >> 8) & 255;
		img->data[i + 2] = (color >> 16) & 255;
		img->data[i + 3] = 0;
		return ;
	}
	dst = img->address + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_vector	new_vector(double x, double y, double z)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
