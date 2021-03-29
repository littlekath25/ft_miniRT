/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 12:51:09 by kfu           #+#    #+#                 */
/*   Updated: 2021/03/28 13:03:28 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_mlx	*ft_init_mlx(t_scene *scene)
{
	t_mlx	*window;
	int		width;
	int		height;

	window = (t_mlx *)ft_calloc(sizeof(t_mlx), 1);
	if (!window)
		ft_error_and_exit(3, "Window - ");
	window->ptr = mlx_init();
	mlx_get_screen_size(window->ptr, &width, &height);
	if (scene->width > width)
		scene->width = width;
	if (scene->height > height)
		scene->height = height;
	window->win = mlx_new_window(window->ptr, scene->width, scene->height, "MiniRT");
	return (window);
}

t_img	*ft_init_img(t_img *img, t_mlx *window, t_scene *scene)
{
	img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (!img)
		ft_error_and_exit(3, "Image - ");
	img->img = mlx_new_image(window->ptr, scene->width, scene->height);
	img->address = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	return (img);
}

int	main(int argc, char **argv)
{
	t_scene		*scene;
	t_mlx		*window;
	t_img		*img;

	if (argv)
	{
		scene = ft_get_scene(argc, argv, scene);
		window = ft_init_mlx(scene);
		img = ft_init_img(img, window, scene);
		ft_make_image(img, scene);
		mlx_put_image_to_window(window->ptr, window->win, img->img, 0, 0);
	}
	mlx_key_hook(window->win, key_hook, window);
	mlx_loop(window->ptr);
	exit(1);
}
