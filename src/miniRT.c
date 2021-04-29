/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 12:51:09 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/29 20:29:56 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_scene	*static_scene(void)
{
	static t_scene	scene;

	return (&scene);
}

int	check_argv(int argc, char **argv)
{
	t_scene	*scene;

	scene = static_scene();
	scene->bmp = 0;
	if (argc < 2 || argc > 3)
	{
		error_and_exit(0, "Invalid number of arguments");
		exit(1);
	}
	if (argc == 2 && ft_strncmp_rev(argv[1], ".rt", 3))
		error_and_exit(0, "The file must end with .rt");
	if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "--save"))
			scene->bmp = 1;
		else
			error_and_exit(0, "The second argument have to be --save");
	}
	return (1);
}

t_mlx	*ft_render(t_mlx *window, char **argv)
{
	t_scene	*scene;

	scene = static_scene();
	scene = get_scene(argv, scene);
	if (scene->bmp == 1)
	{
		window->image = init_img(window->image, NULL);
		make_image(window->image, scene);
		create_bmp(scene, window->image);
		exit (1);
	}
	window = init_mlx(scene);
	window->image = init_img(window->image, window);
	make_image(window->image, scene);
	mlx_put_image_to_window(window->ptr, \
	window->win, window->image->img, 0, 0);
	return (window);
}

int	main(int argc, char **argv)
{
	t_mlx		*window;

	window = NULL;
	if (check_argv(argc, argv))
		window = ft_render(window, argv);
	mlx_key_hook(window->win, key_hook, window);
	mlx_hook(window->win, 33, 1L << 0, close_rt, &window);
	mlx_loop(window->ptr);
	exit(1);
}
