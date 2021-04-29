/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 12:51:09 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/29 19:52:04 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_scene	*ft_static_scene(void)
{
	static t_scene	scene;

	return (&scene);
}

int	ft_check_argv(int argc, char **argv)
{
	t_scene	*scene;

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

t_mlx	*ft_render(t_mlx *window, char **argv)
{
	t_scene	*scene;

	scene = ft_static_scene();
	scene = ft_get_scene(argv, scene);
	if (scene->bmp == 1)
	{
		window->image = ft_init_img(window->image, NULL);
		ft_make_image(window->image, scene);
		ft_create_bmp(scene, window->image);
		exit (1);
	}
	window = ft_init_mlx(scene);
	window->image = ft_init_img(window->image, window);
	ft_make_image(window->image, scene);
	mlx_put_image_to_window(window->ptr, \
	window->win, window->image->img, 0, 0);
	return (window);
}

int	main(int argc, char **argv)
{
	t_mlx		*window;

	window = NULL;
	if (ft_check_argv(argc, argv))
		window = ft_render(window, argv);
	mlx_key_hook(window->win, ft_key_hook, window);
	mlx_hook(window->win, 33, 1L << 0, ft_close, &window);
	mlx_loop(window->ptr);
	exit(1);
}
