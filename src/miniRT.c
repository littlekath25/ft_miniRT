/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 12:51:09 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/28 15:17:42 by kfu           ########   odam.nl         */
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

int	main(int argc, char **argv)
{
	t_scene		*scene;
	t_mlx		*window;
	t_img		*bmp;

	scene = ft_static_scene();
	window = NULL;
	bmp = NULL;
	if (ft_check_argv(argc, argv))
	{
		scene = ft_get_scene(argv, scene);
		if (scene->bmp == 1)
		{
			bmp = ft_init_img(bmp, NULL);
			ft_make_image(bmp, scene);
			ft_create_bmp(scene, bmp);
			printf("File saved as minirt.bmp\n");
			exit (1);
		}
		window = ft_init_mlx();
		window->image = ft_init_img(window->image, window);
		ft_make_image(window->image, scene);
		mlx_put_image_to_window(window->ptr, \
		window->win, window->image->img, 0, 0);
	}
	mlx_key_hook(window->win, key_hook, window);
	mlx_loop(window->ptr);
	exit(1);
}
