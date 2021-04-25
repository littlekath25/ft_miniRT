/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 12:51:09 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/25 18:19:10 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_scene *ft_static_scene(void)
{
	static t_scene scene;
	return (&scene);
}

int		ft_check_argv(int argc, char **argv)
{
	t_scene *scene;

	scene = ft_static_scene();
	scene->bmp = 0;
	if (argc < 2 || argc > 3)
	{
		ft_error_and_exit(0, "Invalid number of arguments");
		exit(1);
	}
	if (argc == 2 && ft_strncmp_rev(argv[1], ".rt", 3))
		ft_error_and_exit(0, "The file must end with .rt");
	if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "--save"))
			scene->bmp = 1;
		else
			ft_error_and_exit(0, "The second argument have to be --save");
	}
	return (1); 
}

t_mlx	*ft_init_mlx(void)
{
	t_mlx	*window;
	int		width;
	int		height;
	t_scene	*scene;

	scene = ft_static_scene();
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

t_img	*ft_init_img(t_img *img, t_mlx *window)
{
	t_scene *scene;

	scene = ft_static_scene();
	img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (!img)
		ft_error_and_exit(3, "Image - ");
	img->img = mlx_new_image(window->ptr, scene->width, scene->height);
	img->address = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (scene->bmp == 1)
		img->data = (char *)ft_calloc(sizeof(unsigned char), scene->width * scene->height * 4 + 1);
	return (img);
}

int	main(int argc, char **argv)
{
	t_scene		*scene;
	t_mlx		*window;

	scene = ft_static_scene();
	if (ft_check_argv(argc, argv))
	{
		scene = ft_get_scene(argc, argv, scene);
		window = ft_init_mlx();
		window->image = ft_init_img(window->image, window);
		ft_make_image(window->image);
		if (scene->bmp == 1)
		{
			ft_create_bmp(scene, window);
			printf("File saved as minirt.bmp\n");
			exit (1);
		}
		mlx_put_image_to_window(window->ptr, window->win, window->image->img, 0, 0);
	}
	mlx_key_hook(window->win, key_hook, window);
	// mlx_mouse_hook(window->win, debugray, scene);
	mlx_loop(window->ptr);
	exit(1);
}
