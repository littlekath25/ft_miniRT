/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/27 17:14:26 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/20 16:56:42 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_parse_this_line(t_scene *scene, char **splitted)
{
	int	ret;

	ret = 0;
	if (ft_isequal(splitted[0], "R"))
		ret = ft_parse_resolution(scene, splitted);
	if (ft_isequal(splitted[0], "A"))
		ret = ft_parse_ambient(scene, splitted);
	if (ft_isequal(splitted[0], "c"))
		ret = ft_parse_camera(scene, splitted);
	if (ft_isequal(splitted[0], "l"))
		ret = ft_parse_light(scene, splitted);
	if (ft_isequal(splitted[0], "sp"))
		ret = ft_parse_sphere(scene, splitted);
	if (ft_isequal(splitted[0], "pl"))
		ret = ft_parse_plane(scene, splitted);
	if (ft_isequal(splitted[0], "sq"))
		ret = ft_parse_square(scene, splitted);
	if (ft_isequal(splitted[0], "cy"))
		ret = ft_parse_cylinder(scene, splitted);
	if (ft_isequal(splitted[0], "tr"))
		ret = ft_parse_triangle(scene, splitted);
	if (ret == -1)
		ft_error_and_exit(0, "Something wrong with parsing");
	return (1);
}

int	ft_read_and_parse(int fd, t_scene *scene)
{
	char	*line;
	char	**splitted;
	int		read;
	int		parse;

	read = 1;
	parse = 0;
	while (read > 0)
	{
		read = get_next_line(fd, &line);
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		splitted = ft_split(line, ' ');
		if (splitted == NULL)
			break ;
		parse = ft_parse_this_line(scene, splitted);
		ft_free_split(splitted);
		free(line);
		if (read == -1 || parse == -1)
			ft_error_and_exit(0, "Something wrong with parsing");
	}
	scene->current_cam = scene->camera;
	return (1);
}

t_scene	*ft_get_scene(int argc, char **argv, t_scene *scene)
{
	int	fd;

	fd = 0;
	if (argc < 2 || argc == 3)
	{
		if (argc == 3 && ft_strcmp(argv[2], "--save"))
			ft_error_and_exit(0, "The second argument have to be --save");
		// if (argc == 3 && !ft_strcmp(argv[2], "--save"))
		// {
		// 	ft_bmp();
		// 	printf("File saved as minirt.bmp\n");
		// }
		else
			ft_error_and_exit(0, "Invalid number of arguments");
		exit(1);
	}
	if (argc == 2 && ft_strncmp_rev(argv[1], ".rt", 3))
		ft_error_and_exit(0, "The file must end with .rt");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error_and_exit(0, "Could not open file");
	// scene = (t_scene *)ft_calloc(sizeof(t_scene), 1);
	// if (!scene)
	// 	ft_error_and_exit(3, "Scene - ");
	ft_read_and_parse(fd, scene);
	return (scene);
}
