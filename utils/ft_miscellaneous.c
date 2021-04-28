/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_miscellaneous.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 17:24:24 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/28 17:18:48 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_reset_impact(t_impact *impact)
{
	impact->intersect = 0;
	impact->near = INFINITY;
	impact->normal = (t_vector){0};
}

int	key_hook(int keycode, t_mlx *window)
{
	t_scene	*scene;

	scene = ft_static_scene();
	if (keycode == 65307 || keycode == 53)
		exit(1);
	if (keycode == 65289 || keycode == 48)
	{
		if (scene->current_cam->next != NULL)
			scene->current_cam = scene->current_cam->next;
		else
			scene->current_cam = scene->camera;
		ft_make_image(window->image, scene);
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

	scene = ft_static_scene();
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

t_vector	ft_copy_vector(t_vector copy)
{
	t_vector	new;

	new.x = copy.x;
	new.y = copy.y;
	new.z = copy.z;
	return (new);
}

t_vector	ft_new_vector(double x, double y, double z)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
