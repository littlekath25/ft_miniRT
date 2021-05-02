/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_info.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/27 17:21:55 by kfu           #+#    #+#                 */
/*   Updated: 2021/05/01 23:15:25 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	parse_resolution(t_scene *scene, char **splitted, int words)
{
	static int	resolution;
	int			width;
	int			height;

	if (words != 3)
		error_and_exit(0, "Wrong resolution values");
	if (resolution == 1)
		error_and_exit(1, "Resolution - ");
	resolution = 0;
	width = ft_atoi(splitted[1]);
	height = ft_atoi(splitted[2]);
	if (width < 0 || height < 0)
		error_and_exit(2, "Resolution - ");
	scene->width = width;
	scene->height = height;
	resolution = 1;
	return (1);
}

int	parse_ambient(t_scene *scene, char **splitted, int words)
{
	static int	ambient;
	char		*category;

	if (words != 3)
		error_and_exit(0, "Wrong ambient values");
	category = "Ambient - ";
	if (ambient == 1)
		error_and_exit(1, category);
	ambient = 0;
	if (!(check_ratio(splitted[1])) || !(check_colors(splitted[2])))
		error_and_exit(2, category);
	scene->ambient.ratio = ft_atof(splitted[1]);
	fill_colors(splitted[2], &scene->ambient.colors);
	scene->ambient.colors = \
	color_scale(scene->ambient.colors, scene->ambient.ratio);
	ambient = 1;
	return (1);
}

int	parse_camera(t_scene *scene, char **splitted, int words)
{
	t_list		*new_node;
	t_camera	*camera;
	char		*category;

	if (words != 4)
		error_and_exit(0, "Wrong camera values");
	category = "Camera - ";
	if (!(check_fov(splitted[3])) || !(check_orientation(splitted[2])))
		error_and_exit(2, category);
	camera = (t_camera *)ft_calloc(sizeof(t_camera), 1);
	new_node = ft_lstnew(camera);
	if (!camera || !new_node)
		error_and_exit(3, category);
	ft_lstadd_back(&scene->camera, new_node);
	fill_position(splitted[1], &camera->pos);
	fill_orientation(splitted[2], &camera->ori);
	camera->fov = tan(ft_atoi(splitted[3]) * (M_PI / 180) / 2);
	scene->current_cam = scene->camera;
	return (1);
}

int	parse_light(t_scene *scene, char **splitted, int words)
{
	t_list	*new_node;
	t_light	*light;
	char	*category;

	if (words != 4)
		error_and_exit(0, "Wrong light values");
	category = "Light - ";
	if (!(check_ratio(splitted[2])) || !(check_colors(splitted[3])))
		error_and_exit(2, category);
	light = (t_light *)ft_calloc(sizeof(t_light), 1);
	new_node = ft_lstnew(light);
	if (!light || !new_node)
		error_and_exit(3, category);
	ft_lstadd_back(&scene->light, new_node);
	if ((fill_position(splitted[1], &light->pos)) == -1 || \
	(fill_colors(splitted[3], &light->colors)) == -1)
		return (-1);
	light->ratio = ft_atof(splitted[2]);
	return (1);
}
