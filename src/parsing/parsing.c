/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/27 17:14:26 by kfu           #+#    #+#                 */
/*   Updated: 2021/05/02 09:32:47 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_scene(t_scene *scene)
{
	if (scene->width <= 0 || scene->height <= 0)
		error_and_exit(0, "No resolution");
	if (scene->camera == NULL)
		error_and_exit(0, "No camera(s)");
	if (scene->ambient.ratio == 0)
		error_and_exit(0, "No ambient");
}

int	parse_this_line(t_scene *scene, char **splitted, int words)
{
	int	ret;

	ret = 0;
	if (ft_isequal(splitted[0], "R"))
		ret = parse_resolution(scene, splitted, words);
	if (ft_isequal(splitted[0], "A"))
		ret = parse_ambient(scene, splitted, words);
	if (ft_isequal(splitted[0], "c"))
		ret = parse_camera(scene, splitted, words);
	if (ft_isequal(splitted[0], "l"))
		ret = parse_light(scene, splitted, words);
	if (ft_isequal(splitted[0], "sp"))
		ret = parse_sphere(scene, splitted, words);
	if (ft_isequal(splitted[0], "pl"))
		ret = parse_plane(scene, splitted, words);
	if (ft_isequal(splitted[0], "sq"))
		ret = parse_square(scene, splitted, words);
	if (ft_isequal(splitted[0], "cy"))
		ret = parse_cylinder(scene, splitted, words);
	if (ft_isequal(splitted[0], "tr"))
		ret = parse_triangle(scene, splitted, words);
	if (ret == -1)
		error_and_exit(0, "Something wrong with parsing");
	return (1);
}

int	read_and_parse(int fd, t_scene *scene)
{
	char	*line;
	char	**splitted;
	int		read;
	int		parse;
	int		words;

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
		splitted = ft_split(line, ' ', &words);
		if (splitted == NULL)
			break ;
		parse = parse_this_line(scene, splitted, words);
		ft_free_split(splitted);
		free(line);
		if (read == -1 || parse == -1)
			error_and_exit(0, "Something wrong with parsing");
	}
	return (1);
}

t_scene	*get_scene(char **argv, t_scene *scene)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_and_exit(0, "Could not open file");
	read_and_parse(fd, scene);
	check_scene(scene);
	return (scene);
}
