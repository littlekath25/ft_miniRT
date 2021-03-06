/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:27:51 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/29 17:24:45 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_mlx	*init_mlx(t_scene *scene)
{
	t_mlx	*window;
	int		width;
	int		height;

	window = (t_mlx *)ft_calloc(sizeof(t_mlx), 1);
	if (!window)
		error_and_exit(3, "Window - ");
	window->ptr = mlx_init();
	mlx_get_screen_size(window->ptr, &width, &height);
	if (scene->width > width)
		scene->width = width;
	if (scene->height > height)
		scene->height = height;
	window->win = \
	mlx_new_window(window->ptr, scene->width, scene->height, "MiniRT");
	return (window);
}

t_img	*init_img(t_img *img, t_mlx *window)
{
	t_scene	*scene;

	scene = static_scene();
	img = (t_img *)calloc(sizeof(t_img), 1);
	if (!img)
		error_and_exit(3, "Image - ");
	if (scene->bmp == 1)
	{
		img->data = (char *)ft_calloc(sizeof(unsigned char), \
		(scene->width * scene->height * 4));
		if (!img->data)
			error_and_exit(3, "Image - ");
		img->line_len = 4 * scene->width;
		img->bpp = 32;
		return (img);
	}
	img->img = mlx_new_image(window->ptr, scene->width, scene->height);
	img->address = \
	mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	return (img);
}
