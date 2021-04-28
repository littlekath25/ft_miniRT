/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_init.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:27:51 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/28 15:19:36 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_mlx	*ft_init_mlx(void)
{
	t_mlx	*window;
	// int		width;
	// int		height;
	t_scene	*scene;

	scene = ft_static_scene();
	window = (t_mlx *)ft_calloc(sizeof(t_mlx), 1);
	if (!window)
		ft_error_and_exit(3, "Window - ");
	window->ptr = mlx_init();
	// mlx_get_screen_size(window->ptr, &width, &height);
	// if (scene->width > width)
	// 	scene->width = width;
	// if (scene->height > height)
	// 	scene->height = height;
	window->win = \
	mlx_new_window(window->ptr, scene->width, scene->height, "MiniRT");
	return (window);
}

t_img	*ft_init_img(t_img *img, t_mlx *window)
{
	t_scene	*scene;

	scene = ft_static_scene();
	img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (!img)
		ft_error_and_exit(3, "Image - ");
	if (scene->bmp == 1)
	{
		img->data = (char *)ft_calloc(sizeof(unsigned char), \
		(scene->width * scene->height * 4));
		img->line_len = 4 * scene->width;
		img->bpp = 32;
		return (img);
	}
	img->img = mlx_new_image(window->ptr, scene->width, scene->height);
	img->address = \
	mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	return (img);
}